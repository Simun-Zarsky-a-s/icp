#include <iostream>
#include "matrix.hpp"
#include <string>

int main() {
    using namespace std;
    cout << "Hello, World!" << endl;
    int err = print_map("map.txt");
    if(err){
        cout << "Emotional damage" << endl;
    }
    return 0;
}
