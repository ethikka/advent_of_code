#include <sstream>
#include <set>
#include <vector>
#include "../common/lib.h"

struct pos {
  int64_t x; 
  int64_t y;
};

std::set<pos> border;
bool operator<(const pos& a, const pos& b) { if(a.y == b.y) return a.x < b.x; return a.y < b.y; };

struct sensor {
  pos position;
  pos closest_beacon;
  int md;

  int64_t conditional_add(bool conditional, int64_t val) {
    if (conditional) return val;
    return 0;
  }

  void no_beacons(int64_t row, std::set<int64_t> &invalid_spots) {
    int64_t xx = std::abs(position.y-row);
    if (xx < md) {
      for (int i = 0; i <= (md-xx); i++) {
          invalid_spots.emplace(conditional_add((row != closest_beacon.y || (row == closest_beacon.y && closest_beacon.x != position.x+i)), position.x+i));
          invalid_spots.emplace(conditional_add((row != closest_beacon.y || (row == closest_beacon.y && closest_beacon.x != position.x-i)), position.x-i));
        }
      }
  };

  bool in_range(pos b) { return md >= std::abs(position.x-b.x)+std::abs(position.y-b.y); };
  bool between(int64_t c, int64_t min, int64_t max) { return (c >= min && c <= max); }

  void generate_border() {
    int mdx = md+1;
    for (int y = mdx, x = 0; x <= mdx; y--, x++) {
      if (between(position.x+x, 0, 4000000) && between(position.y+y, 0, 4000000)) border.emplace(pos {position.x+x, position.y+y});
      if (between(position.x+x, 0, 4000000) && between(position.y-y, 0, 4000000)) border.emplace(pos {position.x+x, position.y-y});
      if (between(position.x-x, 0, 4000000) && between(position.y+y, 0, 4000000)) border.emplace(pos {position.x-x, position.y+y});
      if (between(position.x-x, 0, 4000000) && between(position.y-y, 0, 4000000)) border.emplace(pos {position.x-x, position.y-y});
    }
  };
};

std::istream &operator>>(std::istream &is, sensor &s)
{
  std::string in, xx, yy;
  is >> in >> in >> xx >> yy >> in >> in >> in >> in;
  s.position.x = std::stoi(xx.substr(2, xx.size()-3));
  s.position.y = std::stoi(yy.substr(2, yy.size()-3));
  is >> xx >> yy;
  s.closest_beacon.x = std::stoi(xx.substr(2, xx.size()-3));
  s.closest_beacon.y = std::stoi(yy.substr(2, yy.size()-2));
  s.md = std::abs(s.position.x-s.closest_beacon.x)+std::abs(s.position.y-s.closest_beacon.y);
  return is;
}


std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<sensor> sensors;
  std::set<int64_t> invalid_spots;
  while (!std::cin.eof()) {
    sensor s;
    std::cin >> s;
    sensors.push_back(s);
  }
    
  for (auto s: sensors) s.no_beacons(2000000, invalid_spots);
  res.first = invalid_spots.size()-1;

  for (auto s: sensors) s.generate_border();
  for (auto p: border) {
    bool can_see(false);
    for (auto s: sensors) {
      can_see |= s.in_range(p);
      if (can_see) break;
    }
    if (!can_see) return { res.first, (p.x*4000000)+p.y };
  }
  return res;
}