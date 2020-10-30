#! /bin/bash

if ! g++ Main.cc -o CR
then
    echo "Compiling error exiting script"
    exit;
fi

    ./CR
    root PlotPosition.cc PlotMagField.cc PlotFrequency.cc PlotRadius.cc
#    root  PlotX.cc PlotY.cc PlotZ.cc
