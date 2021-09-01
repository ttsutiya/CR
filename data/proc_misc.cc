#include "../Main.h"
#include "../Local.h"

int main(){
    std::ifstream misc("misc_all.dat");

    if(!misc.is_open()){
        std::cerr << "Couldn't open misc_all.dat file." << std::endl;
        exit(EXIT_FAILURE);
    }

    int id;
    double path;
    double phi_p, theta_p;
    double phi_v, theta_v;
    double x0, y0, z0;
    double x, y, z;
    double v0x, v0y, v0z;
    double vx, vy, vz;

    std::string line;
    std::getline(misc,line);    //throw away first line (commented)

    while(std::getline(misc,line)){
        if(line.empty()) break;
        std::stringstream ss(line);

        ss >> id >> path 
             >> phi_p >> theta_p
             >> phi_v >> theta_v
             >> x0 >> y0 >> z0
             >> x >> y >> z
             >> v0x >> v0y >> v0z
             >>vx >> vy >> vz;
    
    //################################################################################
    //  theta e phi de chegada com relação ao z=0
    
        double arrive_phi, arrive_theta;
        double v_xy = sqrt( pow(vx,2) + pow(vy,2) );
        double v = sqrt( pow(vx,2) + pow(vy,2) + pow(vz,2) );
    
        arrive_phi = atan2( vy, vx ) * RAD2DEG;
        arrive_theta = acos( (pow(vx,2) + pow(vy,2)) / (v * v_xy) ) * RAD2DEG;
    
    //################################################################################        
    //  metrica para comprar distancia absoluta com o valor de path
    
        double relative_path;
        double absolute_dist = sqrt( pow(x-x0,2) + pow(y-y0,2) + pow(z-z0,2) );
    
        relative_path = 100 * (path - absolute_dist) / absolute_dist;
    
    //################################################################################
    // Desvio de v em relação a v0
    
        double deviation;
        double dot = v0x * vx + v0y * vy + v0z * vz;

        double mod_v0 = sqrt( pow(v0x,2) + pow(v0y,2) + pow(v0z,2) );
        double mod_v = sqrt( pow(vx,2) + pow(vy,2) + pow(vz,2) );

        double mod = mod_v0 * mod_v;

//for some reason if (mod == dot) the division will give something near but greater
//than 1, making acos(>1) give me Nan
//this is a workaround
        double div = dot/mod;

        if(div > 1){
            div = 1;
        }

        deviation = acos( div ) * RAD2DEG;

    //################################################################################
   
        std::cout << arrive_phi << " " << arrive_theta << " " << relative_path << " " << deviation << std::endl;
    }
}
