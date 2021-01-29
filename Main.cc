#include "Main.h" 
#include "Local.h"

using std::cout;
using std::endl;

int main(){

    std::cout << "***COSMIC RAYS***\n\n";

    int N;
    double t;
    bool stopFlag;

    double q, m, initialB;
    int mode;

    std::vector<double> pos(3), v(3), B(3);

    PhysInit(N,t,q,m,pos,v,B,initialB,mode,stopFlag);

    std::vector<std::vector<double>> posOut(N, std::vector<double>(3));
    for(int i = 0; i < 3; i++){
        posOut[0][i] = pos[i];
    }

    std::vector<double> pos0(3), v0(3), B0(3);
    for(int i = 0; i < 3; i++){     // Saves the starting values for future use
        pos0[i] = pos[i];
        v0[i] = v[i];
        B0[i] = B[i];
    }

    std::vector<double> maxValues(3), minValues(3);
    for(int i = 0; i < 3; i++){         //Match the values of max and min with 
        maxValues[i] = pos[i];          //the starting values
        minValues[i] = pos[i];
    }

    m = RelativisticMass(m,v);
    std::cout << "mass = " <<  m << std::endl;

    std::vector<double> radius(N);
    std::vector<std::vector<double>> magfield(N,std::vector<double>(3));
    std::vector<double> frequency(N);
    
    for(int i = 0; i < N; i++){         //Main body of the program
                                        //RK4
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
            x2[i] = pos[i] + 0.5 * v1[i] * t;
            v2[i] = v[i] + 0.5 * a1[i] * t;
        }

        MagneticField(x2,B,B0,initialB,mode);
        Lorentz(F,q,v2,B);
        
        for(int i=0; i<3; i++){
            a2[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            x3[i] = pos[i] + 0.5 * v2[i] * t;
            v3[i] = v[i] + 0.5 * a2[i] * t;
        }

        MagneticField(x3,B,B0,initialB,mode);
        Lorentz(F,q,v3,B);
        
        for(int i=0; i<3; i++){
            a3[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            x4[i] = pos[i] + v3[i] * t;
            v4[i] = v[i] + a3[i] * t;
        }

        MagneticField(x4,B,B0,initialB,mode);
        Lorentz(F,q,v4,B);
        
        for(int i=0; i<3; i++){
            a4[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            pos[i] += (t/6) * (v1[i] + 2*v2[i] + 2*v3[i] + v4[i]);
        }

        for(int i=0; i<3; i++){
            v[i] += (t/6) * (a1[i] + 2*a2[i] + 2*a3[i] + a4[i]);
        }

//###########
//RK4

        radius[i] = Gyroradius(q,m,v,B);
        frequency[i] = Frequency(q,m,v,B);

        for(int j = 0; j < 3; j++){
            magfield[i][j] = B[j];
        }

        for(int j = 0; j < 3; j++){
            if(pos[j] != pos[j]){       //comparing two nan value is false
                std::cout << "Nan value" << std::endl;
                std::cout << "i = " << i << std::endl;
                return 1;
            }
            posOut[i][j] = pos[j];
        }

        for(int i = 0; i < 3; i++){
            maxValues[i] = Max(maxValues[i],pos[i]);
            minValues[i] = Min(minValues[i],pos[i]);
        }

        if(stopFlag){
            if(SimStop(B)){
                std::cout << "SimStop Trigered" << std::endl;
                N = i;
                std::cout << " N = " << i << std::endl;
                break;
            }
        }
    }

//Print values to .dat files

    printPos(N, t, maxValues, minValues, posOut);
    printRad(N, t, radius);
    printMag(N, t, magfield);
    printFreq(N, t, frequency);

    return 0;
}
