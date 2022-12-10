#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "../common/lib.h"

struct pos {
  pos(int _x, int _y) { x = _x; y = _y; }
  int x;
  int y;
  int64_t key() { return y*100000+x; };
  void move(int _xo, int _yo) { x += _xo; y += _yo; };
};
std::map<char, pos> offsets = { {'L', {-1, 0}}, {'R', { 1, 0}}, {'U', { 0,-1}}, {'D', { 0, 1}}};

void ouroubourous(std::vector<pos> &knots, char dir, int steps, std::set<int64_t> &positions_a, std::set<int64_t> &positions_b) {
  for (int s = 0; s < steps; s++) {
    for (auto k = 0; k < knots.size(); k++) {
      if (k == 0) knots[k].move(offsets.at(dir).x, offsets.at(dir).y);
      else {
        pos p = { knots[k-1].x-knots[k].x, knots[k-1].y-knots[k].y };
        if (abs(p.x) > 1 || abs(p.y) > 1) { if (abs(p.x) > 0 && abs(p.y) > 0) { knots[k].move(p.x/abs(p.x), p.y/abs(p.y)); }
                                            else                              { knots[k].move(p.x/2, p.y/2);               }}} 
    }
    positions_a.emplace((knots.begin()+1)->key());
    positions_b.emplace(knots.rbegin()->key());
  }
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<pos> knots;
  std::set<int64_t> tail_positions_a, tail_positions_b;
  //std::map<int,std::set<int>> tail_positions_a, tail_positions_b;
  for (int i = 0; i < 10; i++) knots.push_back(pos(0,0));

  char dir;
  int steps(0);

  while (std::cin >> dir >> steps) ouroubourous(knots, dir, steps, tail_positions_a, tail_positions_b);
  return { tail_positions_a.size(), tail_positions_b.size() };
}