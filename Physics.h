#include "Main.h"

#define c_light 299792458

double PhysInit(int &N, double &t, double &q, double &m, std::vector<double> &pos, 
        std::vector<double> &v, std::vector<double> &B, double &initialB, int &mode,
        bool &stopFlag);
double Lorentz(std::vector<double> &F, const double &q, const std::vector<double> &v,
        const std::vector<double> &B);
double Gyroradius(const double &q, const double &m, const std::vector<double> &v,
        const std::vector<double> &B);
double MagneticField(const std::vector<double> &pos, const std::vector<double> &pos0,
        std::vector<double> &B, const std::vector<double> &B0, const double &initialB,
        const int &mode);
double Frequency(const double &q, const double &m, const std::vector<double> v,
       const std::vector<double> B);
bool SimStop(const std::vector<double> B);
double RelativisticMass(double m, std::vector<double> v);

double PhysInit(int &N, double &t, double &q, double &m, std::vector<double> &pos, 
        std::vector<double> &v, std::vector<double> &B, double &initialB, int &mode,
        bool &stopFlag){

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

            double n;
            switch(lineNumber){
                case 0:
                    ss >> n;
                    N = n;
                    break;
                case 1:
                    ss >> t;
                    break;
                case 2:
                    ss >> q;
                    break;
                case 3:
                    ss >> m;
                    break;
                case 4:
                    ss >> pos[0];
                    break;
                case 5:
                    ss >> pos[1];
                    break;
                case 6:
                    ss >> pos[2];
                    break;
                case 7:
                    ss >> v[0];
                    break;
                case 8:
                    ss >> v[1];
                    break;
                case 9:
                    ss >> v[2];
                    break;
                case 10:
                    ss >> B[0];
                    break;
                case 11:
                    ss >> B[1];
                    break;
                case 12:
                    ss >> B[2];
                    break;
                case 13:
                    ss >> initialB;
                    break;
                case 14:
                    ss >> mode;
                    break;
                case 15:
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

double MagneticField(const std::vector<double> &pos, const std::vector<double> &pos0, std::vector<double> &B, const std::vector<double> &B0, const double &initialB, const int &mode){
    
    double r = AbsDistance(pos);
   
    if(mode == 0){

        B[0] = B0[0];
        B[1] = B0[1];
        B[2] = B0[2];
           
    }else if(mode == 1){
        B[0] = B0[0] / (r);
        B[1] = B0[1] / (r);
        B[2] = B0[2] / (r);

     }else if(mode == 2){

        B[0] = B0[0] / pow(r,2);
        B[1] = B0[1] / pow(r,2);
        B[2] = B0[2] / pow(r,2);

     }else if(mode == 3){

        B[0] =  (3*initialB * pos[0] * pos[2]) / pow(r,5);
        B[1] =  (3*initialB * pos[1] * pos[2]) / pow(r,5);
        B[2] =  (initialB * (3*pow(pos[2],2) - pow(r,2))) / pow(r,5);

     }

     return 0;
}

double Frequency(const double &q, const double &m, const std::vector<double> v,
       const std::vector<double> B){

    double f;
    double B_mod;
    
    B_mod = VecMod(B);

    f = (q * B_mod) / (m * 2*pi);
    
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
    std::cout << "% (v_mod / c) = " << 100*(v_mod/c_light) << std::endl;
    double gamma = 1 / (sqrt(1 - pow(v_mod,2) / pow(c_light,2)));

    return m*gamma;
}
