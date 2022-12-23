#include <sstream>
#include <thread>
#include <tuple>
#include <cmath>
#include "../common/lib.h"
#include "../common/generationgrid.h"
#include "../common/vector2.h"

std::string rotation = "NSWE";

std::map<char, vector2> offsets = {{'N', { 0,-1}},
                                   {'S', { 0, 1}},
                                   {'W', {-1, 0}},
                                   {'E', { 1, 0}}};

std::map<char, std::vector<int>> lookups = {{'N', {{0,1,2}}},
                                            {'S', {{4,5,6}}},
                                            {'W', {{0,6,7}}},
                                            {'E', {{2,3,4}}}};

std::vector<vector2> osl = {{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};

vector2 check_node(vector2 c, std::unordered_map<vector2,bool> current_gen) {
  bool spots[8];
  int cnt(0);
  for(auto ol: osl) spots[cnt++] = (current_gen.find(c+ol) == current_gen.end());

  std::vector<char> possible_positions;
  for (int i = 0; i < 4; i++) {
    bool can_place(true);
    for (auto os: lookups[rotation[i]]) can_place &= spots[os];
    if (can_place) possible_positions.push_back(rotation[i]);
  };
  if (possible_positions.size() == 4 || possible_positions.size() == 0) return c;
  else                                                                  return c+offsets.find(possible_positions.front())->second;
};

bool check_change(vector2 c, std::vector<vector2> old_spots) {
  if (c == old_spots.front()) return false;
  return (old_spots.size() == 1);
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  generationgrid<vector2> a(&check_node, &check_change);

  char inp;
  int x(0), y(0), width(0);
  std::map<std::pair<int,int>,char> map;
  while (std::cin >> std::noskipws >> inp) {
    switch(inp) {
      case '#': a.place_pixel({x++, y}, true); break; /*elf*/
      case '\n': width = x; x = 0; y++; break; /*next line*/
      default: x++;
    }
  }

  int count(0);
  while (true) {
    if (count == 10) res.first = a.box_size()-a.get_raw().size();
    a.advance_generation();
    if (a.number_of_changes_last_gen == 0) { res.second = count+1; return res; }
    rotation += rotation[0];
    rotation = rotation.substr(1);
    count++;
  }
}