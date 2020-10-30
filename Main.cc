#include "Main.h" 


int main(){

    cout << "***COSMIC RAYS***\n\n";

    int N;
    double t;
    bool SimStop_flag;

    double max_values[3], min_values[3];
    double q, m, pos[3], v0[3], B[3], initialB;
    double SV_pos[3], SV_v[3], SV_B[3];
    double F[3], v[3], a[3];
    int mode;

    PhysInit(N,t,q,m,pos,v0,B,initialB,mode,SimStop_flag);

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
        SV_v[i] = v0[i];
        SV_B[i] = B[i];
    }

    for(int i = 0; i < 3; i++){     //  Match the values of max and min with the startin values
        max_values[i] = pos[i];
        min_values[i] = pos[i];
    }

    for(int i = 0; i < N; i++){

//        cout << i << "/" << N << endl; //counter

        MagneticField(pos,SV_pos,B,SV_B,initialB,mode);
        Lorentz(F,q,v0,B);
        Acceleration(a,F,m);
        Velocity(t,v,v0,a);
        VelocityCorrection(v,v0,B);
        Trajectory(t,pos,v,a);

        radius[i] = Gyroradius(q,m,v,B);
        frequency[i] = Frequency(q,m,v,B);

        for(int j = 0; j < 3; j++){
            magfield[i][j] = B[j];
        }

        for(int j = 0; j < 3; j++){
            pos_out[i][j] = pos[j];
        }

        for(int i = 0; i < 3; i++){
            max_values[i] = Max(max_values[i],pos[i]);
            min_values[i] = Min(min_values[i],pos[i]);
        }

        for(int i = 0; i < 3; i++){
            v0[i] = v[i];
        }

        if(SimStop_flag){
            if(SimStop(B)){
                cout << "SimStop Trigered" <<endl;
                N = i;
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
