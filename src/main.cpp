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

    Sources::game =true; //start app
    while(Sources::game){

        Sources::game =false;
        Sources::number_of_lives = 1;
        create_window_p(argc, argv); //create welcome window
        if(Sources::game){ //start game
            Sources::game =false;
            create_window_g(argc, argv);//create game window
            if(Sources::game){ //end of game
                Sources::game =false;
                create_window_end(argc, argv);//create end window
                if(Sources::game){
                    continue; //continue game
                }else{
                    break; //end app
                }
            }
        }
    }

    return 0;

}
