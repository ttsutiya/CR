#include "Main.h"

const double C_LIGHT = 299792458;   //meters
const double AU = 1.49598e11;       //AU in meters
const double PC = 2.06265e5;        //PC in AU
const double unts = PC * AU;        //parsec to meters


double PhysInit(double &finalTime, double &h, double &err, double &q, double &m,
        std::vector<double> &pos, std::vector<double> &v, std::vector<double> &B,
        double &initialB, int &mode, bool &adapFlag, int &stopFlag);
double Lorentz(std::vector<double> &F, const double &q, const std::vector<double> &v,
        const std::vector<double> &B);
double Gyroradius(const double &q, const double &m, const std::vector<double> &v,
        const std::vector<double> &B);
double MagneticField(const std::vector<double> &pos, std::vector<double> &B,
        const std::vector<double> &B0, const double &initialB, const int &mode);
double Frequency(const double &q, const double &m, const std::vector<double> v,
       const std::vector<double> B);
bool SimStop(const std::vector<double> B);
double RelativisticMass(double m, std::vector<double> v);
double ASSModel(double ro, double theta);
double BSSModel(double ro, double theta);
double AModel(double z);

double PhysInit(double &finalTime, double &h, double &err, double &q, double &m,
        std::vector<double> &pos, std::vector<double> &v, std::vector<double> &B,
        double &initialB, int &mode, bool &adapFlag, int &stopFlag){
        
    std::ifstream config("config");

    if(!config.is_open()){
        std::cerr << "Couldn't open config file." << std::endl;

        exit;
    }else{

        std::string line;

        int lineNumber=0;

        while(getline(config, line)){
            line.erase(remove_if(line.begin(), line.end(), isspace),
                                                        line.end());
           
            if(line[0] == '#' || line.empty())
                continue;

            int delimiterPos = line.find("=");
            std::string str = line.substr(delimiterPos + 1);

            std::stringstream ss(str);

            switch(lineNumber){
                case 0:
                    ss >> finalTime;
                    break;
                case 1:
                    ss >> h;
                    break;
                case 2:
                    ss >> err;
                    break;
                case 3:
                    ss >> q;
                    break;
                case 4:
                    ss >> m;
                    break;
                case 5:
                    ss >> pos[0];
                    break;
                case 6:
                    ss >> pos[1];
                    break;
                case 7:
                    ss >> pos[2];
                    break;
                case 8:
                    ss >> v[0];
                    break;
                case 9:
                    ss >> v[1];
                    break;
                case 10:
                    ss >> v[2];
                    break;
                case 11:
                    ss >> B[0];
                    break;
                case 12:
                    ss >> B[1];
                    break;
                case 13:
                    ss >> B[2];
                    break;
                case 14:
                    ss >> initialB;
                    break;
                case 15:
                    ss >> mode;
                    break;
                case 16:
                    ss >> adapFlag;
                    break;
                case 17:
                    ss >> stopFlag;
                    break;
            }
            lineNumber++;
        }

    }

    config.close();

    return 0; 
}

double Lorentz(std::vector<double> &F, const double &q, const std::vector<double> &v,
        const std::vector<double> &B){
        
    std::vector<double> L(3);

    CrossProduct(L,v,B);

    F[0] = q * L[0];
    F[1] = q * L[1];
    F[2] = q * L[2];

    return 0;
}

double Gyroradius(const double &q, const double &m, const std::vector<double> &v,
        const std::vector<double> &B){
    
    double r;
    std::vector<double> v_par(3), v_per(3);
    double v_mod, B_mod;

    Decomposition(v,B,v_par,v_per);
    
    v_mod = VecMod(v_per);
    B_mod = VecMod(B);
     
    r = (m * v_mod) / (q * B_mod);

    return r;
}

double MagneticField(const std::vector<double> &pos, std::vector<double> &B,
        const std::vector<double> &B0, const double &initialB, const int &mode){

    switch(mode){
        case 0:{
            B[0] = B0[0];
            B[1] = B0[1];
            B[2] = B0[2];
            break;
            }

        case 1:{
            double r = AbsDistance(pos);

            B[0] = B0[0] / (r);
            B[1] = B0[1] / (r);
            B[2] = B0[2] / (r);
            break;
            }

        case 2:{
            double r = AbsDistance(pos);

            B[0] = B0[0] / pow(r,2);
            B[1] = B0[1] / pow(r,2);
            B[2] = B0[2] / pow(r,2);
            break;
            }

        case 3:{
            double r = AbsDistance(pos);

            B[0] =  (3*initialB * pos[0] * pos[2]) / pow(r,5);
            B[1] =  (3*initialB * pos[1] * pos[2]) / pow(r,5);
            B[2] =  (initialB * (3*pow(pos[2],2) - pow(r,2))) / pow(r,5);
            break;
            }

        case 4:{
            double ro = sqrt( pow(pos[0],2) + pow(pos[1],2) );
            double theta = atan2(-pos[1],pos[0]);
            double Bsp, Zscale, Bro, Btheta;
            
            Bsp = ASSModel(ro,theta);
            Zscale = AModel(pos[2]);

            Bro = Bsp * sin(ro) * Zscale;
            Btheta = Bsp * cos(ro) * Zscale;

            B[0] = Bro * cos(theta) - Btheta * sin(theta);
            B[1] = -( Bro * sin(theta) + Btheta * cos(theta) );
            B[2] = 0;
            break;
            }

        case 5:{
            double ro = sqrt( pow(pos[0],2) + pow(pos[1],2) );
            double theta = atan2(-pos[1],pos[0]);
            double Bsp, Zscale, Bro, Btheta;
            
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
    return 0;
}

double Frequency(const double &q, const double &m, const std::vector<double> v,
       const std::vector<double> B){

    double f;
    double B_mod;
    
    B_mod = VecMod(B);

    f = (q * B_mod) / (m * 2 * PI);
    
    return f;
}

bool SimStop(const std::vector<double> B){
    double B_mod; 

    B_mod = VecMod(B);

    if(B_mod <= 1e-8){
        return true;     
    }else{
        return false;
    }
}

double RelativisticMass(double m, std::vector<double> v){
    double v_mod = sqrt( pow(v[0],2) + pow(v[1],2) + pow(v[2],2));
    std::cout << "% (v_mod / c) = " << 100*(v_mod/C_LIGHT) << std::endl;
    double gamma = 1 / (sqrt(1 - pow(v_mod,2) / pow(C_LIGHT,2)));

    return m*gamma;
}

double ASSModel(double ro, double theta){
    double xi = 10.55e3 * unts;
    double rnaught = 8.5e3 * unts;
    double Bnaught = (3 * rnaught / ro) * pow( tanh(ro / (2 * unts)),3 ) * 1e-10;

    double Bsp = Bnaught * pow( cos( theta - (-5.67) * log(ro/xi) ),2 );

    return Bsp;
}

double BSSModel(double ro, double theta){
    double xi = 10.55e3 * unts;
    double rnaught = 8.5e3 * unts;
    double Bnaught = (3 * rnaught / ro) * pow( tanh(ro / (2 * unts)),3 ) * 1e-10;

    double Bsp = Bnaught * cos( theta - (-5.67) * log(ro/xi) );

    return Bsp;
}

double AModel(double z){
    double z1 = 0.3e3 * unts;
    double z2 = 4e3 * unts;
    double z3 = 20 * unts;

    double Zscale = ( ( 1 / (2 * cosh(z/z1)) ) + ( 1 / (2 * cosh(z/z2) )) ) * tanh(z/z3);

    return Zscale;
}
