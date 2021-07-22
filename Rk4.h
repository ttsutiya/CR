#include "Main.h"

//#############################################################################
//          Runge Kutta 4 Method
//#############################################################################

void Rk(std::vector<double> &pos, std::vector<double> &v,
         std::vector<double> &B, const std::vector<double> &B0,
         const double &initialB, const int mode,
         const double &q, const double &m, const double &h){

    std::vector<double> F(3);
    std::vector<double> x1(3),x2(3),x3(3), x4(3);
    std::vector<double> v1(3),v2(3),v3(3), v4(3);
    std::vector<double> a1(3),a2(3),a3(3), a4(3);

    for(int i=0; i<3; i++){
        x1[i] = pos[i];
        v1[i] = v[i];
    }

    MagneticField(x1,B,B0,initialB,mode);
    Lorentz(F,q,v1,B);
    
    for(int i=0; i<3; i++){
        a1[i] = F[i]/m;
    }

    for(int i=0; i<3; i++){
        x2[i] = pos[i] + 0.5 * v1[i] * h;
        v2[i] = v[i] + 0.5 * a1[i] * h;
    }

    MagneticField(x2,B,B0,initialB,mode);
    Lorentz(F,q,v2,B);
    
    for(int i=0; i<3; i++){
        a2[i] = F[i]/m;
    }

    for(int i=0; i<3; i++){
        x3[i] = pos[i] + 0.5 * v2[i] * h;
        v3[i] = v[i] + 0.5 * a2[i] * h;
    }

    MagneticField(x3,B,B0,initialB,mode);
    Lorentz(F,q,v3,B);
    
    for(int i=0; i<3; i++){
        a3[i] = F[i]/m;
    }

    for(int i=0; i<3; i++){
        x4[i] = pos[i] + v3[i] * h;
        v4[i] = v[i] + a3[i] * h;
    }

    MagneticField(x4,B,B0,initialB,mode);
    Lorentz(F,q,v4,B);
    
    for(int i=0; i<3; i++){
        a4[i] = F[i]/m;
    }

    for(int i=0; i<3; i++){
        pos[i] += (h/6) * (v1[i] + 2*v2[i] + 2*v3[i] + v4[i]);
    }

    for(int i=0; i<3; i++){
        v[i] += (h/6) * (a1[i] + 2*a2[i] + 2*a3[i] + a4[i]);
    }
}

//#############################################################################
//                 Error of the method 
//#############################################################################

double RkErr(const std::vector<double> &x1, const std::vector<double> &x2){
    std::vector<double> error(3);

    for(int i = 0; i < 3; i++){
        error[i] = (1.0/30) * (std::abs(x1[i] - x2[i]));
    }

    double sum=0;
    for(int i = 0; i < 3; i++){
        sum += pow(error[i],2);
    }

    return sqrt(sum);
}

//#############################################################################
//                  Compare with config precision 
//                  See: Comptational Physics by Mark Newman page 358
//#############################################################################

int RkCompare(const std::vector<double> &x1, const std::vector<double> &x2,
              double &h, const double &err){

    double epsolon = RkErr(x1,x2);

    double ro = err / epsolon;
    
    double newH = h * pow(ro,(1.0/4));

    if(newH > 2 * h){       //limit in case epsolon is too small
        newH = 2 * h;
    }
    
    h = newH;       //new step size

    if(ro >= 1){
        return 0;
    }else{
        return 1;
    }
}
