

#include <string>
#include <vector>

using namespace std;


class Resources {

public:

    /**
     *  Constructor of class resources
     *  Loads the input file with map
     *  Validates content of the file
     * @param map
     */
    Resources(const string& map);

    int height;
    int width;
    int ghost_number;
    int key_number;
    vector<vector<char>> matrix;
};

/**
 * Returns vector with given parameters at the first line of input file
 * @param first_line
 * @return size in vector (two integers values)
 */
vector<int> dimensions(const string& first_line);

/**
 * Prints given 2D vector
 * @param matrix
 */
void print_matrix(vector<vector<char>> matrix);