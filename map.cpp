#include <vector>
#include <iostream>
#include <random>

using std::cout;
using std::endl;
using std::vector;

enum class CellType {
    Empty,
    Wall,
    Occupied // This can be further detailed for characters, opponents, chests, etc.
};

class Map {
public:
    Map(int width, int height) : width(width), height(height), grid(height, std::vector<CellType>(width, CellType::Empty)) {
      makeMap();
    }

    void makeMap() {
      // fill with 0
      int x = 10; // Width
      int y = 10; // Height

      // Create a 2D vector filled with 0
      std::vector<std::vector<int>> arr(y, std::vector<int>(x, 1));

      printMap(arr);

      // Set begin variables and set initial position to 1
      int beginX = x/2;
      int beginY = y/2;
      int dynamicX = beginX;
      int dynamicY = beginY;
      arr[beginX][beginY] = 2;

      printMap(arr);

      // MAKE A PATH TO OUTSIDE THE MAP
      while (getRandomStep(arr, dynamicX, dynamicY)) {
      }
      dynamicX = x/2;
      dynamicY = y/2;
      while (getRandomStep(arr, dynamicX, dynamicY)) {
      }
      dynamicX = x/2;
      dynamicY = y/2;
      while (getRandomStep(arr, beginX, dynamicY)) {
      }

      printMap(arr);

      // get (3)
      loadOccupiedCell(arr);

      printMap(arr);

      // check if path exists
      if (isValidPathExists(arr, beginX, beginY)) {
        std::cout << "There is a path to the outside." << std::endl;
      } else {
        std::cout << "No path to the outside." << std::endl;
      }


      }

    void setCell(int x, int y, CellType type) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = type;
        } else {
            std::cout << "Error: Position out of bounds.\n";
        }
    }

    CellType getCell(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return grid[y][x];
        }
        return CellType::Wall; // Treat out-of-bounds as walls
    }

    // add chests, doors, etc
    bool loadOccupiedCell(vector<vector<int>> &arr) {
      int numNeighbours = 0;
      for (int i = 1; i<arr.size() - 1; i++) {
        for (int j = 1; j<arr[i].size() - 1; j++) {
          // check for exactly 3 neighbours
          if (arr[i+1][j] == 2)
            numNeighbours++;
          if (arr[i-1][j] == 2)
            numNeighbours++;
          if (arr[i][j+1] == 2)
            numNeighbours++;
          if (arr[i][j-1] == 2)
            numNeighbours++;

          if (numNeighbours == 3) {
            arr[i][j] = 3;
            numNeighbours = 0;
            break;
          }
          numNeighbours = 0;
        }
      }
    }

    bool isValid(int x, int y, int width, int height) {
    return x >= 0 && y >= 0 && x < width && y < height;
}

    bool isValidPathExists(std::vector<std::vector<int>>& grid, int x, int y) {
      int width = grid[0].size();
      int height = grid.size();

      // Check if out of bounds (means we reached the edge)
      if (!isValid(x, y, width, height)) return true;

      // If not "2", not part of the path
      if (grid[y][x] != 2) return false;

      // Mark as visited to avoid infinite loops
      grid[y][x] = -1; // Temporary mark as visited

      // Explore all 4 directions
      bool up = isValidPathExists(grid, x, y - 1);
      bool down = isValidPathExists(grid, x, y + 1);
      bool left = isValidPathExists(grid, x - 1, y);
      bool right = isValidPathExists(grid, x + 1, y);

      // Reset to "2" after exploring (if you need to keep the grid intact)
      // grid[y][x] = 2;
      return up || down || left || right;
    }


    /*
    ~~~~~~~~~~~~~~~~ UTIL METHODS ~~~~~~~~~~~~~~~~~~
    */
    bool indexExists(vector<vector<int>>& vec, int x, int y) {
      // Check if the x index is within bounds
      if (x >= 0 && x < vec.size()) {
          // Check if the y index is within bounds for the specific x
          if (y >= 0 && y < vec[x].size()) {
              return true; // The index exists
          }
      }
      return false; // The index does not exist
    }
    bool getRandomStep(vector<vector<int>>& vec, int &x, int &y) {
      // Random number generator
      std::random_device rd;  // Obtain a random number from hardware
      std::mt19937 gen(rd()); // Seed the generator
      std::uniform_int_distribution<> distr(0, 3); // Define the range

      switch (distr(gen)) {
        case 0:
            //cout << "You chose option 0." << endl;
            x -= 1;
            break;
        case 1:
            //cout << "You chose option 1." << endl;
            x += 1;
            break;
        case 2:
            //cout << "You chose option 2." << endl;
            y -= 1;
            break;
        case 3:
            //cout << "You chose option 3." << endl;
            y += 1;
            break;
      }
        // check if step exists
        if (indexExists(vec, x, y)) {
          vec[x][y] = 2;
          return true;
        }
        else {
          return false;
        }

    }

    void printMap(vector<vector<int>> &arr) {
      // Print the 2D array to verify it's filled with 0
      for (size_t i = 0; i < arr.size(); ++i) {
        // Iterate through each column in the row
        for (size_t j = 0; j < arr[i].size(); ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl; // Newline after each row for readability
      }
      cout<< "\n" <<endl;
    }



private:
    int width, height;
    std::vector<std::vector<CellType>> grid;
};

int main() {
    Map myMap(10, 5); // Creating a map of width 10 and height 5
    // myMap.setCell(2, 2, CellType::Wall); // Setting a specific cell as Wall
    // myMap.setCell(3, 3, CellType::Occupied); // Setting a cell as Occupied

    cout << "Map after initialization and modifications:" << endl;

    // Check if a valid path exists - this function needs to be implemented based on your specific requirements
    // if (myMap.isValidPathExists()) {
    //     cout << "A valid path exists in the map." << endl;
    // } else {
    //     cout << "No valid path exists in the map." << endl;
    // }

    return 0;
}
