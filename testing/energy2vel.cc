#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

const double c = 299792458;
const double ev = 1.6e-19;

double Energy(const double v, const double m0){
    double E;
    E = m0*pow(c,2) / sqrt(1-pow(v/c,2));
    E /= ev;

    return E;
}

int main(){
    double m0 = 1.67e-27;
    double v;

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
    cout << endl << endl;

//############################################################

    double E = Energy(v,m0);

    cout << "Energy = " << E << endl;

//############################################################

    double E1 = E;
    double E3 = E1/10;
    double E2 = E3 * sqrt(10);

//wrong results, the numbers gets too big and it rounds to c
//    v = c * sqrt( 1 - pow( m0*pow(c,2)/E1 ,2) );
//    cout << "Velocity = " << v << endl;
//
//    v = c * sqrt( 1 - pow( m0*pow(c,2)/E2 ,2) );
//    cout << "Velocity = " << v << endl;
//
//    v = c * sqrt( 1 - pow( m0*pow(c,2)/E3 ,2) );
//    cout << "Velocity = " << v << endl;

    double E_old;
    bool flag1, flag2;
    flag1 = 0;
    flag2 = 0;

    v = 299792457.99999;
    E = Energy(v,m0);

    cout << std::scientific;
    cout << "E  = " << E << endl;
    cout << "E1 = " << E1 << endl;
    cout << "E2 = " << E2 << endl;
    cout << "E3 = " << E3 << endl << endl;
    cout << std::fixed;
    cout << std::setprecision(7);

    while(!flag1 || !flag2){
        E = Energy(v,m0);
//        cout << "while E = " << E << endl;

        if( !flag1 && E > E3 ){
            flag1 = 1;

            cout << "E_old  = " << E_old << endl;
            cout << "E3     = " << E3 << endl;
            cout << "E      = " << E << endl;

            cout << "diff% old " << -100*(E_old-E3)/E3 << endl;
            cout << "diff%     " << 100*(E-E3)/E3 << endl;

            cout << "v_old = " << v_old << endl ;
            cout << "v     = " << v << endl << endl;
        }else if( flag1 && E > E2){
            flag2 = 1;

            cout << "E_old  = " << E_old << endl;
            cout << "E2     = " << E2 << endl;
            cout << "E      = " << E << endl;

            cout << "diff% old " << -100*(E_old-E2)/E2 << endl;
            cout << "diff%     " << 100*(E-E2)/E2 << endl;
            cout << "v_old = " << v_old << endl ;
            cout << "v     = " << v << endl << endl;
        }

        v_old = v; 
        E_old = E;

        v+=0.0000001;

        if(flag1 && flag2){
            cout << "done" << endl;
            break;
        }

        if(v > c){ 
            cout << "v > c" << endl;
            break;
        }
    }
    
    cout << "#######iron######" << endl << endl;

    m0 = 9.27e-26;
    v = 299792457.9794888;
    flag1 = flag2 = 0;
    bool flag3 = 0;

    E = Energy(v,m0);

    cout << std::scientific;
    cout << "E  = " << E << endl;
    cout << "E1 = " << E1 << endl;
    cout << "E2 = " << E2 << endl;
    cout << "E3 = " << E3 << endl << endl;
    cout << std::fixed;
    cout << std::setprecision(7);

    while(!flag1 || !flag2 || !flag3){
        E = Energy(v,m0);
//        cout << "while E = " << E << endl;

        if( !flag1 && E > E3 ){
            flag1 = 1;

            cout << "E_old  = " << E_old << endl;
            cout << "E3     = " << E3 << endl;
            cout << "E      = " << E << endl;

            cout << "diff% old " << -100*(E_old-E3)/E3 << endl;
            cout << "diff%     " << 100*(E-E3)/E3 << endl;

            cout << "v_old = " << v_old << endl ;
            cout << "v     = " << v << endl << endl;
        }else if( !flag2 && E > E2 ){
            flag2 = 1;

            cout << "E_old  = " << E_old << endl;
            cout << "E2     = " << E2 << endl;
            cout << "E      = " << E << endl;

            cout << "diff% old " << -100*(E_old-E2)/E2 << endl;
            cout << "diff%     " << 100*(E-E2)/E2 << endl;
            cout << "v_old = " << v_old << endl ;
            cout << "v     = " << v << endl << endl;
        }else if( !flag3 && E > E1){
            flag3 = 1;

            cout << "E_old  = " << E_old << endl;
            cout << "E1     = " << E1 << endl;
            cout << "E      = " << E << endl;

            cout << "diff% old " << -100*(E_old-E1)/E1 << endl;
            cout << "diff%     " << 100*(E-E1)/E1 << endl;

            cout << "v_old = " << v_old << endl ;
            cout << "v     = " << v << endl << endl;
        }

        v_old = v; 
        E_old = E;

        v+=0.0000001;

        if(flag1 && flag2 && flag3){
            cout << "done" << endl;
            break;
        }

        if(v > c){ 
            cout << "v > c" << endl;
            break;
        }
    }


}
