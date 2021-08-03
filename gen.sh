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

NUMBERSIM=2
for ((N=1; N<=$NUMBERSIM; N++))
do
    ./genconfig

    if ./CR
    then
        mv config           config_$N
        #mv frequency.dat    frequency_$N.dat
        #mv magfield.dat     magfield_$N.dat
        #mv pos.dat          pos_$N.dat
        #mv rad.dat          rad_$N.dat
        mv misc.dat         misc_$N.dat

        mv config_$N        data/cfg
        #mv frequency_$N.dat data/freq
        #mv magfield_$N.dat  data/mag
        #mv pos_$N.dat       data/pos
        #mv rad_$N.dat       data/rad
        mv misc_$N.dat      data/misc
        echo "$N/$NUMBERSIM"
    else
        ((N--))
        echo "$N/$NUMBERSIM"
    fi
done
