#! /bin/bash

#rm data/*.dat 2> /dev/null

if ! g++ genconfig.cc -o genconfig
then
    echo "Error compiling genconfig.cc"
    exit;
fi

if ! g++ Main.cc -o CR
then
    echo "Compiling error exiting script"
    exit;
fi

for ((N=1; N<=1000; N++))
do
    ./genconfig

    if ./CR
    then
        mv config           config_$N
        mv frequency.dat    frequency_$N.dat
        mv magfield.dat     magfield_$N.dat
        mv pos.dat          pos_$N.dat
        mv rad.dat          rad_$N.dat
        mv misc.dat         misc_$N.dat

        mv config_$N        data/cfg
        mv frequency_$N.dat data/freq
        mv magfield_$N.dat  data/mag
        mv pos_$N.dat       data/pos
        mv rad_$N.dat       data/rad
        mv misc_$N.dat      data/misc
        echo "$N"
    else
        ((N--))
        echo "$N"
    fi
done
