#include <sstream>
#include <set>
#include <vector>
#include "../common/lib.h"

struct pos {
  int64_t x; 
  int64_t y;
};

struct sensor {
  pos position;
  pos closest_beacon;
  int md;

  int64_t conditional_add(bool conditional, bool part_2, int64_t val) {
    if (conditional && !part_2) return val;
    if (part_2 && val >= 0 && val <= 4000000 && conditional) return val;
    return -9999999;
  }

  void no_beacons(int64_t row, std::set<int64_t> &invalid_spots, bool part_2) {
    int64_t xx = std::abs(position.y-row);
    if (part_2) std::cout << xx << std::endl;
    if (xx < md) {
      for (int i = 0; i <= (md-xx); i++) {
          invalid_spots.emplace(conditional_add((row != closest_beacon.y || (row == closest_beacon.y && closest_beacon.x != position.x+i)), part_2, position.x+i));
          invalid_spots.emplace(conditional_add((row != closest_beacon.y || (row == closest_beacon.y && closest_beacon.x != position.x-i)), part_2, position.x-i));
        }
      }
  };
  void print() { std::cout << position.x << "," << position.y << " | " << closest_beacon.x << "," << closest_beacon.y << "  " << md << std::endl; };
};

std::istream &operator>>(std::istream &is, sensor &s)
{
  std::string in, xx, yy;
  //Sensor at x=2, y=18: closest beacon is at x=-2, y=15  
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
    
  for (auto s: sensors) {
    s.no_beacons(2000000, invalid_spots, false);
  }
  res.first = invalid_spots.size()-1;

  invalid_spots.clear();
  for (auto s: sensors)  
    s.no_beacons(0, invalid_spots, true);
  std::cout << invalid_spots.size()-1;
  //4000000
  return res;
}