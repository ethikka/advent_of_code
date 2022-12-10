#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "../common/lib.h"

struct pos {
  pos(int _x, int _y) { x = _x; y = _y; }
  int x;
  int y;
  std::string key() { return std::to_string(y)+";"+std::to_string(x); };
  void move(int _xo, int _yo) { x += _xo; y += _yo; };
};
std::map<char, pos> offsets = { {'L', {-1, 0}}, {'R', { 1, 0}}, {'U', { 0,-1}}, {'D', { 0, 1}}};

void ouroubourous(std::vector<pos> &knots, char dir, int steps, std::set<std::string> &positions) {
  for (int s = 0; s < steps; s++, positions.emplace(knots.rbegin()->key())) 
    for (auto k = 0; k < knots.size(); k++) {
      if (k == 0) knots[k].move(offsets.at(dir).x, offsets.at(dir).y);
      else {
        pos p = { knots[k-1].x-knots[k].x, knots[k-1].y-knots[k].y };
        if (abs(p.x) > 1 || abs(p.y) > 1) { if (abs(p.x) > 0 && abs(p.y) > 0) { knots[k].move(p.x/abs(p.x), p.y/abs(p.y)); }
                                            else                              { knots[k].move(p.x/2, p.y/2);               }}} 
    }
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<pos> knots_a, knots_b;
  std::set<std::string> tail_positions_a, tail_positions_b;
  knots_a.push_back(pos(0,0));
  knots_a.push_back(pos(0,0));
  for (int i = 0; i < 10; i++)
    knots_b.push_back(pos(0,0));

  char dir;
  int steps(0);

  while (std::cin >> dir >> steps) {
    ouroubourous(knots_a, dir, steps, tail_positions_a);
    ouroubourous(knots_b, dir, steps, tail_positions_b);
  }
  return { tail_positions_a.size(), tail_positions_b.size() };
}