// https://www.redblobgames.com/grids/hexagons/

#include <sstream>
#include <unordered_map>
#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::unordered_map<glm::ivec3,bool> floormap;
  std::unordered_map<std::string,glm::ivec3> neighbours{{ "e", { 1, -1,  0}}, { "w", { -1,  1,  0}}, {"ne", { 1,  0, -1}},	{"sw", { -1,  0,  1}}, {"se", { 0, -1,  1}},	{"nw", {  0,  1, -1}}};  
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (std::getline(std::cin, line)) {
    glm::ivec3 xyz = {0, 0, 0};
    for(int i = 0; i < line.size(); i++) {
      std::string dir = line.substr(i, 1);
      if (line[i] == 'n' || line[i] == 's') dir += line[++i];
      xyz += neighbours[dir];
    }
    floormap[xyz] = !floormap[xyz];
  }
  for (auto k: floormap) if (k.second) res.first++;

  for (int cnt = 1; cnt <= 100; cnt++) {
    std::unordered_map<glm::ivec3,int> sums;
    for(auto t: floormap) for(auto& n: neighbours) if (floormap[t.first]) ++sums[t.first + n.second];
    
    std::unordered_map<glm::ivec3,bool> next_gen;
		for(auto& s : sums) 
      if      (s.second == 1 && floormap[s.first]) next_gen[s.first] = true;
      else if (s.second == 2)                      next_gen[s.first] = true;

		floormap = next_gen;    
  }

  for (auto k: floormap) if (k.second) res.second++;
  return res;
}