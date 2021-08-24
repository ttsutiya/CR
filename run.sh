#! /bin/bash

if ! g++ Main.cc -o CR
then
    echo "Compiling error exiting script"
    exit;
else
    if ./CR
    then
        echo "Running ROOT"
        #root plot/PlotPosition.cc #plot/PlotMagField.cc plot/PlotFrequency.cc plot/PlotRadius.cc
        #root  plot/PlotX.cc plot/PlotY.cc plot/PlotZ.cc
    fi

fi

