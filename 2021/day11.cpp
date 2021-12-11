#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <thread>
#include "../common/lib.h"

template<typename T>
std::vector<T> offsets();

struct vector2 {
  int x;
  int y;
};

template<>
std::vector<vector2> offsets() { return {{-1,-1},{-1, 0},{-1, 1},{ 0,-1},{ 0, 1},{ 1,-1},{ 1, 0},{ 1, 1}}; };
vector2 operator +(const vector2 &lhs, const vector2 &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y }; };
bool operator ==(const vector2 &lhs, const vector2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };

namespace std {
  template<> struct std::hash<vector2> {
    std::size_t operator()(const vector2& k)const { return hash<long long>()(((long long)k.x)^(((long long)k.y)<<32)); };
  };
}

class octoboard {
  private:
    int generation;
    std::unordered_map<vector2, int> _energymap;
  public:
    octoboard() {
    }
    void set_energy(vector2 v, int e) { _energymap[v] = e; }
    int advance() {
      std::unordered_map<vector2, int> _newmap;
      std::queue<vector2> q;

      for (auto n: _energymap) {
        _newmap[n.first] = _energymap[n.first]+1;
        if (_newmap[n.first] > 9) { _newmap[n.first] = 0; q.push({n.first}); }
      }
      while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for(const auto o: offsets<vector2>()) {
          vector2 _nk = v+o;
          if (_newmap.find(_nk) != _newmap.end()) {
            if (_newmap[_nk] != 0) _newmap[_nk]++; 
            if (_newmap[_nk] > 9) { _newmap[_nk] = 0; q.push(_nk); }
          }
        }
      }
      _energymap = _newmap;

      int res(0);
      for (auto n: _energymap) if (n.second == 0) res++;
      return res;
    }
    
    bool synced() {
      for (auto n: _energymap) if (n.second != 0) return false;
      return true;
    }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char c;
  octoboard ob;
  int x(1), y(1);
  while (std::cin >> std::noskipws >> c) {
    switch(c) {
      case '\n': x = 1; y++; break; 
      default: ob.set_energy({x++, y}, (int)c-48);
    }
  }

  while (!ob.synced()) {
    int r(0);
    r = ob.advance();
    if (res.second++ < 100) res.first += r;
  }
  return res;
}