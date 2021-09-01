#! /bin/bash

FOLDER="$(ls -v cfg)"

for i in $FOLDER; do
    ID=$(echo $i | sed 's/config_\(.*\)/\1/')
    cp ./cfg/config_$ID ../config
    cd ../

    if ! ./CR
    then
        echo "fail config_$ID" >> ./data/redo_fail.txt
    fi
    
    rm config
    mv misc.dat ./data/misc/misc_$ID.dat

    echo $ID
    cd data 
done
