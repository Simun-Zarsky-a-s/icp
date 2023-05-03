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
#include "resources.hpp"
#include <QApplication>
#include <QErrorMessage>
#include "Sources.h"
#include <QDebug>
#include <QFile>

using namespace std;


Resources::Resources(QString map){ ///todo

    src_file = std::move(map);
    height = -1; //default values
    width = -1;

}

void Resources::dimensions(){
    fstream new_file;
    new_file.open(src_file.toStdString(), ios::in); //opening of the source file with map

        if(new_file.fail()){
            std::cerr <<  "1File containing map not found.";
            std::cout << src_file.toStdString();
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
             num = stoi(word);
        }
        catch(invalid_argument){
            std::cerr <<
                      "Strtoi error invalid number.";

            exit(1);
        }

        size.push_back(num);
    }
    new_file.close();
    height = size[0]+2; //set height
    width = size[1]+2;  //set width
}

int Resources::get_width() const{
    fstream new_file;
    new_file.open(src_file.toStdString(), ios::in); //opening of the source file with map
    QFile commonFile(Sources::Map_file_destination);

    if (!commonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Unable to open file: " << commonFile.fileName() << " besause of error " << commonFile.errorString() << endl;

        return 1;
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

    return size[1]+2;//return width
}


int Resources::get_height() const{
    fstream new_file;
    new_file.open(src_file.toStdString(), ios::in); //opening of the source file with map

    if(new_file.fail()){
        std::cerr <<
                "3File containing map not found.";
        std::cout << src_file.toStdString();
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
            cerr<< "Strtoi error invalid number.";
            exit(1);
        }

        size.push_back(num);
    }
    new_file.close();

    return size[0]+2;//return height
}

void Resources::fill_matrix() {
    fstream new_file;
    string line;

    vector<vector<char>> loaded_matrix(height, vector<char>(width, 0));
    new_file.open(src_file.toStdString(), ios::in); //opening of the source file with map
        if(new_file.fail()){
            std::cerr <<   "4File containing map not found.";
            std::cout << src_file.toStdString();
            exit(1);

        }

    if (new_file.is_open()) {

        int row_num = 0;

        getline(new_file, line);//removing first line with dimensions
        // filling the matrix
        while (getline(new_file, line)) {
            // check length of line

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

    new_file.close();

}

void Resources::check_matrix(){
    bool target = false;
    bool start = false;
    for(int i=0; i<matrix.size()-2; i++) { //for each row
        for (int j = 0; j <matrix[i].size()-2; j++) {// for each column
            switch(matrix[i][j]) {
                case 'T':

                    if (target) { //target check
                        std::cerr <<"Found more than one target in loaded map" ;
                        exit(1);
                    } else {
                        target = true;
                    }

                    break;

                case 'S':

                    if (start) {  //start check
                        std::cerr <<"Found more than one start in loaded map" ;

                        exit(1);
                    } else {
                        start = true;
                    }

                    break;

                case 'X': //other expected characters
                case '.':
                case 'G':
                case 'K':
                    break;
                default: //unexpected characters

                    std::cerr << "Found invalid character in loaded map" ;
                    exit(1);

            }

        }
    }
    if(!target || !start){ //missing target or start
        std::cerr <<"Loaded map does not contain start or target." ;
        exit(1);
    }
}


vector<vector <char>> Resources::get_matrix() {

    if(!Sources::play_log_mode){ //loading in game mode

        Resources res(Sources::Map_file_destination); ///init resources

        res.dimensions(); //get dimensions
        res.fill_matrix(); //load matrix
        res.check_matrix();//check it

        return res.matrix;
    }
    else{ //loading in log mode

        Resources res(Sources::Map_file_destination); ///init resources

        res.dimensions(); //get dimensions
        res.fill_log_matrix();//load matrix
        res.check_matrix();//check it

        return res.matrix;

    }


}

void Resources::fill_log_matrix() {
    fstream new_file;
    string line;
    vector<vector<char>> loaded_matrix(height, vector<char>(width, 0));//helper matrix

    new_file.open(Sources::Map_file_destination.toStdString(), ios::in); //opening of the source file with map
    if(new_file.fail()){
        std::cerr <<   "5File containing map not found.";
        std::cout << src_file.toStdString();
        exit(1);

    }

    if (new_file.is_open()) {

        int row_num = 0;

        getline(new_file, line);
        // filling the matrix
        while (getline(new_file, line) && row_num <  height-2) { //loading only the top of the file with map,
            // in the rest of the file are logs

            if(line.length() > width-2){ //check dimension
                std::cerr <<"Loaded map exceeds, given width." ;
                exit(1);

            }

            //convert line to vector and add it by each char to the matrix
            vector<char> line_of_chars(line.begin(), line.end());
            for(int i =0; i < line_of_chars.size(); i++){
                loaded_matrix[row_num][i] = line_of_chars[i];

            }

            row_num++;
        }
        matrix = loaded_matrix;
    }

    new_file.close(); //close the file anyway

}





