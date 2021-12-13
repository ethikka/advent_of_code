#include <sstream>
#include <algorithm>
#include <set>
#include <cmath>
#include "../common/lib.h"

class paper {
  private:
    int max_x = 0, max_y = 0;
    std::set<std::pair<int,int>> dots;
  public:
    void set_point(int x, int y) { 
      dots.insert({x, y}); 
      max_x = std::max(max_x, x);
      max_y = std::max(max_y, y);
    }
    int64_t count_dots() { return dots.size(); }
    paper fold(std::string fold) {
      int n = std::stoi(fold.substr(2));
      paper np;
      if (fold[0] == 'y') { // up
        for(auto d: dots) {
          if      (d.second < (max_y - n)) np.set_point(d.first, d.second);
          else if (d.second > (max_y - n)) np.set_point(d.first, d.second - (2*(d.second - n)));
        }
      } else {              // left
        for(auto d: dots) {
          if      (d.first < (max_x - n)) np.set_point(d.first, d.second);
          else if (d.first > (max_x - n)) np.set_point(d.first - (2*(d.first - n)), d.second);
        }
      }
      return np;
    };

    void print() {
      printf("\033[2J");
      for (auto d: dots) 
        printf("\33[%d;%dH0", d.second+1, d.first+1);
      printf("\33[39;49m\n");
      printf("\33[%d;%dH-  \n", max_y+2, 0);
      std::cout << std::flush;
    };

};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  paper p;
  while (!std::cin.eof()) { 
    std::getline(std::cin, line);
    if (line.size() == 0) break;
    std::replace(line.begin(), line.end(), ',', ' '); 
    std::istringstream ssl(line);
    int x(0), y(0);
    ssl >> x >> y;
    p.set_point(x, y);
  }
  std::string instruction;
  while (std::cin >> instruction >> instruction >> instruction) {
    paper np = p.fold(instruction);
    if (res.first == 0) res.first = np.count_dots();
    p = np;
  }
  if (!output_for_timing)
    p.print();
  return res;
}