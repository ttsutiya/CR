#include "../Main.h"
#include "../Local.h"

using namespace std;

int main(){
    int xp,yp;          xp = yp = 100;   //points
    double xd,yd;       xd = yd = 1;    //distance points
    double xstart,ystart;
    vector<vector<double>> arr;
    double norm=0;

    xstart = -xp/2 * xd;
    ystart = yp/2 * yd;

    vector<double> pos(3);      pos[2] = 1e19;
    vector<double> B(3);

    int mode;
//    cout << "Mode:" << endl << "ASS(0)" << endl << "BSS(1)" << endl;
    cin >> mode;
    
    for(double i = ystart; i > -ystart; i-=yd){
        pos[1] = i;

        for(double j = xstart; j < -xstart; j+=xd){
            pos[0] = j;     

            double ro = sqrt( pow(pos[0],2) + pow(pos[1],2) );
            double theta = atan2(-pos[1],pos[0]);
            double Bsp, Zscale, Bro, Btheta;

            switch(mode){
                case 0:{
                    Bsp = ASSModel(ro,theta);
                    Zscale = AModel(pos[2]);

                    Bro = Bsp * sin(-10 * DEG2RAD) * Zscale;
                    Btheta = Bsp * cos(-10 * DEG2RAD) * Zscale;

                    B[0] = Bro * cos(theta) - Btheta * sin(theta);
                    B[1] = -(Bro * sin(theta) + Btheta * cos(theta));
                    B[2] = 0;
                    break;
                }
                case 1:{
                    Bsp = BSSModel(ro,theta);
                    Zscale = AModel(pos[2]);

                    Bro = Bsp * sin(-10 * DEG2RAD) * Zscale;
                    Btheta = Bsp * cos(-10 * DEG2RAD) * Zscale;

                    B[0] = Bro * cos(theta) - Btheta * sin(theta);
                    B[1] = -( Bro * sin(theta) + Btheta * cos(theta) );
                    B[2] = 0;
                    break;
                }
            }
            double mag = sqrt( pow(B[0],2) + pow(B[1],2) );
            if(mag > norm) norm = mag;

            vector<double> tmp;
            tmp.push_back(pos[0]);
            tmp.push_back(pos[1]);
            tmp.push_back(B[0]);
            tmp.push_back(B[1]);

            tmp.push_back(Bro);
            tmp.push_back(Btheta);
            tmp.push_back(theta);

            arr.push_back(tmp);
        }
    }

    norm /= 10;


    for(int i = 0; i < arr.size(); i++){
        cout << arr[i][0] << " " << arr[i][1] << " "
             << arr[i][2] / norm << " " << arr[i][3] / norm << " "
             << arr[i][4] << " " << arr[i][5]  << " " 
             << arr[i][6] * RAD2DEG << endl;
    }

    //cout << pos[0] << " " << pos[1] << " "
    //<< B[0] << " " << B[1] << " " << B[2] << endl;
   
}
