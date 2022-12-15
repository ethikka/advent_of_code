#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> res(0,0);
 
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

std::vector<pos> offsets = {{0, 1}, { -1, 1}, { 1, 1}};

bool simulate(pos ss, std::map<pos, char> &rocks, bool inf) {
  pos s(ss);
  while (true) {
    bool bo(true);
    for (auto o: offsets) {
      if (bo) {
        pos ns=s+o;
        switch(rocks[ns]) {
          case '#':
          case 'x':
          case 'o': break;
          default: {
            if (ns.y > 162) { 
              rocks[ns] = 'x';
              if (res.first == 0) for (auto r: rocks) if (r.second == 'o') res.first++;
            }
            else {
              s = ns;
              if (inf) rocks[s] = '~';
              bo = false;
            };
          }
        }
      }
    }
    if (bo) { if (rocks[s] == 'o') return false; rocks[s] = 'o'; return true; }
  }
  return true;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
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
    for (auto p: lerp(std::stringstream(pl), std::stringstream(pr))) rocks[p] = '#';
  }
 
  std::queue<int64_t> q;
  q.emplace(1);
  while (!q.empty()) {
    int64_t w = q.front();
    q.pop();

    pos s(startx, starty);
    if (simulate(s, rocks, false)) {
      q.emplace(w+1);
      if (w % 10000 == 0) {
        int64_t total(0);
        for (auto r: rocks) if (r.second == 'o') total++;
      }
    }
    res.second = w-1;
  }
  return res;
}