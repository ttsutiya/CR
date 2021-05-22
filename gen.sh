#! /bin/bash

rm data/*.dat 2> /dev/null

if ! g++ genconfig.cc -o genconfig
then
    echo "Error compiling genconfig.cc"
    exit;
fi

for ((N=1; N<=3; N++))
do
    ./genconfig
    ./CR
    mv config config_$N
    mv config_$N data/cfg

    mv data/frequency.dat    data/frequency_$N.dat
    mv data/magfield.dat     data/magfield_$N.dat
    mv data/pos.dat          data/pos_$N.dat
    mv data/rad.dat          data/rad_$N.dat
    mv data/misc.dat         data/misc_$N.dat

    mv data/frequency_$N.dat data/freq
    mv data/magfield_$N.dat  data/mag
    mv data/pos_$N.dat       data/pos
    mv data/rad_$N.dat       data/rad
    mv data/misc_$N.dat  data/misc
    
done

