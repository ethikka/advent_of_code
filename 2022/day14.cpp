#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include "../common/lib.h"

struct pos { 
  pos(int _x, int _y) { x = _x; y = _y; }
  pos(std::stringstream inp) { char d; inp >> x >> d >> y; }
  pos();
  int x; 
  int y; 
};

bool operator<(const pos& a, const pos& b) { if (a.y == b.y) return a.x < b.x; return a.y < b.y; }
pos operator+(const pos& a, const pos& b) { return {a.x+b.x, a.y+b.y}; }

std::vector<pos> lerp(pos from, pos to) {
  std::vector<pos> res;
  if (from.x == to.x || from.y == to.y) 
    for (int xx = 0; xx <= abs(from.x-to.x); xx++)
      for (int yy = 0, nx = to.x-from.x, ny = to.y-from.y; yy <= abs(from.y-to.y); yy++) 
        res.push_back({ from.x+((nx == 0) ? xx : (xx*(nx/abs(nx)))), from.y+((ny == 0) ? yy : (yy*(ny/abs(ny)))) });
  return res;
};

std::vector<pos> offsets = {{ -1, 1}, { 1, 1}, {0, 1}};

bool simulate(pos s, std::map<pos, char> &rocks) {
  while (true) {
    bool miss(true);
    for (auto o: offsets) {
      pos ns=s+o;
      if (rocks.find(ns) == rocks.end()) {
        if (ns.y > 162) return false;
        s = ns;
        miss &= false;
      } else 
        miss &= true;
    }
    if (miss) { 
      rocks[s] = 'o';
      break;
    }
  }
  return true;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::map<pos, char> rocks;
  int startx(500), starty(0);
  rocks[{startx,starty}] = '+';
  while (std::getline(std::cin, line)) {
    std::stringstream l(line);
    std::string pl, pr;
    l >> pl >> pr >> pr;
    do {
      for (auto p: lerp(std::stringstream(pl), std::stringstream(pr))) rocks[p] = '#';
      pl = pr;
      l >> pr >> pr;
    } while (!l.eof());
  }
 
  std::queue<int64_t> q;
  q.emplace(1);
  while (!q.empty()) {
    int64_t w = q.front();
    q.pop();

    pos s(startx, starty);
    if (simulate(s, rocks)) q.emplace(w+1);
    else                    res.first = w;
  }

  // Print the mofo
  for (int y = 0; y < 161; y++) {
    for (int x = 473; x < 578; x++) 
    if (rocks.find({x, y}) != rocks.end()) std::cout << rocks[{x,y}]; else std::cout << '.';
    std::cout << std::endl;
  }

  return res;
}

// 445 too low