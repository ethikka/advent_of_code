#include <sstream>
#include <vector>
#include <cmath>
#include "../common/lib.h"

const int BUMP = 100;

class simplesnailfish {
  public:
    std::vector<int64_t> na;
    simplesnailfish(std::string input) { for (int i = 0; i < input.size(); i++) if (input[i] >= '0' && input[i] <= '9') na.push_back(100+(input[i]-'0')); else na.push_back((int(input[i]))); }
    simplesnailfish(std::vector<int64_t> a, std::vector<int64_t> b) { na.push_back((int)'['); for(auto i: a) na.push_back(i); na.push_back((int)','); for(auto i: b) na.push_back(i); na.push_back((int)']'); }

    int pos_of_num(int start, bool forward) {
      for (int i = start; i >= 0 && i < na.size(); (forward)?i++:i--) if (na[i] >= BUMP) return i;
      return -1;
    }

    bool explode() {
      int bc(0);
      for (int i = 0; i < na.size(); i++) {
        if (na[i] == (int)'[') bc++; if (na[i] == (int)']') bc--;
        if (bc == 5) {
          int p = pos_of_num(i, false);
          if (p != -1) na[p] += (na[pos_of_num(i, true)])-BUMP;
          p = pos_of_num(i+5, true);
          if (p != -1) na[p] += (na[pos_of_num(i+3, true)])-BUMP;
          for (int ec = 0; ec < 4; ec++) na.erase(na.begin()+i);
          na[i] = BUMP; // 0
          return true;
        }
      }
      return false;
    }

    bool split() {
      for (int i = 0; i < na.size(); i++) 
        if (na[i] >= (BUMP+10)) {
          int val = na[i]-BUMP;
          na.erase(na.begin()+i);
          na.insert(na.begin()+i, {(int)'[', (int)floor(val/2.0)+BUMP, (int)',', (int)ceil(val/2.0)+BUMP, (int)']'});
          return true;
        }
      return false;
    }

    simplesnailfish operator+(const simplesnailfish &r) { return simplesnailfish(na, r.na); }

    void reduce() { while (explode() || split()); }
    void print() { for (int i = 0; i < na.size(); i++) if (na[i] >= BUMP) std::cout << (na[i])-BUMP; else std::cout << (char)na[i]; std::cout << std::endl; }

    std::uintmax_t magnitude() {
      reduce();
      while (true) {
        if (na.size() == 1) return na[0]-BUMP;
        for (int i = 2; i < na.size(); i++) 
          if ((na[i] == (int)',') && (na[i-1] >= BUMP) && (na[i+1] >= BUMP)) {
            na[i+2] = (3*(na[i-1]-BUMP))+(2*(na[i+1]-BUMP))+BUMP;
            for (int r = 0; r < 4; r++) na.erase(na.begin()+i-2);
          }
      }
    }
};

std::vector<simplesnailfish> numbers;

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  while (std::cin.peek() != EOF) {
    std::string line;
    std::getline(std::cin, line);
    numbers.push_back(simplesnailfish(line));
  }

  simplesnailfish s = numbers[0];
  for (int i = 1; i < numbers.size(); s = s+numbers[i++]) s.reduce();
  res.first = s.magnitude();

  for (int i = 0; i < numbers.size()-1; i++) 
    for (int j = i; j < numbers.size(); j++) {
      res.second = std::max(res.second, (numbers[i]+numbers[j]).magnitude());
      res.second = std::max(res.second, (numbers[j]+numbers[i]).magnitude());
    }
  return res;
}
