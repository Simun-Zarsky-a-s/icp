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

Resources::Resources(string map){ ///todo

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
    height = size[0]+2; ///todo document this
    width = size[1]+2;
}

void Resources::fill_matrix() {
    fstream new_file;
    string line;
    vector<vector<char>> loaded_matrix(height, vector<char>(width, 0));
    new_file.open("map.txt", ios::in); //opening of the source file with map
    if(new_file.fail()){
        throw Exception("Error while opening the file");
    }
    if (new_file.is_open()) {

        int row_num = 0;

        getline(new_file, line);
        // filling the matrix
        while (getline(new_file, line)) {
            // check lenght of line
            if (line.length() > width) {
                string err = "line exceeds the width";
                throw Exception("Line exceeds the width");
            }
            //convert line to vector and add it by each char to the matrix
            vector<char> line_of_chars(line.begin(), line.end());
            for(int i =0; i < line_of_chars.size(); i++){
                loaded_matrix[row_num][i] = line_of_chars[i];

            }

            row_num++;

            //check number of lines
            if (row_num > height) {
                throw Exception("Row exceeds the height");
            }
        }
        matrix = loaded_matrix;
    }
    else{
        new_file.close();

    }
    new_file.close();

}

void Resources::check_matrix(){
    bool target = false;
    bool start = false;
    for(int i=0; i<matrix.size()-2; i++) {
        for (int j = 0; j <matrix[i].size()-2; j++) {
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

void print_2D_vector(vector<vector<char>> matrix){
    for(auto & i : matrix) {
        for (char j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}


vector<vector <char>> Resources::get_matrix() {

     Resources res(std::move("map.txt")); ///init resources
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

    return res.matrix;

}





