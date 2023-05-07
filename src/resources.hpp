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
    //!file with map
        QString src_file;
        //!loaded dimensions height
        int height;

    //!loaded dimensions width
        int width;

    //!vector of positions [height, width] of ghosts
        vector<vector<int>> ghosts;

    //!vector of positions [height, width] of keys
        vector<vector<int>> keys;

    //!2D vector representing loaded map
        vector<vector<char>> matrix;

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

            /**
         * Extracts width s from the first line of source file
         * Initializes width
         * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
         * @date 21/4/2023
         */
        [[nodiscard]] static int get_width() ;

            /**
          * Extracts height s from the first line of source file
          * Initializes height
          * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
          * @date 21/4/2023
          */
        [[nodiscard]] static int get_height() ;

        /**
        * Transform the data from source file to 2D matrix and stores it in matrix
        * Initializes matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void fill_matrix() ;

        /**
       * Transform the data from source file to 2D matrix and stores it in matrix in log mode
       * Initializes matrix, have special boundaries for loading
       * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
       * @date 3/5/2023
       */
        void fill_log_matrix() ;

        /**
        * Checks validity of the content of loaded matrix
        * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
        * @date 21/4/2023
        */
        void check_matrix();

};


#endif
