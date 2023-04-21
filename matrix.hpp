/**
    * Project: ICP 2022/23
    *
    * @brief Library for resource handling
    * @file matrix.hpp
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    * @date 21/4/2023
    */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include <vector>
#include <string>

using namespace std;

/**
 * Class representing information loaded from the source file
 */
class Resources {

    public:
        /**
         * Constructor of class Resources
         * @param src_file file with map for the game
         */
        explicit Resources(string src_file);

        string src_file; ///file with map
        ///loaded dimensions
        int height;
        int width;
        vector<vector<int>> ghosts; ///vector of positions [height, width] of ghosts
        vector<vector<int>> keys;  ///vector of positions [height, width] of keys
        vector<vector<char>> matrix; ///2D vector representing loaded map

        /**
       * Extracts given dimensions from the first line of source file
       * Initializes height and width
       * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
       * @date 21/4/2023
       */
        void dimensions();

        /**
        * Takes positions of ghosts and keys from matrix
         * Initializes ghosts and keys
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void ghost_key();

        /**
        * Transform the data from source file to 2D matrix and stores it in matrix
        * Initializes matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void fill_matrix() ;

        /**
        * Checks validity of the content of loaded matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void check_matrix();

        /**
        * Prints content of the matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void print_matrix();
        /**
        * Prints all positions of ghosts
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void print_ghosts();

        /**
        * Prints all positions of keys
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void print_keys();

};

/**
 * Prints all attributes of resources for debugging purposes
 * Uses: Resources::print_keys(), Resources::print_ghosts() and Resources::print_matrix()
 * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
 * @param map file containing the map
 * @date 21/4/2023
 */
void debug_resources(string map);


#endif
