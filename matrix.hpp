#include <string>
#include <vector>

using namespace std;
class Resources {

public:
    Resources(const string& map);

    int height;
    int width;
    int ghost_number;
    int key_number;
    vector<vector<char>> matrix;
};