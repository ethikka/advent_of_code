#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include "../common/lib.h"

struct voxel {
  voxel(): x(0), y(0), z(0) {};
  voxel(int _x, int _y, int _z) { x = _x, y = _y; z = _z; };
  int x;
  int y;
  int z;
  std::string to_string() { return std::to_string(x)+','+std::to_string(y)+','+std::to_string(z); };
};
voxel operator+(const voxel &lhs, const voxel &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z }; };
bool operator<(const voxel& a, const voxel& b){ return (a.x<b.x || (a.x==b.x && a.y<b.y) || (a.x==b.x && a.y==b.y && a.z<b.z)); }

std::set<voxel> lerp(voxel min, voxel max) {
  std::set<voxel> res;
  for (int xx = min.x; xx <= max.x; xx++) for (int yy = min.y; yy <= max.y; yy++) for (int zz = min.z; zz <= max.z; zz++) res.emplace(voxel( xx, yy, zz));
  return res;
};

std::vector<voxel> offsets() { return {{-1,0,0},{0,-1,0},{0,0,-1},{1,0,0},{0,1,0},{0,0,1}}; };

std::istream &operator>>(std::istream &is, voxel &v)
{
  char c;
  is >> v.x >> c >> v.y >> c >> v.z;
  return is;
};

int64_t floodfill(std::set<voxel> &voxels, std::set<voxel> &space, voxel start) {
  int64_t total(0);
  std::queue<voxel> q;
  q.emplace(start);
  std::set<voxel> visited;
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    if (visited.find(w) != visited.end()) continue;
    visited.emplace(w);
    for (voxel o: offsets()) {
      if (space.find(w+o) == space.end()) continue;     // outside the solvespace
      if (visited.find(w+o) != visited.end()) continue; // already checked
      if (voxels.find(w+o) != voxels.end()) ++total;
      else q.emplace(w+o);
    }
  }
  return total;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::set<voxel> voxels;
  voxel min(9999,9999,9999), max(0,0,0);
  while (!std::cin.eof()) {
    voxel v;
    std::cin >> v;
    voxels.emplace(v);
    min.x = std::min(v.x-2, min.x); min.y = std::min(v.y-2, min.y); min.z = std::min(v.z-2, min.z); max.x = std::max(v.x+2, max.x); max.y = std::max(v.y+2, max.y); max.z = std::max(v.z+2, max.z);
  }
  std::set<voxel> space = lerp(min, max);

  for (auto v: voxels) for (auto o: offsets()) if (voxels.find(v+o) == voxels.end()) res.first++;
  res.second = floodfill(voxels, space, min);
  return res;
}