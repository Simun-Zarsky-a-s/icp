/**
    * Project: ICP 2022/23
    *
    * @brief Implementation of resource handling
    * @file matrix.cpp
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    */

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include "matrix.hpp"
#include "exception.h"
using namespace std;

Resources::Resources(string map){

    src_file = std::move(map);
    height = -1;
    width = -1;

}

void Resources::dimensions(){
    fstream new_file;
    new_file.open(src_file, ios::in); //opening of the source file with map
    if(new_file.fail()){
        throw Exception("Error while opening the file");
    }
    string first_line;
    getline(new_file, first_line); // get first line with size
    istringstream iss(first_line); //split the line
    vector<int> size; string word;

    //load the words from first line to size array
    int bad_parameter = 1;
    while(iss >> word){
        int num = stoi(word);
        size.push_back(num);
    }
    new_file.close();
    height = size[0];
    width = size[1];
}

void Resources::fill_matrix() {
    fstream new_file;
    string line;

    new_file.open(src_file, ios::in); //opening of the source file with map
    if(new_file.fail()){
        throw Exception("Error while opening the file");
    }
    if (new_file.is_open()) {

        int row = 0;
        getline(new_file, line);
        // filling the matrix
        while (getline(new_file, line)) {
            // check lenght of line
            if (line.length() > width) {
                string err = "line exceeds the width";
                throw Exception("Line exceeds the width");
            }
            //convert line to vector and add it to matrix
            vector<char> v(line.begin(), line.end());
            matrix.push_back(v);
            row++;

            //check number of lines
            if (row > height) {
                throw Exception("Row exceeds the height");
            }
        }
    }
    else{
        new_file.close();

    }
    new_file.close();

}

void Resources::check_matrix(){
    bool target = false;
    bool start = false;
    for(int i=0; i<matrix.size(); i++) {
        for (int j = 0; j <matrix[i].size(); j++) {
            switch(matrix[i][j]) {
                case 'T':
                    if (target) {
                        throw Exception("Double target in matrix");
                    } else {
                        target = true;
                    }
                    break;

                case 'S':
                    if (start) {
                        throw Exception("Double start in matrix");
                    } else {
                        start = true;
                    }
                    break;

                case 'X':
                case '.':
                case 'G':
                case 'K':
                    break;
                default:
                    throw Exception("Invalid char in matrix");

            }

        }
    }
    if(!target || !start){
        throw Exception("Missing target or start in matrix");
    }
}

void Resources::ghost_key() {
    vector<int> position(2);
    for(int i=0; i<matrix.size(); i++) {
            for (int j = 0; j <matrix[i].size(); j++) {
                position[0] = i;
                position[1] = j;
                if (matrix[i][j] == 'G'){
                    ghosts.push_back(position);
                }
                if (matrix[i][j] == 'K'){
                    keys.push_back(position);
                }
            }

    }
}

void Resources::print_matrix(){
    for(auto & i : matrix) {
        for (char j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void Resources::print_ghosts(){
    for(auto & ghost : ghosts) {
        cout << "ghost on :" ;
        for (int j : ghost) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void Resources::print_keys(){
    for(auto & key : keys) {
        cout << "key on :";
        for (int j : key) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void debug_resources(string map){

    Resources res(std::move(map)); ///init resources

    try {
        res.dimensions();
    } catch (Exception mce) {
        cout << "Encoutered exception in: res.fill_matrix()" << endl;
        cout << mce.show() << endl;
    }

    try {
        res.fill_matrix();
    } catch (Exception mce) {
        cout << "Encoutered exception in: res.fill_matrix()" << endl;
        cout << mce.show() << endl;
    }

    try {
        res.check_matrix();
    } catch (Exception mce) {
        cout << "Encoutered exception in: res.check_matrix();" << endl;
        cout << mce.show() << endl;
    }


    cout << "height :" << res.height << endl;
    cout << "width :" << res.width << endl;
    cout << "MAP :"  << endl;
    res.print_matrix();
    res.ghost_key();
    res.print_ghosts();
    res.print_keys();
}




