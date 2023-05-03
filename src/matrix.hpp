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
#include <QString>

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
        explicit Resources(QString map);

        QString src_file; ///file with map
        ///loaded dimensions
        int height;
        int width;
        vector<vector<int>> ghosts; ///vector of positions [height, width] of ghosts
        vector<vector<int>> keys;  ///vector of positions [height, width] of keys
        vector<vector<char>> matrix; ///2D vector representing loaded map

        /**
      * Initializes resesources and returns matrix
      * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
      * @date 25/4/2023
      */
        static vector<vector <char>> get_matrix();


        /**
       * Extracts given dimensions from the first line of source file
       * Initializes height and width
       * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
       * @date 21/4/2023
       */
        void dimensions();
        int get_width();
        int get_height();

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
        void fill_log_matrix() ;

        /**
        * Checks validity of the content of loaded matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void check_matrix();



};

/**
       * Prints content od 2D vector
       * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
       * @date 25/4/2023
       */
void print_2D_vector(vector<vector<char>> mapa);

#endif
