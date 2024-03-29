#include "Main.h"

void printPos(const std::vector<double> &timeStamp, const std::vector<double> &maxValues,
        const std::vector<double> &minValues, 
            const std::vector<std::vector<double> > &posOut){

    std::cout << "Print Pos" << std::endl;
    std::ofstream pos("pos.dat");                   //N
                                                    //Max x Max y Max z Min x Min y Min z
                                                    //time x y z 
    pos << posOut.size() << std::endl;
    pos << std::scientific << std::setprecision(16);

    
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
    std::cout << "Print Rad" << std::endl;
    std::ofstream rad("rad.dat");
    
    rad << radius.size() << std::endl;
    rad << std::scientific << std::setprecision(10);

    for(int i = 0; i < radius.size(); i++){ 
        rad  << timeStamp[i] << " " << radius[i] << " " << std::endl;
    }

    rad.close();
}

void printFreq(const std::vector<double> &timeStamp,
               const std::vector<double> &frequency){
    std::cout << "Print Freq" << std::endl;
    std::ofstream freq("frequency.dat");

    freq << frequency.size() << std::endl;
    freq << std::scientific << std::setprecision(10);

    for(int i = 0; i < frequency.size(); i++){ 
        freq  << timeStamp[i] << " " << frequency[i] << " " << std::endl;
    }

    freq.close();
}

void printMag(const std::vector<double> &timeStamp,
              const std::vector<std::vector<double> > &magfield){
    std::cout << "Print Mag" << std::endl;
    std::ofstream mag("magfield.dat");

    mag << magfield.size() << std::endl;
    mag << std::scientific << std::setprecision(10);

    double B_mod;

    for(int i = 0; i < magfield.size(); i++){
        mag << timeStamp[i] << " " << VecMod(magfield[i]) << std::endl;
    }
    
    mag.close();
}

void printMisc(const double &time, const double &phi_p, const double &theta_p,
               const double &phi_v, const double &theta_v,
               const std::vector<double> &pos0, const std::vector<double> &pos,
               const std::vector<std::vector<double>> &posOut,
               const std::vector<double> v0, const std::vector<double>v){
    std::cout << "Print Misc" << std::endl;
    std::ofstream misc("misc.dat");

    double path = 0;

    for(int i = 1; i < posOut.size(); i++){
        std::vector<double> vec_diff(3);
        
        for(int j = 0; j < 3; j++){
            vec_diff[j] = posOut[i][j] - posOut[i-1][j];
        }

        path += VecMod(vec_diff);
    }

    misc << time << " " 
         << path << " " 
         << phi_p << " " << theta_p << " "
         << phi_v << " " << theta_v << " "
         << pos0[0] << " " << pos0[1] << " " << pos0[2] << " "
         << posOut[posOut.size()-1][0] << " " << posOut[posOut.size()-1][1] << " " << posOut[posOut.size()-1][2] << " " 
         << v0[0] << " " << v0[1] << " " << v0[2] << " "
         << v[0] << " " << v[1] << " " << v[2] << " " 
         << std::endl;

    misc.close();
}
