#include "../Main.h"
#include "../Local.h"

using namespace std;

int main(){
    vector<double> pos(3);
    pos[0] = 2.5814275053487646e+20;
    pos[1] = 1.9715108120132062e+20;
    pos[2] = 3.8012336356430237e+20;

    double phi,theta;
    double p = sqrt( pow(pos[0],2) + pow(pos[1],2) );


    phi = atan2(pos[1],pos[0]) * RAD2DEG;
    theta = atan2(p,pos[2]) * RAD2DEG;

    cout << "phi = " << phi << endl;
    cout << "theta = " << theta << endl;
    
}
