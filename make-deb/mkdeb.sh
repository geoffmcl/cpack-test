#!/bin/sh
#< mkdeb.sh
BN=`basename $0`
TMPREPO="git@github.com:htacg/tidy-html5.git"
TMPDIR="tidy-html5"
TMPFIL="version.txt"
CWD="$(pwd)"
TMPCTL="control"
TMPLOG="$CWD/bldlog-u.txt"
TMPMD5="mkmd5sum.sh"
TMPDDIR="DEBIAN"
#TMPDDIR="debian"
TMPMAN="usr/share/man/man1/tidy.1"
if [ -f "$TMPLOG" ]; then
    rm -f "$TMPLOG"
fi

echo "$BN: Update $TMPDIR, in $CWD"
if [ -d "$TMPDIR" ]; then
    cd "$TMPDIR"
    echo "$BN: Doing 'git pull' in $(pwd)..."
    git pull
else
    echo "$BN: Doing 'git clone $TMPREPO $TMPDIR'..."
    git clone $TMPREPO $TMPDIR
    cd "$TMPDIR"
fi
if [ ! -f "$TMPFIL" ]; then
    echo "$BN: Can NOT locate $TMPFIL!"
    exit 1
fi

echo "$BN: Getting version and architecture..."
TMPARCH=`uname -m`
# TMPVER=$(cat version.txt)
while read line; do
    TMPVER="$line"
    break
done < "$TMPFIL"
echo "$BN: Version '$TMPVER' arch '$TMPARCH'"
TMPDIR2="tidy-$TMPVER-$TMPARCH"
echo "$BN: DEB directory '$TMPDIR2'"
# TMPINST="$CWD/$TMPDIR2"
# TMPINST="$CWD/$TMPDIR2/usr/local"
TMPINST="$CWD/$TMPDIR2/usr"
#TMPDEB="tidy-5.1.47-x86_64.deb"
TMPDEB="$TMPDIR2.deb"
TMPMD5FIL="$TMPDIR2/$TMPDDIR/md5sums"
MANFIL="$TMPDIR2/$TMPMAN"
TMPTIDY="$TMPDIR2/usr/bin/tidy"
TMPLIB="$TMPDIR2/usr/lib/libtidy.so.$TMPVER"

cd build/cmake
echo "$BN: Doing 'cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$TMPINST'"
echo "$BN: Doing 'cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$TMPINST'" >> "$TMPLOG"
cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$TMPINST >> $TMPLOG 2>&1
if [ ! "$?" = "0" ]; then
    echo "$BN: cmake configuration or generation FAILED!"
    exit 1
fi
echo "$BN: Doing 'make'"
echo "$BN: Doing 'make'" >> "$TMPLOG"
make >> "$TMPLOG" 2>&1
if [ ! "$?" = "0" ]; then
    echo "$BN: make FAILED!"
    echo "$BN: make FAILED!" >> "$TMPLOG"
    exit 1
fi
TMPLAST="$(pwd)"
#####################################
### enter root mode - DID NOT WORK
### echo "$BN: Enter root login..."
### sudo su
#####################################
# get back to root
cd "$CWD"
if [ -d "$TMPDIR2" ]; then
    echo "$BN: Removing last install... '$TMPDIR2'"
    # sudo rm -rf "$TMPINST"
    rm -rf "$TMPDIR2"
else
    echo "$BN: No previous install '$TMPDIR2'"
fi
if [ -d "$TMPDIR2" ]; then
    echo "$BN: FAILED to remove '$TMPDIR2'!"
    exit 1
fi
# temp exit
# exit 1

# back to build
cd "$TMPLAST"
# echo "$BN: Doing 'sudo make install'"
# sudo make install
echo "$BN: Doing 'make install'"
echo "$BN: Doing 'make install'" >> "$TMPLOG"
make install >> "$TMPLOG" 2>&1
if [ ! "$?" = "0" ]; then
    echo "$BN: make install FAILED!"
    echo "$BN: make install FAILED!" >> "$TMPLOG"
    exit 1
fi
# get back to root
cd "$CWD"
if [ ! -d "$TMPDIR2" ]; then
    echo "$BN: Install to $TMPDIR2 FAILED!"
    exit 1
fi
if [ ! -d "$TMPDIR2/$TMPDDIR" ]; then
    mkdir "$TMPDIR2/$TMPDDIR"
else
    echo "$BN: '$TMPDIR2/$TMPDDIR' already exists..."
fi
#####################################
### Modify files
if [ -f "$MANFIL" ]; then
    echo "$BN: Compressing man file $MANFIL"
    gzip -v -9 $MANFIL
else
    echo "$BN: Warning: NOT FOUND file $MANFIL"
fi
#####################################
### is this the strip
if [ -f "$TMPTIDY" ]; then
    echo "$BN: Stripping file $TMPTIDY"
    strip -s $TMPTIDY
else
    echo "$BN: Warning: NOT FOUND file $TMPTIDY!"
fi
if [ -f "$TMPLIB" ]; then
    echo "$BN: Stripping file $TMPLIB"
    strip -s $TMPLIB
else
    echo "$BN: Warning: NOT FOUND file $TMPLIB!"
fi
######################################
echo "$BN: Writting '$TMPDIR2/$TMPDDIR/$TMPCTL'"
TMPA="$TMPARCH"
if [ "$TMPA" = "x86_64" ]; then
    TMPA="amd64"
fi
cat <<EOT > "$TMPDIR2/$TMPDDIR/$TMPCTL"
Package: libtidy5
Version: $TMPVER
Section: libs
Priority: optional
Architecture: $TMPA
Depends: libc (>= 6.0.0)
Maintainer: Geoff R. McLane <ubuntu@geoffair.info>
Description: HTML Tidy
 Release version $TMPVER-$TMPARCH
EOT

if [ ! -f "$TMPDIR2/$TMPDDIR/$TMPCTL" ]; then
    echo "$BN: Failed to write '$TMPDIR2/$TMPDDIR/$TMPCTL'!"
    exit 1
fi

if [ -f "$TMPMD5" ]; then
    echo "$BN: Doing: './$TMPMD5 $TMPINST $TMPMD5FIL'"
    ./$TMPMD5 $TMPINST $TMPMD5FIL
    if [ ! "$?" = "0" ]; then
        echo "$BN: Generation of $TMPMD5FIL FAILED!"
        exit 1
    fi
else
    echo "$BN: Warning: $TMPMD5 md5sums generator NOT found!"
fi

if [ -f "$TMPDEB" ]; then
    echo "$BN: Removing last $TMPDEB"
    rm "$TMPDEB"
fi
#####################################
### exit root
### exit
#####################################
cd "$CWD"
echo "$BN: Running 'dpkg-deb --build $TMPDIR2'"
dpkg-deb --build $TMPDIR2
if [ ! "$?" = "0" ]; then
    echo "$BN: dpkg-deb FAILED!"
    exit 1
fi

if [ ! -f "$TMPDEB" ]; then
    echo "$BN: Appears creation of '$TMPDEB' FAILED!"
    exit 1
fi

echo "$BN: Appears a successful DEB build... $TMPDEB"
echo "$BN: Appears a successful DEB build... $TMPDEB" >> "$TMPLOG"
echo "$BN: Doing: 'lintian $TMPDEB'" >> $TMPLOG 2>&1
echo "=========================" >> "$TMPLOG"
lintian $TMPDEB >> $TMPLOG 2>&1
if [ ! "$?" = "0" ]; then
    echo "=========================" >> "$TMPLOG"
    echo "$BN: lintian FAILED. See $TMPLOG"
    exit 1
fi
echo "=========================" >> "$TMPLOG"
echo "$BN: All done... see $TMPLOG"
echo "$BN: All done..." >> "$TMPLOG"
echo "" >> "$TMPLOG"

# eof

