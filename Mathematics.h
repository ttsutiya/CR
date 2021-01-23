#include "Main.h"

using namespace std;

#define pi 3.141592654
#define rad2deg (180./pi)

double Max(double a, double b){
double Min(double a, double b){
double VecMod(double Vec[]){
double CrossProduct(double c[3], double a[3], double b[3]){
double DotProduct(double a[3], double b[3]){
double Decomposition(double v[3], double B[3], double v_par[3], double v_per[3]){
double RelDistance(double pos[3], double SV_pos[3]){    //relative distance
double AbsDistance(double pos[3]){      //absolute distance

double Max(double a, double b){
    double max;

    if(a > b){
        max = a;
    }else{
        max = b;
    }

    return max;
}

double Min(double a, double b){
    double min;

    if(a > b){
        min = b;
    }else{
        min = a;
    }

    return min;
}

double VecMod(double Vec[]){
        double mod;

        mod = sqrt(pow(Vec[0],2) + pow(Vec[1],2) + pow(Vec[2],2));

        return mod;
}

double CrossProduct(double c[3], double a[3], double b[3]){

    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];

    return 0;
}

double DotProduct(double a[3], double b[3]){

    double c = a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; 

    return c;
}

double Decomposition(double v[3], double B[3], double v_par[3], double v_per[3]){

    double B_mod;
    
    B_mod = VecMod(B);

    double dp = DotProduct(v,B);

    v_par[0] = dp * B[0] / pow(B_mod,2);
    v_par[1] = dp * B[1] / pow(B_mod,2);
    v_par[2] = dp * B[2] / pow(B_mod,2);

    v_per[0] = v[0] - v_par[0];
    v_per[1] = v[1] - v_par[1];
    v_per[2] = v[2] - v_par[2];

    return 0;
}

double RelDistance(double pos[3], double SV_pos[3]){    //relative distance
        
    double RDist;
    double temp[3];

    for(int i = 0; i<3; i++){
        temp[i] = pos[i]-SV_pos[i];
    }
    
    RDist = VecMod(temp);

    return RDist;
}

double AbsDistance(double pos[3]){      //absolute distance
    
    double ADist;

    ADist = VecMod(pos);

    return ADist;
}
