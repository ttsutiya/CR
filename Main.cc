#include "Main.h" 
#include "Local.h"

int main(){

    cout << "***COSMIC RAYS***\n\n";

    int N;
    double t;
    bool stopFlag;

    double max_values[3], min_values[3];
    double q, m, pos[3], v[3], B[3], initialB;
    double SV_pos[3], SV_v[3], SV_B[3];
    int mode;

    PhysInit(N,t,q,m,pos,v,B,initialB,mode,stopFlag);

    double pos_out[N][3];
    double radius[N];
    double magfield[N][3];
    double frequency[N];


//----------------------------------------------------------------------------------------------------
//  Core 
  
    for(int i = 0; i < 3; i++){
        pos_out[0][i] = pos[i];
    }

    for(int i = 0; i < 3; i++){     // Saves the starting values for future use
        SV_pos[i] = pos[i];
        SV_v[i] = v[i];
        SV_B[i] = B[i];
    }

    for(int i = 0; i < 3; i++){     //  Match the values of max and min with the startin values
        max_values[i] = pos[i];
        min_values[i] = pos[i];
    }

    m = RelativisticMass(m,v);
    cout << "mass = " <<  m << endl;

////            cout << " test = " << v[0] <<" ";
    for(int i = 0; i < N; i++){
//        if(i < 10){
//            cout << " testinside = " << v[0] <<" ";
//        }

//RK4
//###########

        double F[3];
        double x1[3],x2[3],x3[3], x4[3];
        double v1[3],v2[3],v3[3], v4[3];
        double a1[3],a2[3],a3[3], a4[3];

        for(int i=0; i<3; i++){
            x1[i] = pos[i];
            v1[i] = v[i];
//            cout << v[i] <<" ";
        }
 //       cout << endl;

        MagneticField(x1,SV_pos,B,SV_B,initialB,mode);
        Lorentz(F,q,v1,B);

        for(int i=0; i<3; i++){
            a1[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            x2[i] = pos[i] + 0.5 * v1[i] * t;
            v2[i] = v[i] + 0.5 * a1[i] * t;
        }

        MagneticField(x2,SV_pos,B,SV_B,initialB,mode);
        Lorentz(F,q,v2,B);
        
        for(int i=0; i<3; i++){
            a2[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            x3[i] = pos[i] + 0.5 * v2[i] * t;
            v3[i] = v[i] + 0.5 * a2[i] * t;
        }

        MagneticField(x3,SV_pos,B,SV_B,initialB,mode);
        Lorentz(F,q,v3,B);
        
        for(int i=0; i<3; i++){
            a3[i] = F[i]/m;
        }

        for(int i=0; i<3; i++){
            x4[i] = pos[i] + v3[i] * t;
            v4[i] = v[i] + a3[i] * t;
        }

        MagneticField(x4,SV_pos,B,SV_B,initialB,mode);
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
                cout << "Nan value" << endl;
                cout << "i = " << i << endl;
                return 1;
            }
            pos_out[i][j] = pos[j];
        }

        for(int i = 0; i < 3; i++){
            max_values[i] = Max(max_values[i],pos[i]);
            min_values[i] = Min(min_values[i],pos[i]);
        }

        if(stopFlag){
            if(SimStop(B)){
                cout << "SimStop Trigered" <<endl;
                N = i;
                cout << " N = " << i << endl;
                break;
            }
        }
    }

//Print values to .dat files

    print_pos(N, t, max_values, min_values, pos_out);
    print_rad(N, t, radius);
    print_mag(N, t, magfield);
    print_freq(N, t, frequency);

    return 0;
}
