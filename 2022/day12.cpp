#include <sstream>
#include <queue>
#include <vector>
#include <map>
#include <tuple>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::int64_t res(99999999);
  std::vector<std::pair<int,int>> offsets= { {-1,0}, {1,0}, {0,-1}, {0,1}};
  char inp;

  char map[128][128];
  int steps_a[128][128], steps_b[128][128];
  int mx(0), my(0), sx(0), sy(0), ex(0), ey(0);
  std::queue<std::tuple<int64_t,int64_t,int64_t>> q;

  while (std::cin >> std::noskipws >> inp) {
    switch (inp) {
      case '\n': mx = 0; my++; break;
      case 'S': sx = mx; sy = my; map[mx++][my] = 'a'; break;
      case 'E': ex = mx; ey = my; map[mx++][my] = 'z'; break;
      default:  map[mx++][my] = inp;
    }
  };

  q.push({sx, sy, 0});
  steps_a[sx][sy] = 0;
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    for(auto o: offsets) {
      int nx(std::get<0>(w)+o.first), ny(std::get<1>(w)+o.second);
      if(nx < 0 || nx > mx || ny < 0 || ny > my) continue;
      if (((map[nx][ny]-map[std::get<0>(w)][std::get<1>(w)]) < 2) && (steps_a[nx][ny] == 0 || steps_a[nx][ny] > std::get<2>(w)+1)) 
        q.push({nx, ny, steps_a[nx][ny] = std::get<2>(w)+1});
    }
  }

  q.push({ex, ey, 0});
  steps_b[ex][ey] = 0;
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    for(auto o: offsets) {
      int nx(std::get<0>(w)+o.first), ny(std::get<1>(w)+o.second);
      if(nx < 0 || nx > mx || ny < 0 || ny > my || std::get<2>(w) > res) continue;
      if (((map[std::get<0>(w)][std::get<1>(w)]-map[nx][ny]) < 2) && (steps_b[nx][ny] == 0 || steps_b[nx][ny] > std::get<2>(w)+1)) {
        if (map[nx][ny] == 'a' && std::get<2>(w)+1 < res) res = std::get<2>(w)+1;
        q.push({nx, ny, steps_b[nx][ny] = std::get<2>(w)+1});
      }
    }
  }
  return { steps_a[ex][ey], res }; 
}