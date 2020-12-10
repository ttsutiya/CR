#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define c_light 299792458

double PhysInit(int &N, double &t, double &q, double &m, double pos[3], double v[3], double B[3], double &initialB, int &mode, bool &SimStop_flag){

    //ugly implementation**************************
    
    ifstream config("config");

    if(config.is_open()){

        string str;
        double arr[16];

        while(getline(config, str, '=')){
            int i;

            config >> arr[i];

            if(!config){
                break;
            }

            i++;
        }

        N=arr[0];
        t=arr[1];

        q=arr[2];
        m=arr[3];

        pos[0]=arr[4];
        pos[1]=arr[5];
        pos[2]=arr[6];

        v[0]=arr[7];
        v[1]=arr[8];
        v[2]=arr[9];

        B[0]=arr[10];
        B[1]=arr[11];
        B[2]=arr[12];

        initialB=arr[13];
        mode=arr[14];
        SimStop_flag=arr[15];


    }else{
        cerr << "Couldn't open config.dat file." << endl;
        exit(1);
    }

    config.close();

    return 0; 
}

double Lorentz(double F[3], double q, double v[3], double B[3]){
        
    double L[3];

    CrossProduct(L,v,B);

    F[0] = q * L[0];
    F[1] = q * L[1];
    F[2] = q * L[2];

    return 0;
}

double Acceleration(double a[3], double F[3], double m){

    a[0] = F[0]/m;
    a[1] = F[1]/m;
    a[2] = F[2]/m;

    return 0;
}

double Velocity(double t,double v[3], double v0[3], double a[3]){

    v[0] = v0[0]+a[0]*t;
    v[1] = v0[1]+a[1]*t;
    v[2] = v0[2]+a[2]*t;

    return 0;
}

double VelocityCorrection(double v[3], double v0[3], double B[3]){

    double v0_par[3], v0_per[3];
    double v_par[3], v_per[3];

    Decomposition(v0,B,v0_par,v0_per);
    Decomposition(v,B,v_par,v_per);

    double v0_mod = VecMod(v0_per);
    double v_mod = VecMod(v_per);

    double correction = v0_mod / v_mod;

    v_per[0] = correction * v_per[0];
    v_per[1] = correction * v_per[1];
    v_per[2] = correction * v_per[2];

    v[0] = v_par[0] + v_per[0];
    v[1] = v_par[1] + v_per[1];
    v[2] = v_par[2] + v_per[2];

    return 0;
}

double Trajectory(double t,double pos[3], double v[3], double a[3]){
    
    pos[0] = pos[0] + v[0]*t + 0.5*a[0]*pow(t,2);
    pos[1] = pos[1] + v[1]*t + 0.5*a[1]*pow(t,2);
    pos[2] = pos[2] + v[2]*t + 0.5*a[2]*pow(t,2);

    return 0;
}

double Gyroradius(double q, double m, double v[3], double B[3]){
    
    double r;
    double v_par[3], v_per[3];
    double v_mod, B_mod;

    Decomposition(v,B,v_par,v_per);
    
    v_mod = VecMod(v_per);
    B_mod = VecMod(B);
     
    r = (m * v_mod) / (q * B_mod);

    return r;
}

double MagneticField(double pos[3], double SV_pos[3], double B[3], double SV_B[3], double initialB, int mode){
    
    double r = AbsDistance(pos);
   
    if(mode == 0){

        B[0] = SV_B[0];
        B[1] = SV_B[1];
        B[2] = SV_B[2];
           
    }else if(mode == 1){
        B[0] = SV_B[0] / (r);
        B[1] = SV_B[1] / (r);
        B[2] = SV_B[2] / (r);

     }else if(mode == 2){

        B[0] = SV_B[0] / pow(r,2);
        B[1] = SV_B[1] / pow(r,2);
        B[2] = SV_B[2] / pow(r,2);

     }else if(mode == 3){

        B[0] =  (3*initialB * pos[0] * pos[2]) / pow(r,5);
        B[1] =  (3*initialB * pos[1] * pos[2]) / pow(r,5);
        B[2] =  (initialB * (3*pow(pos[2],2) - pow(r,2))) / pow(r,5);

     }

     return 0;
}

double Frequency(double q, double m, double v[3], double B[3]){

    double f;
    double B_mod;
    
    B_mod = VecMod(B);

    f = (q * B_mod) / (m * 2*pi);
    
    return f;
}

bool SimStop(double B[]){
    double B_mod; 

    B_mod = VecMod(B);

    if(B_mod <= 1e-8){
        return true;     
    }else{
        return false;
    }
}

double RelativisticMass(double m, double v[]){

    double v_mod = sqrt( pow(v[0],2) + pow(v[1],2) + pow(v[2],2));
    cout << "% v_mod / c= " << 100*(v_mod/c_light) << endl;
    double gamma = 1 / (sqrt(1 - pow(v_mod,2) / pow(c_light,2)));

    return m*gamma;
}
