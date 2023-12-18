#include <sstream>
#include <vector>
#include "../common/lib.h"

std::string dirs = "ULDR";
std::string HEX = "0123456789abcdef";

int64_t area(std::vector<std::pair<int, int>> laces) {
  int64_t x(0),y(0),area(0),b(0);
  std::vector<std::pair<int64_t, int64_t>> shape;
  for (auto l: laces) {
    switch (l.first) {
      case 0: x -= l.second; break;
      case 1: y -= l.second; break;
      case 2: x += l.second; break;
      case 3: y += l.second; break;
    }
    shape.emplace_back(x, y);
  }

  for (int64_t i = 0; i < laces.size(); ++i) {
    auto l1(shape[i]), l2(shape[(i + 1) % laces.size()]);
    area += (l1.first * l2.second - l2.first * l1.second);
    b += std::abs(l1.first - l2.first) + std::abs(l1.second - l2.second);
  }
  area = std::abs(area/2); 
  // area = https://en.wikipedia.org/wiki/Shoelace_formula
  // Pick's theorem = https://en.wikipedia.org/wiki/Pick%27s_theorem
  // Shoelace = i+(b/2)-1 ==> i = Shoelace-(b/2)+1
  // Area = Shoelace-(b/2)+1+b ==> {{{{-halve B + B = + halve B}}}} ==> Shoelace + (b/2) + 1
  return area+(b/2)+1;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<std::pair<int,int>> laces_a, laces_b;
  int cnt(0);
  std::string d,dir;

  while (std::cin >> dir >> cnt >> d) {
    laces_a.push_back({dirs.find(dir), cnt});
    cnt = 0;
    for (int i = 2; i < 7; i++) { cnt  = (cnt*16) + HEX.find(d[i]); }
    laces_b.push_back({3-(int)(d[7]-'0'), cnt});
  }
  return { area(laces_a),area(laces_b) };
}