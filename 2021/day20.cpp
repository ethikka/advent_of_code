#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "../common/lib.h"

std::string lookup;
const int MARGIN = 200;

template<typename T>
std::vector<T> offsets();

struct vector2 {
  int x;
  int y;
};

template<>
std::vector<vector2> offsets() { return {{-1,-1},{0,-1},{1,-1},{-1,0},{0,0},{1,0},{-1,1},{0,1},{1,1}}; };
vector2 operator +(const vector2 &lhs, const vector2 &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y }; };
bool operator ==(const vector2 &lhs, const vector2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };

namespace std {
  template<> struct std::hash<vector2> { std::size_t operator()(const vector2& k)const { return hash<long long>()(((long long)k.x)^(((long long)k.y)<<32)); };};
};

class map {
  private:
    std::unordered_map<vector2,char> current_gen;
    int max_x = 0;
    int max_y = 0;
    int gen = 0;    
  public:
    void advance() {
      gen++;
      std::unordered_map<vector2,char> newstate;//(current_gen);
      for (auto e: current_gen) {
        int k(0);
        for(const auto i: offsets<vector2>()) {
          if (current_gen.count(e.first+i) > 0)
            if (current_gen[e.first+i] == '#') k++;
          k *= 2;
        }
        newstate[e.first] = lookup[k/2];
      }
      current_gen = newstate;
    };
    void reset_max() { max_x = 0; max_y = 0; };
    void place(vector2 key, char l) { current_gen[key] = l; max_x = std::max(max_x, key.x); max_y = std::max(max_y, key.y); };

    int count_on() {
      int res(0);
      for (auto e: current_gen) 
        if (e.first.x >= MARGIN-gen && e.first.y >= MARGIN-gen && e.first.x <= max_x+gen && e.first.y <= max_y+gen) 
          if (e.second == '#') res++;
      return res;
    };
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::getline(std::cin, lookup);
  map a;
  char c;
  for(int x = 0; x < 100+MARGIN+MARGIN; x++) for(int y = 0; y < 100+MARGIN+MARGIN; y++) a.place({x, y}, '.'); 
  a.reset_max();

  int x(MARGIN), y(MARGIN);
  while (std::cin >> std::noskipws >> c) { if (c == '\n') { x = MARGIN; y++; } else a.place({x++, y}, c); }

  for (int i = 0; i < 50; i++) {
    if (i == 2) res.first = a.count_on();
    a.advance();
  }
  res.second = a.count_on();
  return res;
}