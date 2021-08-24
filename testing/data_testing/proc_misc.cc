#include "../../Main.h"
#include "../../Local.h"

int main(){
    std::ifstream misc("misc_all.dat");

    if(!misc.is_open()){
        std::cerr << "Couldn't open misc_all.dat file." << std::endl;
        exit(EXIT_FAILURE);
    }

    int id;
    double path;
    double phi, theta;
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
             >> phi >> theta 
             >> x0 >> y0 >> z0
             >> x >> y >> z
             >> v0x >> v0y >> v0z
             >>vx >> vy >> vz;
    
//        std::cout << id << " " << path << " "
//                  << phi << " " << theta << " " 
//                  << x0 << " " << y0 << " " << z0 << " "
//                  << x << " " << y << " " << z << " "
//                  << v0x << " " << v0y << " " << v0z << " "
//                  << vx << " " << vy << " " << vz << " "
//                  << std::endl;
    
    //################################################################################
    //  theta e phi de chegada com relação ao z=0
    
        double arrive_phi, arrive_theta;
        double v_xy = sqrt( pow(vx,2) + pow(vy,2) );
        double v = sqrt( pow(vx,2) + pow(vy,2) + pow(vz,2) );
    
        arrive_phi = acos( vx / v_xy ) * RAD2DEG;
        arrive_theta = acos( (pow(vx,2) + pow(vy,2)) / (v * v_xy) ) * RAD2DEG;
    
    //################################################################################        
    //  metrica para comprar distancia absoluta com o valor de path
    
        double relative_path;
        double absolute_dist = sqrt( pow(x-x0,2) + pow(y-y0,2) + pow(z-z0,2) );
    
        relative_path = (path - absolute_dist) / absolute_dist;
    
    //################################################################################
    // Desvio de v em relação a v0 (?)
    
        double variation;
        variation = v0x * vx + v0y * vy + v0z * vz;
    
    //################################################################################
    
        std::cout << arrive_phi << " " << arrive_theta << " " << relative_path << " " << variation << std::endl;
    }
}
