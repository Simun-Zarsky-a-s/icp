/**
    * Project: ICP 2022/23
    *
    * @brief Pacman like application
    * @file main.cpp
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#include <iostream>
#include "matrix.hpp"
#include <string>
#include "game.cpp"
#include "Sources.h"
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[]) {
    using namespace std;
    //vector<vector<char>> mapa = Resources::get_matrix();
    //print_2D_vector(mapa);

    Sources::argc =argc;
    for(int i =0; i < argc; i++){
        Sources::argv[i]= argv[i];
    }

    int res, res2, res3;
    while(true){
         res = create_window_p(argc, argv);
        if(!res){
             res2 = create_window_g(argc, argv);
            if(!res2){
                res3 = create_window_end(argc, argv);
                if(res3){
                    continue;
                }else{
                    break;
                }
            }
        }
    }


    return 0;

}
