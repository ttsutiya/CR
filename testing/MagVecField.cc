#include "../Main.h"
#include "../Local.h"

using namespace std;

int main(){
    int xp,yp;          xp = yp = 600;
    double xd,yd;       xd = yd = 1e9;
    double xstart,ystart;
    vector<vector<double>> arr;
    double norm=0;

    xstart = -xp/2 * xd;
    ystart = yp/2 * yd;

    vector<double> pos(3);      pos[2] = 1e19;
    vector<double> B(3);
    
    for(double i = ystart; i > -ystart; i-=yd){
        pos[1] = i;

        for(double j = xstart; j < -xstart; j+=xd){
            pos[0] = j;     

            double ro = sqrt( pow(pos[0],2) + pow(pos[1],2) );
            double theta = -atan2(pos[1],pos[0]);
            double Bsp, Zscale, Bro, Btheta;

            Bsp = ASSModel(ro,theta);
            Zscale = AModel(pos[2]);

            Bro = Bsp * sin(ro) * Zscale;
            Btheta = Bsp * cos(ro) * Zscale;

            B[0] = Bro * cos(theta) - Btheta * sin(theta);
            B[1] = Btheta * sin(theta) + Btheta * cos(theta);
            B[2] = 0;

            double mag = sqrt( pow(B[0],2) + pow(B[1],2) );
            if(mag > norm) norm = mag;

            vector<double> tmp;
            tmp.push_back(pos[0]);
            tmp.push_back(pos[1]);
            tmp.push_back(B[0]);
            tmp.push_back(B[1]);

            arr.push_back(tmp);
        }
    }

    norm /= 10;


    for(int i = 0; i < arr.size(); i++){
        cout << arr[i][0] << " " << arr[i][1] << " "
             << arr[i][2] / norm << " " << arr[i][3] / norm << endl;
    }

    //cout << pos[0] << " " << pos[1] << " "
    //<< B[0] << " " << B[1] << " " << B[2] << endl;
   
}
