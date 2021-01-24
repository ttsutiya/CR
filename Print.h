#include "Main.h"

void printPos(const int &N, const double &t,  const std::vector<double> &maxValues,
        const std::vector<double> &minValues, 
        const std::vector<std::vector<double>> &posOut){
    std::ofstream pos("pos.dat");
    //N
    //Max x Max y Max z Min x Min y Min z
    //time x y z 
    
    pos << N << std::endl;
    
    for(int i=0; i<3; i++){
        pos << std::scientific << std::setprecision(10) << maxValues[i] << " ";
    }

    for(int i=0; i<3; i++){
        pos << std::scientific << std::setprecision(10) << minValues[i] << " ";
    }

    pos << std::endl;

    for(int i=0; i<N; i++){
        pos << std::scientific << std::setprecision(10) << i*t <<" ";

        for(int j=0; j<3; j++){
            pos << posOut[i][j] << " ";
        }
        pos << std::endl;
    }

    pos.close();
}

void printRad(const int &N, const double &t, const std::vector<double> radius){
    std::ofstream rad("rad.dat");
    
    double time;

    rad << N << std::endl;

    for(int i = 0; i < N; i++){ 
        time = t*i;

        rad << std::fixed << std::setprecision(10) << time << " "
            << std::scientific << std::setprecision(10) << radius[i] << std::endl;
    }

    rad.close();
}

void printMag(const int &N, const double &t,
        const std::vector<std::vector<double>> &magfield){
    std::ofstream mag("magfield.dat");

    double B_mod;
    double time;

    mag << N << std::endl;

    for(int i=0; i<N; i++){
        time = t*i;
        B_mod= sqrt(pow(magfield[i][0],2) + pow(magfield[i][1],2) + pow(magfield[i][2],2));

        mag << std::fixed << std::setprecision(10) << time << " "
            << std::scientific << std::setprecision(10) << B_mod << std::endl;
        
    }
    
    mag.close();
}

void printFreq(const int &N, const double &t,
        const std::vector<double> &frequency){
    std::ofstream freq("frequency.dat");

    double time;

    freq << N << std::endl;

    for(int i = 0; i < N; i++){ 
        time = t*i;

        freq << std::fixed << std::setprecision(10) << time << " "
             << std::scientific << std::setprecision(10) << frequency[i] << std::endl;
    }

    freq.close();
}
