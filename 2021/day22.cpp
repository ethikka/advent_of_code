#include <sstream>
#include <vector>
#include <cmath>
#include "../common/lib.h"

struct cube {
  int xs, xe, ys, ye, zs, ze;
  cube(int xs, int xe, int ys, int ye, int zs, int ze):  xs(xs), xe(xe), ys(ys), ye(ye), zs(zs), ze(ze){}

  std::uintmax_t size(bool part_a){
    if (part_a && (xs<=-50 || xe>=50 || ys<=-50 || ye>=50 || zs<=-50 || ze>=50))  return 0;
    std::uintmax_t out = xe-xs+1; out*= ye-ys+1; out*= ze-zs+1;
    return out;
  }
};

bool intersects(cube& a, cube& b){ 
  return !(a.xe<b.xs || b.xe<a.xs || a.ye<b.ys || b.ye<a.ys|| a.ze<b.zs || b.ze<a.zs);
}

void subtract(cube& a, cube& b, std::vector<cube>& build){
  cube c(std::max(a.xs, b.xs), std::min(a.xe, b.xe), std::max(a.ys, b.ys), std::min(a.ye, b.ye),std::max(a.zs, b.zs), std::min(a.ze, b.ze));
  if(a.zs<c.zs) build.emplace_back(a.xs, a.xe, a.ys, a.ye, a.zs, c.zs-1);
  if(c.ze<a.ze) build.emplace_back(a.xs, a.xe, a.ys, a.ye, c.ze+1, a.ze);
  if(a.xs<c.xs) build.emplace_back(a.xs, c.xs-1, a.ys, a.ye, c.zs, c.ze);
  if(c.xe<a.xe) build.emplace_back(c.xe+1, a.xe, a.ys, a.ye, c.zs, c.ze);
  if(a.ys<c.ys) build.emplace_back(c.xs, c.xe, a.ys, c.ys-1, c.zs, c.ze);
  if(c.ye<a.ye) build.emplace_back(c.xs, c.xe, c.ye+1, a.ye, c.zs, c.ze);
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<cube> cubes;
  std::string line;
  while (std::cin.peek() != EOF) {
    std::getline(std::cin, line);
    std::stringstream ssl(line.substr(line.find('=')));
    int xs, xe, ys, ye, zs, ze;
    char tr;
    ssl >> tr >> xs >> tr >> tr >> xe >> tr >> tr >> tr >> ys >> tr >> tr >> ye >> tr >> tr >> tr >> zs >> tr >> tr >> ze;
    cube cur(xs, xe, ys, ye, zs, ze);
    std::vector<cube> build;
    for(auto& c: cubes)
      if(intersects(c, cur)) subtract(c, cur, build);
      else                   build.push_back(c);
    if(line[1] == 'n') build.push_back(cur); // on
    cubes = std::move(build);
  }
  for(auto& c: cubes){
    res.first += c.size(true);
    res.second += c.size(false);
  }
  return res;
}