#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include "../common/lib.h"

class segmentdisplay {
  private:
    std::vector<std::string> checks;
    std::map<std::string, int> numbers;
    std::string rnum[10];
  public:
    int a = 0;
    int b = 0;
    segmentdisplay(std::string input) {
      std::istringstream ssl(input);
      std::string line;
      for (int i = 0; i < 10; i++) {
        ssl >> line;
        std::sort(line.begin(), line.end());
        checks.push_back(line);
      }
      ssl >> line;// discard the |
      descramble();
      for (int i = 0, mul = 1000; i < 4; i++, mul /= 10) {
        ssl >> line;
        std::sort(line.begin(), line.end());
        int s = line.size();
        if (s == 2 || s == 3 || s ==4 || s == 7)
          a++;
        b += (numbers[line]*mul);
      }
    }

    bool contains(std::string s, std::vector<std::string> check_against) {
      bool res(true);
      for (auto ss: check_against) {
        for(auto c: ss) 
          res &= (s.find(c) != std::string::npos);
        if (!res) return false;
      }
      return res;
    }

    void descramble() {
      for(auto c: checks) { 
        if (c.size() == 2) { numbers[c] = 1; rnum[1] = c; }
        if (c.size() == 4) { numbers[c] = 4; rnum[4] = c; }
        if (c.size() == 3) { numbers[c] = 7; rnum[7] = c; }
        if (c.size() == 7) { numbers[c] = 8; rnum[8] = c; }
      }
      for(auto c: checks) { 
        if (c.size() == 6) {
          if      (!contains(c, {rnum[1]}))                  { numbers[c] = 6; rnum[6] = c; }
          else if (contains(c, {rnum[1], rnum[4], rnum[7]})) { numbers[c] = 9; rnum[9] = c; }
          else                                               { numbers[c] = 0; rnum[0] = c; }}
        if (c.size() == 5) if (contains(c, {rnum[1]})) { numbers[c] = 3; rnum[3] = c; }
      }
      for(auto c: checks) 
        if (c.size() == 5) {
          if (contains(rnum[6], {c})) { numbers[c] = 5; rnum[5] = c; } else if (c != rnum[3]) { numbers[c] = 2; rnum[2] = c; }}
    }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (!std::cin.eof()) { 
    std::getline(std::cin, line);
    segmentdisplay s(line);
    res.first += s.a;
    res.second += s.b;
  }
  return res;
}