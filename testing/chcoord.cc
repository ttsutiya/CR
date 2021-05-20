#include "../Local.h"
#include "../Main.h"

using namespace std;

void TransSpheHem(double &velMod, const double &theta, const double &phi, vector<double> &v){
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

int main(){
    double theta        = 90 * DEG2RAD;
    double phi          = 0 * DEG2RAD;

    double theta_gen    = 0 * DEG2RAD;
    double phi_gen      = 0 * DEG2RAD;

    double velMod       = 1;
    vector<double> v(3);

    TransSpheHem(velMod,theta_gen,phi_gen,v); 
    cout << "TransSpheHem: " << endl;
    for(double i : v){
        cout << i << " ";
    }
    cout << endl << endl;

    TransSpheCart(v,theta,phi);
    cout << "TransSpheCart: " << endl;

    for(double i : v){
        cout << i << " ";
    }
    cout << endl;
}
