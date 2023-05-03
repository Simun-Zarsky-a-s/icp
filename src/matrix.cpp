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
#include <QApplication>
#include <QErrorMessage>
#include "Sources.h"
using namespace std;

Resources::Resources(string map){ ///todo

    src_file = std::move(map);
    height = -1;
    width = -1;

}

void Resources::dimensions(){
    fstream new_file;
    cout << src_file << endl;
    new_file.open(src_file, ios::in); //opening of the source file with map

        if(new_file.fail()){
            std::cerr <<  "File containing map not found.";
            exit(1);
        }

    string first_line;
    getline(new_file, first_line); // get first line with size
    istringstream iss(first_line); //split the line
    vector<int> size; string word;

    //load the words from first line to size array
    int bad_parameter = 1;
    int num;
    while(iss >> word){
        try{
             num = stoi(word); ///todo possible error here
        }
        catch(invalid_argument){
            std::cerr <<
                      "Strtoi error invalid number.";

            exit(1);
        }

        size.push_back(num);
    }
    new_file.close();
    height = size[0]+2;
    width = size[1]+2;
}

int Resources::get_width(){
    fstream new_file;
    cout << src_file << endl;
    new_file.open(src_file, ios::in); //opening of the source file with map

    if(new_file.fail()){
        std::cerr <<  "File containing map not found.";
        exit(1);
    }

    string first_line;
    getline(new_file, first_line); // get first line with size
    istringstream iss(first_line); //split the line
    vector<int> size; string word;

    //load the words from first line to size array
    int bad_parameter = 1;
    int num;
    while(iss >> word){
        try{
            num = stoi(word); ///todo possible error here
        }
        catch(invalid_argument){
            std::cerr <<
                    "Strtoi error invalid number.";

            exit(1);
        }

        size.push_back(num);
    }
    new_file.close();

    return size[1]+2;
}


int Resources::get_height(){
    fstream new_file;
    cout << src_file << endl;
    new_file.open(src_file, ios::in); //opening of the source file with map

    if(new_file.fail()){
        std::cerr <<
                "File containing map not found.";
        exit(1);
    }

    string first_line;
    getline(new_file, first_line); // get first line with size
    istringstream iss(first_line); //split the line
    vector<int> size; string word;

    //load the words from first line to size array
    int bad_parameter = 1;
    int num;
    while(iss >> word){
        try{
            num = stoi(word); ///todo possible error here
        }
        catch(invalid_argument){
           std:cerr<< "Strtoi error invalid number.";

            exit(1);
        }

        size.push_back(num);
    }
    new_file.close();

    return size[0]+2;
}

void Resources::fill_matrix() {
    fstream new_file;
    string line;
    vector<vector<char>> loaded_matrix(height, vector<char>(width, 0));
    new_file.open(src_file, ios::in); //opening of the source file with map
        if(new_file.fail()){
            std::cerr <<   "File containing map not found.";

            exit(1);

        }

    if (new_file.is_open()) {

        int row_num = 0;

        getline(new_file, line);
        // filling the matrix
        while (getline(new_file, line)) {
            // check lenght of line

            if(line.length() > width-2){
                std::cerr <<"Loaded map exceeds, given width." ;
                exit(1);

            }

            //convert line to vector and add it by each char to the matrix
            vector<char> line_of_chars(line.begin(), line.end());
            for(int i =0; i < line_of_chars.size(); i++){
                loaded_matrix[row_num][i] = line_of_chars[i];

            }

            row_num++;

            //check number of lines

            if(row_num > height-2){
                std::cerr <<"Loaded map exceeds, given height." ;
                exit(1);
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
                        std::cerr <<"Found more than one target in loaded map" ;
                        exit(1);
                    } else {
                        target = true;
                    }

                    break;

                case 'S':

                    if (start) {
                        std::cerr <<"Found more than one start in loaded map" ;

                        exit(1);
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

                    std::cerr << "Found invalid character in loaded map" ;
                    exit(1);

            }

        }
    }
    if(!target || !start){
        std::cerr <<"Loaded map does not contain start or target." ;
        exit(1);
    }
}


vector<vector <char>> Resources::get_matrix() {

     Resources res(Sources::Map_file_destination.toStdString()); ///init resources

        res.dimensions();

        res.fill_matrix();

        res.check_matrix();

    return res.matrix;

}




