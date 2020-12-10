#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void print_pos(int N, double t,  double max_values[], double min_values[], double pos_out[][3]){
    ofstream pos("pos.dat");
    //N
    //Max x Max y Max z Min x Min y Min z
    //time x y z 
    
    pos << N << endl;
    
    for(int i=0; i<3; i++){
        pos << scientific << setprecision(10) << max_values[i] << " ";
    }

    for(int i=0; i<3; i++){
        pos << scientific << setprecision(10) << min_values[i] << " ";
    }

    pos << endl;

    for(int i=0; i<N; i++){
        pos << scientific << setprecision(10) << i*t <<" ";

        for(int j=0; j<3; j++){
            pos << pos_out[i][j] << " ";
        }
        pos << endl;
    }

    pos.close();
}

void print_rad(int N, double t, double radius[]){
    ofstream rad("rad.dat");
    
    double time;

    rad << N << endl;

    for(int i = 0; i < N; i++){ 
        time = t*i;

        rad << fixed << setprecision(10) << time << " "
            << scientific << setprecision(10) << radius[i] << endl;
    }

    rad.close();
}

void print_mag(int N, double t, double magfield[][3]){
    ofstream mag("magfield.dat");

    double B_mod;
    double time;

    mag << N << endl;

    for(int i=0; i<N; i++){
        time = t*i;
        B_mod= sqrt(pow(magfield[i][0],2) + pow(magfield[i][1],2) + pow(magfield[i][2],2));

        mag << fixed << setprecision(10) << time << " "
            << scientific << setprecision(10) << B_mod << endl;
        
    }
    
    mag.close();
}

void print_freq(int N, double t, double frequency[]){
    ofstream freq("frequency.dat");

    double time;

    freq << N << endl;

    for(int i = 0; i < N; i++){ 
        time = t*i;

        freq << fixed << setprecision(10) << time << " "
             << scientific << setprecision(10) << frequency[i] << endl;
    }

    freq.close();
}
