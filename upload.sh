#!/bin/sh

cd build
make

board="/run/media/$USER/RPI-RP2"

i=0
while [ $i -ne 1 ]
do
    [ -d $board ] && $(cp seha_utils.uf2 $board 2> /dev/null) && i=1
done

echo "done"
