#include <iostream>
#include "matrix.hpp"
#include <string>
#include "game.cpp"


int main(int argc, char *argv[]) {
    using namespace std;
    cout << "Hello, World!" << endl;
    int err = print_map("map.txt");
    if(err){
        cout << "Emotional damage" << endl;
    }
    create_window_p(argc, argv);
    return 0;

}
