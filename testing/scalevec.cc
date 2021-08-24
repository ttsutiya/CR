#include "../Main.h"
#include "../Local.h"

int main(){
    std::vector<double> v0(3);
    std::vector<double> v(3);

    v0[0] = 1;
    v0[1] = 0;
    v0[2] = 0;

    v[0] = 1;
    v[1] = 1;
    v[2] = 1;

    std::cout << "Mod(v0) = " << VecMod(v0) << std::endl
              << "Mod(v) = "  << VecMod(v) << std::endl;
    
    ScaleVector(v0,v);

    std::cout << "Mod(v0) = " << VecMod(v0) << std::endl
              << "Mod(v) = "  << VecMod(v) << std::endl;
    for(auto i:v) std::cout << i << std::endl;

}
