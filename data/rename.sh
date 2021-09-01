#! /bin/bash

CFG=$(ls -v ./cfg)
MISC=$(ls -v ./misc)

mkdir cfg_renamed
mkdir misc_renamed

N=2636
for i in $CFG; do
    ID=$(echo $i | sed 's/config_\(.*\)/\1/')
    cp ./cfg/config_$ID ./cfg_renamed/config_$N
    cp ./misc/misc_$ID.dat ./misc_renamed/misc_$N.dat
    ((N++))
done
