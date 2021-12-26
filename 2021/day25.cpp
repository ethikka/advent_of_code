#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "../common/lib.h"

struct vector2 {
  int x;
  int y;
};
vector2 operator +(const vector2 &lhs, const vector2 &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y }; };
bool operator ==(const vector2 &lhs, const vector2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };

namespace std {
  template<> struct std::hash<vector2> { std::size_t operator()(const vector2& k)const { return hash<long long>()(((long long)k.x)^(((long long)k.y)<<32)); };};
};

class herd {
  private:
    std::unordered_map<vector2,char> current_gen;
    int max_x = 0;
    int max_y = 0;
    vector2 _or = {1,0};
    vector2 _od = {0,1};
  public:
    bool advance_generation() {
      int moves(0);
      std::unordered_map<vector2,char> newstate;
      newstate = current_gen;
      for (auto e: current_gen) 
        if (e.second == '>') {
          if (e.first.x == max_x) { if (current_gen[{0, e.first.y}] == '.') { newstate[{0, e.first.y}] = '>'; newstate[e.first] = '.'; moves++;}; }
          else                    { if (current_gen[e.first+_or] == '.')    { newstate[e.first+_or] = '>';    newstate[e.first] = '.'; moves++;}; }}
      current_gen = newstate;
      for (auto e: current_gen) 
        if (e.second == 'v') {
          if (e.first.y == max_y) { if (current_gen[{e.first.x, 0}] == '.') { newstate[{e.first.x, 0}] = 'v'; newstate[e.first] = '.'; moves++;}; }
          else                    { if (current_gen[e.first+_od] == '.')    { newstate[e.first+_od] = 'v';    newstate[e.first] = '.'; moves++;}; }}
      current_gen = newstate;
      return (moves > 0);
    };

    void place(vector2 key, char l) { current_gen[key] = l; max_x = std::max(max_x, key.x); max_y = std::max(max_y, key.y); };
    void print_automata() {
      printf("\033[2J");
      for (auto n: current_gen) 
        if (n.second)
          printf("\33[%d;%dH%c", n.first.y+2, n.first.x+1, n.second);
      printf("\33[39;49m\n\33[%d;%dH", 138, 0);
      std::cout << std::flush;
    };     
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  herd h;
  char c;
  int x(0), y(0);
  while (std::cin >> std::noskipws >> c) { if (c == '\n') { x = 0; y++; } else h.place({x++, y}, c); }
  int steps(1);
  while (h.advance_generation()) steps++;
  return {steps, 0};
}