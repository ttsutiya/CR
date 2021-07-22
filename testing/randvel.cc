#include "../Main.h"
#include "../Local.h"

using namespace std;

int main(){
    double velMod = 1;

    double theta    = 135 * DEG2RAD;
    double phi      = 180 * DEG2RAD;

    double vec[3];
    
    vec[0] = -( velMod * sin(theta) * cos(phi) );
    vec[1] = -( velMod * sin(theta) * sin(phi) );
    vec[2] = -( velMod * cos(theta) );

    for(double vel : vec){
        cout << vel << " ";
    }
    cout << endl;
}
