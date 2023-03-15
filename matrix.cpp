//
// Created by samuel on 9.3.2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "matrix.hpp"

using namespace std;

int print_map(char map[]){
    fstream file;
    file.open(map, ios::in );

        string line;
        getline(file, line);
        get_dimensions(line);

        while (getline(file, line))
        {
            // note that the newline character is not included
            // in the getline() function
            cout << line << endl;
        }
    file.close();
    return 0;
}

int get_dimensions(string line){
    string str=line;
    vector<string> words;
    char delimeter=' ';
    int n=str.size();
    for(int i=0;i<n;i++)
    {
        int j=i;
        while(str[i]!=delimeter && i<n)
            i++;
        string temp=str.substr(j,i-j);
        words.push_back(temp);
    }
    for (auto i : words){ //C++11
        cout <<"Parametr "<< i<< endl;
    }
    return 0;
}







