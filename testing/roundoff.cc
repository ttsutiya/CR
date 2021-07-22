#include"../Main.h"

using namespace std;

int main(){
    cout << setprecision(16);

    double v[3];
    v[0] = 2.0239995562e+08;
    v[1] = 1.3673355885e+08;
    v[2] = -1.7382091279e+08;
    
    for(int i = 0; i<3; i++){
        cout << "v[" << i << "] = " << v[i] << endl;
    }
    cout << endl;

    double v2[3];
    for(int i = 0; i<3; i++){
        v2[i] = pow(v[i],2);
        cout << "v2[" << i << "] = " << v2[i] << endl;
    }
    cout << endl;

    double v_mod=0;
    for(double i : v2){
        v_mod += i ;
    }
    v_mod = sqrt(v_mod);
    cout << "v_mod = " << v_mod << endl;

    v_mod = sqrt( pow(v[0],2) + pow(v[1],2) + pow(v[2],2));
    cout << "v_mod = " << v_mod << endl;

}
