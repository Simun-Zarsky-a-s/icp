/**
    * Project: ICP 2022/23
    *
    * @brief Pacman like application
    * @file main.cpp
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#include "game.cpp"
#include "Sources.h"


int main(int argc, char *argv[]) {
    using namespace std;
    //vector<vector<char>> mapa = Resources::get_matrix();
    //print_2D_vector(mapa);

    Sources::game =true;
    while(Sources::game){
        Sources::game =false;
        Sources::number_of_lives = 1;
        create_window_p(argc, argv);
        if(Sources::game){
            Sources::game =false;
            create_window_g(argc, argv);
            if(Sources::game){
                Sources::game =false;
                create_window_end(argc, argv);
                if(Sources::game){
                    continue;
                }else{
                    break;
                }
            }
        }
    }


    return 0;

}
