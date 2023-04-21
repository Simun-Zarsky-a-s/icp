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
//#include "game.cpp"



int main(int argc, char *argv[]) {
    using namespace std;
    cout << "Hello, World!" << endl;

    debug_resources("map.txt"); //at the bottom oc matrix.cpp initializes whole resources

    // create_window_p(argc, argv);
    return 0;

}
