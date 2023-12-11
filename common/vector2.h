#ifndef VECTOR2_H
#define VECTOR2_H

#include <vector>
#include <set>

struct vector2 {
  vector2(int _x, int _y) { x = _x; y = _y; }
  int x;
  int y;
  int64_t manhattanlength() { return abs(x)+abs(y); };
  std::string to_string() { return "("+std::to_string(x)+","+std::to_string(y)+") "; }
};

vector2 operator +(const vector2 &lhs, const vector2 &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y }; };
vector2 operator -(const vector2 &lhs, const vector2 &rhs) { return { lhs.x-rhs.x, lhs.y-rhs.y }; };
vector2 operator *(const vector2 &lhs, int mult) { return { lhs.x*mult, lhs.y*mult }; };
bool operator ==(const vector2 &lhs, const vector2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };
bool operator<(const vector2& a, const vector2& b) { if(a.y == b.y) return a.x < b.x; return a.y < b.y; };
bool operator>(const vector2& a, const vector2& b) { if(a.y == b.y) return a.x > b.x; return a.y > b.y; };

namespace std {
  template<> struct std::hash<vector2> { std::size_t operator()(const vector2& k)const { return hash<long long>()(((long long)k.x)^(((long long)k.y)<<32)); }; };
}

std::vector<vector2> lerp(vector2 min, vector2 max, vector2 ignore) {
  std::vector<vector2> res;
  for (int xx = min.x; xx <= max.x; xx++) 
  for (int yy = min.y; yy <= max.y; yy++)
    if (ignore.x != xx || ignore.y != yy) res.push_back({xx, yy});
  return res;
};


std::set<vector2> lerp(vector2 min, vector2 max) {
  std::set<vector2> res;
  for (int xx = min.x; xx <= max.x; xx++) 
  for (int yy = min.y; yy <= max.y; yy++) res.emplace(vector2{xx, yy});
  return res;
};
#endif