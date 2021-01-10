#include <map>
#include <set>
#include <vector>
#include <iterator>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<char> input { std::istream_iterator<char>{ std::cin }, {}};
  int x(0), y(0), bx(0), by(0), rx(0), ry(0);
  bool realsanta = true;
  std::set<std::pair<int,int>> roadmap, roadmap_b;
  roadmap.insert({0,0});
  roadmap_b.insert({0,0});
  for(auto& i: input) {
    if      (i == '^') { x++; realsanta ? bx++ : rx++; }
    else if (i == 'v') { x--; realsanta ? bx-- : rx--; }
    else if (i == '<') { y--; realsanta ? by-- : ry--; }
    else if (i == '>') { y++; realsanta ? by++ : ry++; }

    roadmap.insert(std::make_pair(x, y));
    roadmap_b.insert(realsanta ? std::make_pair(bx, by) : std::make_pair(rx, ry));
    realsanta = !realsanta;
  }
  return { roadmap.size(), roadmap_b.size()};
}