#! /bin/bash

mkdir cfg_filter
mkdir misc_filter

FILES=$(ls -v misc)

for i in $FILES; do
    ID=$(echo $i | sed 's/misc_\(.*\)\.dat/\1/')
    cp ./misc/misc_$ID.dat ./misc_filter/
    cp ./cfg/config_$ID ./cfg_filter/
done
