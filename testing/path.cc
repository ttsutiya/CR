#include "../Local.h"
#include "../Main.h"

using namespace std;

int main(){
    vector<vector<double>> posOut;
    vector<double> tmp(3,0);

    posOut.push_back(tmp);

//    for(int i = 0; i < 3; i++){
//        tmp[i] = 1;
//        cout << tmp[i] << endl;
//    }
//    posOut.push_back(tmp);
//
//    
//    for(int i = 0; i < 3; i++){
//        tmp[i] = 2;
//        cout << tmp[i] << endl;
//    }
//    posOut.push_back(tmp);
//
    tmp[0] = 1; 
    posOut.push_back(tmp);

    tmp[1] = 1;
    posOut.push_back(tmp);

    tmp[0] = 0;
    posOut.push_back(tmp);

    tmp[2] = 1;
    posOut.push_back(tmp);

    for(auto i : posOut){
        for(auto j : i){
            cout << "for test = " << j << endl;
        }
    }

    double path = 0;

    for(int i = 1; i < posOut.size(); i++){
        vector<double> vec_diff(3);
        
        for(int j = 0; j < 3; j++){
            vec_diff[j] = posOut[i][j] - posOut[i-1][j];
            cout << "j = " << j << endl;
        }

        path += VecMod(vec_diff);
    }

    cout << path << endl;
}
