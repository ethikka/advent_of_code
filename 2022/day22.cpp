#include <sstream>
#include <map>
#include <set>
#include "../common/lib.h"
#include "../common/vector2.h"

std::string directions = ">v<^";
std::map<char, vector2> mof = { {'<', vector2(-1, 0)}, {'>', vector2(1, 0)}, {'^', vector2(0, -1)}, {'v', vector2(0, 1)} };
std::map<char, int> dof = { {'L', -1}, {'R', 1} };

struct warp {
  int x;
  int y;
  char newdir;
};

std::map<vector2,std::map<int,warp>> warpmap;

void generate_warpmap() {
  for (auto p: lerp({  0,100}, { 49,100})) warpmap[p].emplace(3, warp{50,      50+p.x,       0});
  for (auto p: lerp({ 50, 50}, { 50, 99})) warpmap[p].emplace(2, warp{p.y-50,  100,          1});
  for (auto p: lerp({ 50,149}, { 99,149})) warpmap[p].emplace(1, warp{49,      100+p.x,      2});
  for (auto p: lerp({ 49,150}, { 49,199})) warpmap[p].emplace(0, warp{p.y-100, 149,          3});
  for (auto p: lerp({100, 49}, {149, 49})) warpmap[p].emplace(1, warp{99,      p.x-50,       2});
  for (auto p: lerp({ 99, 50}, { 99, 99})) warpmap[p].emplace(0, warp{p.y+50,  49,           3});
  for (auto p: lerp({149,  0}, {149, 49})) warpmap[p].emplace(0, warp{99,      100+(49-p.y), 2});
  for (auto p: lerp({ 99,100}, { 99,149})) warpmap[p].emplace(0, warp{149,     149-p.y,      2});
  for (auto p: lerp({  0,199}, { 49,199})) warpmap[p].emplace(1, warp{p.x+100, 0,            1});
  for (auto p: lerp({100,  0}, {149,  0})) warpmap[p].emplace(3, warp{p.x-100, 199,          3});
  for (auto p: lerp({  0,150}, {  0,199})) warpmap[p].emplace(2, warp{p.y-100, 0,            1});
  for (auto p: lerp({ 50,  0}, { 99,  0})) warpmap[p].emplace(3, warp{0,       p.x+100,      0});
  for (auto p: lerp({  0,100}, {  0,149})) warpmap[p].emplace(2, warp{50,      149-p.y,      0});
  for (auto p: lerp({ 50,  0}, { 50, 49})) warpmap[p].emplace(2, warp{0,       (49-p.y)+100, 0});
};

void walk_a(int steps, int direction, vector2 &current, std::map<vector2,char> map) {
  vector2 newcurrent(current.x, current.y);
  for (int i = 0; i < steps; i++) {
    newcurrent = current+mof.at(directions[direction]);
    if (map.find(newcurrent) == map.end()) {
      vector2 tmpc(newcurrent);
      while (map.find(tmpc+mof.at(directions[(direction+2)%4])) != map.end()) tmpc = tmpc + mof.at(directions[(direction+2)%4]);
      if (map[tmpc] != '#') current = tmpc;
    } else if (map[newcurrent] != '#') current = newcurrent;
  }
}

void walk_b(int steps, int &direction, vector2 &current, std::map<vector2,char> map) {
  vector2 newcurrent(current.x, current.y);
  for (int i = 0; i < steps; i++) {
    newcurrent = current+mof.at(directions[direction]);
    if (map.find(newcurrent) == map.end()) {
      auto w = warpmap[current][direction];
      if (map[{w.x, w.y}] != '#') {
        current = vector2{ w.x, w.y };
        direction = w.newdir;
      }
    } else if (map[newcurrent] != '#')  current = newcurrent;
  }
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char inp;
  int x(0), y(0);
  std::string instructions;
  std::map<vector2,char> map;
  vector2 start_a(-1,-1), start_b(-1, -1);
  while (std::cin >> std::noskipws >> inp) {
    switch(inp) {
      case '.': if (start_a.x == -1) start_a = start_b = {x,y}; // no break; so we drop into the next statement
      case '#': map[{x++,y}] = inp; break; 
      case '\n': if (x == 0) break; x = 0; y++; break; /*next line*/
      default: { if (inp != ' ') { std::cin >> instructions; instructions = inp+instructions; }
        x++;
      }
    }
  }  

  int direction_a(0), direction_b(0), steps(0);
  generate_warpmap();
  for (int i = 0; i < instructions.size(); i++) {
    if (instructions[i] == 'L' || instructions[i] == 'R') {
      walk_a(steps, direction_a, start_a, map); direction_a = (direction_a + dof[instructions[i]]+4) % 4; 
      walk_b(steps, direction_b, start_b, map); direction_b = (direction_b + dof[instructions[i]]+4) % 4;
      steps = 0;
    } else {
      steps *= 10; steps += instructions[i]-'0';
    }
  }
  walk_a(steps, direction_a, start_a, map); res.first =  ((start_a.y+1)*1000)+((start_a.x+1)*4)+direction_a;
  walk_b(steps, direction_b, start_b, map); res.second = ((start_b.y+1)*1000)+((start_b.x+1)*4)+direction_b;
  return res;
}