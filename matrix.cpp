//
// Created by samuel on 9.3.2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<sstream>
#include <cstdio>

#include "matrix.hpp"

#define SOURCE_ERR 1 ///todo make file with errors

using namespace std;

void print_matrix(vector<vector<char>> matrix){
    for(int i=0; i<matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> dimensions(const string& first_line){
    istringstream iss(first_line); //split the line
    vector<int> size; string word;
    //load the words from first line to size array
    while(iss >> word){
        int num = stoi(word);
        size.push_back(num);
    }
    return size;
}

Resources:: Resources(const string& map){
    fstream new_file;
    new_file.open(map, ios::in); //opening of the source file with map
    string sa;

    getline(new_file, sa); // get first line with size
    vector<int> size;
    size = dimensions(sa);
    //transform size array to class attributes
    height = size[0];
    width = size[1];

    // Checking whether the file is open.
    if (new_file.is_open()) {

        int row =0;
        // filling the matrix
        while (getline(new_file, sa)) {
            // check lenght of line
            if(sa.length() > width){
                perror("width of line exceeds given dimension");
                exit(SOURCE_ERR);
            }
            //convert line to vector and add it to matrix
            vector<char> v(sa.begin(), sa.end());
            matrix.push_back(v); row++;

            //check number of lines
            if(row > height){
                perror("height of input exceeds given dimension");
                exit(SOURCE_ERR);
            }

        }

        bool target = false;
        bool start = false;

        //check the matrix and get number of ghosts and keys
        for(int i=0; i<matrix.size(); i++){    //row
            for(int j=0; j<matrix[i].size(); j++){ //column

                switch(matrix[i][j]){ //check the character of the matrix
                    case 'T':
                        if(target){
                            perror("more targets in source file");
                            exit(SOURCE_ERR);
                        }else{
                            target = true;
                        }
                        break;

                    case 'S':
                        if(start){
                            perror("more starts in source file");
                            exit(SOURCE_ERR);
                        }else{
                            start = true;
                        }
                        break;

                    case 'X':
                    case '.':
                    case '\n':
                    case '\0':
                        continue;

                    case'G':
                        ghost_number++;
                        break;

                    case'K':
                        key_number++;
                        break;

                    default:
                        perror("unexpected character in source file");
                        exit(SOURCE_ERR);
                }
            }

        }
        //check if file contained target and start
        if(!target || !start){
            perror("no target or start in source file");
            exit(SOURCE_ERR);
        }

        // Close the file object.
        new_file.close();
    }


}

///todo remove make segment errors

vector<int> check_matrix(vector<vector<char>> matrix){
    bool target = false;
    bool start = false;
    int key =0, ghost =0;
    vector<int> bn_kn;

    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            cout<<matrix[i][j]<<" ";
            switch(matrix[i][j]){
                case 'T':
                    if(target){
                        perror("more targets in source file");
                        exit(SOURCE_ERR);
                    }else{
                        target = true;
                    }
                    break;

                case 'S':
                    if(start){
                        perror("more starts in source file");
                        exit(SOURCE_ERR);
                    }else{
                        start = true;
                    }
                    break;

                case 'X':
                case '.':
                case '\n':
                case '\0':
                    continue;

                case'G':
                    ghost++;
                    break;

                case'K':
                    key++;
                    break;
                default:
                    perror("unexpected character in source file");
                    exit(SOURCE_ERR);
            }
        }
        cout<<endl;
    }


    if(!target || !start){
        perror("no target or start in source file");
        exit(SOURCE_ERR);
    }
    bn_kn[0] = ghost;
    bn_kn[1] = key;
    for(int i = 0; i < bn_kn.size(); i++)
        std::cout << bn_kn[i] << ' ';

    return bn_kn;

}










