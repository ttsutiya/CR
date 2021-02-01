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

    for(double time = h; time <= finalTime;){         

        Rk4(pos,v,B,B0,initialB,mode,q,m,h);
        
//        if(adapCounter == 0){
//            adapCounter++;
//        }else if(adapCounter == 1){
//
//            adapCounter = 0;
//        }

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

        timeStamp.push_back(time);
        time += h;
        cout << "time = " << time << endl;
    }
    cout << "time.size() = " << timeStamp.size() << endl;

//#############################################################################
//                      Print values to .dat files
//#############################################################################

    printPos(timeStamp, maxValues, minValues, posOut);
    printRad(timeStamp, radius);
    printFreq(timeStamp, frequency);
    printMag(timeStamp, magfield);

    return 0;
}
