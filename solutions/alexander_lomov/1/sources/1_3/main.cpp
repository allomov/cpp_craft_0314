#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <list>

struct Point {
  int x, y;
  Point(const unsigned int x_, const unsigned int y_): x(x_), y(y_) {}
};

template <typename T>
class BoundsMatrix
{
  std::vector<T> inner_;
  unsigned int dimx_, dimy_;

public:

  void setDimensions (const unsigned int dimx, const unsigned int dimy) {
    dimx_ = dimx; dimy_ = dimy;
    inner_.resize (dimx_ * dimy_);
  }

  T& operator()(const unsigned int x, const unsigned int y) {
//    if (x >= dimx_ || y>= dimy_) throw 0; // ouch
    return inner_[dimx_ * y + x];
  }

  void set(const unsigned int x, const unsigned int y, const T value) {
    inner_[dimx_ * y + x] = value;
  }

  unsigned int dimx() {
    return dimx_;
  }

  unsigned int dimy() {
    return dimy_;
  }
};


class IslandsMap {
private:
  BoundsMatrix<short> matrix;

public: 
  void readFromFile(const std::ifstream& input_file) {
    std::vector<std::string> lines;
    std::string line;
    while(!input_file.eof()) { 
      std::getline(input_file, line);
      lines.push_back(line);
    }
    matrix.setDimensions(line.length(), lines.size());
    for (int i = 0; i < lines.size(); i++) {
      line = lines.at(i);
      for (int j = 0; j < line.length(); j++) {
        short value = (line.at(j) == 'o' ? 1 : 0);
        matrix.set(j, i, value);
      }
    }

  }
  
  bool isLand(const int x, const int y) {
    if (x < 0 || y < 0 || x >= dimx() || y >= dimy()) return false;
    return matrix(x, y) != 0;
  }

  bool isMarked(unsigned int x, unsigned int y) {
    return matrix(x, y) > 1;
  }

  void markLand(unsigned int x, unsigned int y) {
    matrix.set(x, y, 100);
  }

  unsigned int dimx() {
    return matrix.dimx();
  }

  unsigned int dimy() {
    return matrix.dimy();
  }

  std::list<Point> landsNearby(int x, int y) {
    std::list<Point> result;
    if (isLand(x+1, y)) result.push_back(Point(x+1, y));
    if (isLand(x-1, y)) result.push_back(Point(x-1, y));
    if (isLand(x, y+1)) result.push_back(Point(x, y+1));
    if (isLand(x, y-1)) result.push_back(Point(x, y-1));
    return result;
  }
    
};


int main(int argc, char* argv[]) {    

    std::ifstream input_file(BINARY_DIR "/input.txt");
    std::ofstream output_file(BINARY_DIR "/output.txt");
    IslandsMap map;
    map.readFromFile(input_file);
    unsigned int iselands_count = 0;
    std::stack<Point> stack;

    for (int y = 0; y < map.dimy(); y++) {
      for (int x = 0; x < map.dimx(); x++) {
        if (map.isLand(x, y) && !map.isMarked(x, y)) {
          std::cout << "Found an island (" << x << ", " << y << std::endl;
          stack.push(Point(x, y));
          iselands_count++;
          while (!stack.empty()) {
            Point current_point = stack.top();
            stack.pop();
            map.markLand(current_point.x, current_point.y);
            std::cout << "Marked island (" << current_point.x << ", " << current_point.y << std::endl;
            std::list<Point> neighbors = map.landsNearby(current_point.x, current_point.y);
            for(std::list<Point>::iterator iterator = neighbors.begin(); iterator != neighbors.end(); ++iterator) {
              Point neighbor = *iterator;
              if (!map.isMarked(neighbor.x, neighbor.y)) {
                std::cout << "Neigbor added (" << neighbor.x << ", " << neighbor.y << std::endl;
                stack.push(neighbor);
              }
            }
          }
        }
      }
    }

    output_file << iselands_count << std::endl;
    input_file.close();
    output_file.close();
}
