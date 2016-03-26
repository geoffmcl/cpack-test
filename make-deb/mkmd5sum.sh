#!/bin/bash
#< mkmd5sum.sh - 20160326
BN=`basename $0`

TMPDEBUG=0
ADDLINKS=0

TMPCNT=0

if [ "$TMPDEBUG" = "1" ]; then
    TMPDIR="tidy-5.1.47-x86_64/usr"
    TMPFIL="tidy-5.1.47-x86_64/DEBIAN/md5sums"
else
    if [ ! "$#" = "2" ]; then
        echo "$BN: requires two parameters... directory file"
        exit 1
    fi
    TMPDIR="$1"
    TMPFIL="$2"
fi

if [ ! -d "$TMPDIR" ]; then
    echo "$BN: No $TMPDIR to process..."
    exit 1
fi
if [ -f "$TMPFIL" ]; then
    rm -f "$TMPFIL"
fi
if [ -f "$TMPFIL" ]; then
    echo "$BN: FAILED to remove '$TMPFIL'"
    exit 1
fi

cd "$TMPDIR"
TMPLIST="$(find . -type f)"
TMPLINKS="$(find . -type l)"
cd ../..

# echo "$TMPLIST"
if [ ! -z "$TMPLIST" ]; then
    for fil in $TMPLIST; do
        # echo "${fil:2}"
        cd "$TMPDIR"
        cd ..
        TMPMD5="$(md5sum usr/${fil:2})"
        cd ..
        echo "$TMPMD5" >> "$TMPFIL"
        TMPCNT=`expr $TMPCNT + 1`
    done
fi

# echo "$TMPLINKS"
if [ "$ADDLINKS" = "1" ]; then
    if [ ! -z "$TMPLINKS" ]; then
        for fil in $TMPLINKS; do
            # echo "${fil:2}"
            cd "$TMPDIR"
            cd ..
            TMPMD5="$(md5sum usr/${fil:2})"
            cd ..
            echo "$TMPMD5" >> "$TMPFIL"
            TMPCNT=`expr $TMPCNT + 1`
        done
    fi
fi

echo "$BN: Written $TMPCNT entries to $TMPFIL"

if [ "$TMPCNT" = "0" ]; then
    echo "$BN: No entries written!"
    exit 1
fi

exit 0

# eof

