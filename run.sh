#! /bin/bash

if ! g++ Main.cc -o CR
then
    echo "Compiling error exiting script"
    exit;
else
    if ./CR
    then
        echo "Running ROOT"
        #root PlotPosition.cc #PlotMagField.cc PlotFrequency.cc PlotRadius.cc
        #root  PlotX.cc PlotY.cc PlotZ.cc
    fi

fi

