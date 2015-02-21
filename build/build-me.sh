#!/bin/sh
#< build-me.sh for cpack-test project - 20150221
#
BN=`basename $0`
TMPINST="$HOME/projects/install/cpack-test"

echo "$BN: building cpack-test project..."

cmake .. -DCMAKE_INSTALL_PREFIX=$TMPINST
if [ ! "$?" = "0" ]; then
    echo "$BN: cmake config, generation error!"
    exit 1
fi

make
if [ ! "$?" = "0" ]; then
    echo "$BN: make error!"
    exit 1
fi

echo ""
echo "$BN: Appears a successful build..."
echo "$BN: Time for 'make install' which will install product into $TMPINST"
echo ""

# eof

