#! /bin/bash

MISC="misc_all.dat"
FILES=$(ls -v ./misc)

echo "#id path phi_p theta_p phi_v theta_v x0 y0 z0 x y z v0x v0y v0z vx vy vz" > $MISC

for i in $FILES; do
    ID=$(echo $i | sed 's/misc_\(.*\).dat/\1/')
    echo $ID $(cat ./misc/$i) >> $MISC
done
