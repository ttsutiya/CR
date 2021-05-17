#include "Main.h"

#define PI 3.141592654
#define RAD2DEG (180/PI)
#define DEG2RAD (PI/180)

double Max(double a, double b);
double Min(double a, double b);
double VecMod(const std::vector<double> &vec);
double CrossProduct(std::vector<double> &c, const std::vector<double> &a,
        const std::vector<double> &b);
double DotProduct(const std::vector<double> &a, const std::vector<double> &b);
double VecAngle(const std::vector<double> &pos0, const std::vector<double> &pos);
double Decomposition(const std::vector<double> &v, const std::vector<double> &B,
        std::vector<double> &v_par, std::vector<double> &v_per);
double AbsDistance(const std::vector<double> &pos);

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

double VecMod(const std::vector<double> &vec){
        double mod;

        mod = sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));

        return mod;
}

double CrossProduct(std::vector<double> &c, const std::vector<double> &a,
        const std::vector<double> &b){

    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];

    return 0;
}

double DotProduct(const std::vector<double> &a, const std::vector<double> &b){

    double c = a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; 

    return c;
}

double VecAngle(const std::vector<double> &pos0, const std::vector<double> &pos){
    double angle;
    double dot,A,B;

    dot = DotProduct(pos0,pos);
    A = VecMod(pos0);
    B = VecMod(pos);

    angle = acos( dot / (A*B) );

    return angle * RAD2DEG;
}

double Decomposition(const std::vector<double> &v, const std::vector<double> &B, std::vector<double> &v_par, std::vector<double> &v_per){

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

double AbsDistance(const std::vector<double> &pos){
    double absDist;

    absDist = VecMod(pos);

    return absDist;
}
