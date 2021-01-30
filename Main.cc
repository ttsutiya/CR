#include "Main.h" 
#include "Local.h"

using std::cout;
using std::endl;

int main(){

    std::cout << "***COSMIC RAYS***\n\n";

    double finalTime, h;
    bool stopFlag;

    double q, m, initialB;
    int mode;

    std::vector<double> pos(3), v(3), B(3);

    PhysInit(finalTime,h,q,m,pos,v,B,initialB,mode,stopFlag);

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

//#############################################################################
//                  Store intitial values of the metrics
//#############################################################################

    MagneticField(pos,B,B0,initialB,mode);

    std::vector<double> timeStamp(1);
    timeStamp[0] = 0;

    std::vector<std::vector<double>> posOut(1, std::vector<double>(3));
    for(int i = 0; i < 3; i++){
        posOut[0][i] = pos[i];
    }

    std::vector<double> radius(1);
    radius[0] = Gyroradius(q,m,v,B);

    std::vector<std::vector<double>> magfield(1, std::vector<double>(3));
    for(int i = 0; i < 3; i++){
        magfield[0][i] = B[i];
    }

    std::vector<double> frequency(1);
    frequency[0] = Frequency(q,m,v,B);

//#############################################################################
//                               RK4
//#############################################################################

    for(double time = 0; time <= finalTime;){         

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

        std::vector<double> temp(3);    //temporary vec to be used to push
                                        //into vector of vectors
        for(int i = 0; i < 3; i++){
            if(pos[i] != pos[i]){       //comparing two nan value is false
                std::cout << "Nan value" << std::endl;
                return 1;
            }
            
            temp[i] = pos[i];
        }
        posOut.push_back(temp);

        radius.push_back(Gyroradius(q,m,v,B));
        frequency.push_back(Frequency(q,m,v,B));

        for(int i = 0; i < 3; i++){
            temp[i] = B[i];
        }
        magfield.push_back(temp);

        for(int i = 0; i < 3; i++){
            maxValues[i] = Max(maxValues[i],pos[i]);
            minValues[i] = Min(minValues[i],pos[i]);
        }

        if(stopFlag){
            if(SimStop(B)){
                std::cout << "SimStop Trigered" << std::endl;
                break;
            }
        }

        time += h;
        timeStamp.push_back(time);
        cout << "time = " << time << endl;
    }

//#############################################################################
//                      Print values to .dat files
//#############################################################################

    printPos(timeStamp, maxValues, minValues, posOut);
    printRad(timeStamp, radius);
    printFreq(timeStamp, frequency);
    printMag(timeStamp, magfield);

    return 0;
}
