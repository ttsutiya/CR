#include "Main.h"
#include "Local.h"
#include <random>
#include <chrono>

using namespace std;

//Random generate position of the particle inside 
//the top dome of a sphere of radius 52850 LY ~ 5e20 m
void Rand(double &theta, double &phi){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed); 

    uniform_real_distribution<double> randtheta(0,PI/2);
    theta = randtheta(generator);
     
    uniform_real_distribution<double> randphi(0,2*PI);
    phi = randphi(generator);
}

void RandPos(vector<double> &pos, double &theta, double &phi){
    Rand(theta,phi);

    cout << "theta[deg] = " << theta * RAD2DEG << endl 
         << "phi[deg] = " << phi * RAD2DEG << endl;
    double r = 5e20;

    pos[0] = r * sin(theta) * cos(phi);
    pos[1] = r * sin(theta) * sin(phi);
    pos[2] = r * cos(theta);
}

void TransSpheHem(const double &velMod, const double &theta, const double &phi, vector<double> &v){
    v[0] =  velMod * cos(theta);
    v[1] =  velMod * ( sin(theta) * cos(phi) );
    v[2] =  velMod * ( sin(theta) * sin(phi) ); 
}

void TransSpheCart(vector<double> &v, const double &theta, const double &phi){
    double vx = v[0];
    double vy = v[1];
    double vz = v[2];
    
    v[0] = vx * sin(theta) * cos(phi) + vy * cos(theta) * cos(phi) - vz * sin(phi);
    v[1] = vx * sin(theta) * sin(phi) + vy * cos(theta) * sin(phi) + vz * cos(phi);
    v[2] = vx * cos(theta) - vy * sin(theta);
}

void RandVel(vector<double> &v, const double &theta, const double &phi){
    const double velMod = 2.5e8;

//    velx = -( velMod * sin(theta) * cos(phi) );
//    vely = -( velMod * sin(theta) * sin(phi) );
//    velz = -( velMod * cos(theta) );
    
    double theta_r, phi_r;
    Rand(theta_r,phi_r);

    TransSpheHem(velMod, theta_r, phi_r, v);
    TransSpheCart(v,theta,phi);

    for(auto &i : v){
        i*= -1;
    }
}

void CentVel(vector<double> &v, const double &theta, const double &phi){
    const double velMod = 2.5e8;

    v[0] = -( velMod * sin(theta) * cos(phi) );
    v[1] = -( velMod * sin(theta) * sin(phi) );
    v[2] = -( velMod * cos(theta) );
}

int main(){
    string sdur1 = "#Duration";
    string sdur2 = "# 0 -> no time limit";
    //double finalTime = 1e7;
    double finalTime = 0;

    string sstep = "#Step size";
    double t = 1e-3;

    string serr = "#Error";
    double err = 1e10;

    string spar = "#Particle specifications";
    double charge = 1.6e-19;
    double mass = 1.67e-27;

    string spos = "#Initial position";
    vector<double> pos(3);
    double theta, phi;
    RandPos(pos,theta,phi);

    string svel = "#Initial velocity";
    vector<double> v(3);
    //RandVel(v,theta,phi);
    CentVel(v,theta,phi);

    string smag = "#Constant magnetic field (mode 0/1/2)";
    double magfieldx, magfieldy, magfieldz;
    magfieldx = 0;
    magfieldy = 0;
    magfieldz = 0;

    string sinit = "#B_0 used in the dipole field (mode 3)"; 
    double initialB = 7e8;

    string smode = "#   0 - constant\n"
                   "#   1 - 1/r\n"
                   "#   2 - 1/r^2\n"
                   "#   3 - dipole\n"
                   "#   4 - ASS Model\n"
                   "#   5 - BSS Model";
    int mode = 4;
    
    string sadap = "#Adaptative RK4";
    int adapFlag = 1;
    
    string sstop = "#Stop simulation\n"
                    "#   0 - Disabled\n"
                    "#   1 - Magnitude\n"
                    "#   2 - Z=0";
    int simStop = 2;

//############################################################

    ofstream cfg("config");
    
    cfg << std::scientific << std::setprecision(3);
    cfg  << sdur1 <<"\n" << sdur2 << "\nfinalTime = " << finalTime << "\n\n";
    cfg  << sstep << "\nt = " << t << "\n\n";
    cfg  << serr << "\nerr = " << err << "\n\n";
    cfg  << spar << "\ncharge = " << charge << "\nmass = " << mass << "\n\n";

    cfg << std::scientific << std::setprecision(10);
    cfg  << spos << "\npos(x) = " << pos[0] 
                 << "\npos(y) = " << pos[1]
                 << "\npos(z) = " << pos[2] << "\n\n";
    cfg  << svel << "\nvel(x) = " << v[0] 
                 << "\nvel(y) = " << v[1] 
                 << "\nvel(z) = " << v[2] << "\n\n";
    cfg  << smag << "\nmagfield(x) = " << magfieldx 
                 << "\nmagfield(y) = " << magfieldy
                 << "\nmagfield(z) = " << magfieldz << "\n\n";
    cfg  << sinit << "\nintialB = " << initialB << "\n\n";
    cfg  << smode << "\nmode = " << mode << "\n\n";
    cfg  << sadap << "\nadapFlag = " << adapFlag << "\n\n";
    cfg  << sstop << "\nsimStop = " << simStop << "\n\n";

    cfg.close();
}
