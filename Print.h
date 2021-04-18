#include "Main.h"

void printPos(const std::vector<double> &timeStamp, const std::vector<double> &maxValues,
        const std::vector<double> &minValues, 
            const std::vector<std::vector<double> > &posOut){
    std::ofstream pos("data/pos.dat");                   //N
                                                    //Max x Max y Max z Min x Min y Min z
                                                    //time x y z 
    pos << posOut.size() << std::endl;
    pos << std::scientific << std::setprecision(10);

    
    for(int i=0; i<3; i++){
        pos << maxValues[i] << " ";
    }

    for(int i=0; i<3; i++){
        pos << minValues[i] << " ";
    }

    pos << std::endl;

    for(int i = 0; i < posOut.size(); i++){
        pos << timeStamp[i] << " ";
        for(int j = 0; j < 3; j++){
            pos << posOut[i][j] << " ";
        }
        pos << std::endl;
    }

    pos.close();
}

void printRad(const std::vector<double> &timeStamp,
              const std::vector<double> radius){
    std::ofstream rad("data/rad.dat");
    
    rad << radius.size() << std::endl;
    rad << std::scientific << std::setprecision(10);

    for(int i = 0; i < radius.size(); i++){ 
        rad  << timeStamp[i] << " " << radius[i] << " " << std::endl;
    }

    rad.close();
}

void printFreq(const std::vector<double> &timeStamp,
               const std::vector<double> &frequency){
    std::ofstream freq("data/frequency.dat");

    freq << frequency.size() << std::endl;
    freq << std::scientific << std::setprecision(10);

    for(int i = 0; i < frequency.size(); i++){ 
        freq  << timeStamp[i] << " " << frequency[i] << " " << std::endl;
    }

    freq.close();
}

void printMag(const std::vector<double> &timeStamp,
              const std::vector<std::vector<double> > &magfield){
    std::ofstream mag("data/magfield.dat");

    mag << magfield.size() << std::endl;
    mag << std::scientific << std::setprecision(10);

    double B_mod;

    for(int i = 0; i < magfield.size(); i++){
        mag << timeStamp[i] << " " << VecMod(magfield[i]) << std::endl;
    }
    
    mag.close();
}

void printRadAngle(const std::vector<double> &pos0, const std::vector<double> &pos){
    std::ofstream ra("data/radangle.dat");

    double radius = sqrt( pow(pos[0],2) + pow(pos[1],2) );
    double angle = VecAngle(pos0,pos); 

    ra << angle << " " << radius << std::endl;
}
