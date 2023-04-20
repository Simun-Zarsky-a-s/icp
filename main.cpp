#include <iostream>
#include "matrix.hpp"
#include <string>
//#include "game.cpp"


int main(int argc, char *argv[]) {
    using namespace std;
    cout << "Hello, World!" << endl;
    Resources res("map.txt");

    cout << "height :" << res.height << endl; ///debugging data about resources
    cout << "width :" << res.width << endl;
    cout << "ghosts :" << res.ghost_number << endl;
    cout << "keys :" << res.key_number << endl;
    cout << "MAP :"  << endl;
    print_matrix(res.matrix);


    // create_window_p(argc, argv);
    return 0;

}
