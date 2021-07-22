#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

int main(){
    double c = 299792458;
    double m0 = 1.67e-27;
    double E = 1e7;
    double v;

    // test = 1 always
    //double test = 1 - pow( m0*pow(c,2)/2 ,2); 
    //cout << test << endl;
    
    //for(int i=E; i > 0; i--){
    //    v = c * sqrt( 1 - pow( (m0*pow(c,2)/i) ,2));
    //    cout << i << " " << v << endl;
    //    
    //    if(v =! c){
    //        cout << "Max energy = " << i << endl;
    //        break;
    //    }
    //}

    cout << std::setprecision(16);

    double percent = 0.99; 
    double v_old;

    for(int i=3; ; i++){ 
        percent += 9.0/pow(10,i);

        v = percent * c;         
        cout << "%" << percent * 100 << " " << "v = " << v << endl;

        if(v >= c){
            v = v_old;
            cout << "v = " << v << endl;
            break;
        }

        v_old = v;
    }

    //double test0 = 1-pow(v/c,2);
    //cout << test0<< endl;

    //double test = sqrt(1-pow(v/c,2));
    //cout << test << endl;
    //double test1 = m0*pow(c,2);
    //cout << test1 << endl;

    E = m0*pow(c,2) / sqrt(1-pow(v/c,2));
    cout << "Energy = " << E << endl;


}
