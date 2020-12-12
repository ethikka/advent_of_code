#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  int cx(0), cy(0), wx(10), wy(-1), sx(0), sy(0), facing(90);

  while (std::cin >> line) {
    int num = std::stoi(line.substr(1));
    switch(line[0]) {
      case 'N': cy -= num; wy -= num; break;
      case 'E': cx += num; wx += num; break;
      case 'S': cy += num; wy += num; break;
      case 'W': cx -= num; wx -= num; break;
      case 'L': {
        facing = ((facing+360) - num) % 360; 
        int tmp = wx;
        switch(num) {
          case 90:  wx = wy;    wy = tmp*-1; break;
          case 180: wx = wx*-1; wy = wy *-1; break;
          case 270: wx = wy*-1; wy = tmp;    break;
        }
        break;
      }
      case 'R': {
        facing = ((facing+360) + num) % 360; 
        int tmp = wx;
        switch(num) {
          case  90: wx = wy*-1; wy = tmp;    break;
          case 180: wx = wx*-1; wy = wy *-1; break;
          case 270: wx = wy;    wy = tmp*-1; break;
        }
        break;
      }
      case 'F': {
        sx += wx*num; sy += wy*num;
        switch((facing+360) % 360) {
          case   0: cy -= num; break; /* N */
          case  90: cx += num; break; /* E */
          case 180: cy += num; break; /* S */
          case 270: cx -= num; break; /* W */
        }
        break;
      }
    }
  }
  res.first = manhattan(cx, cy);
  res.second = manhattan(sx, sy);
  return res;
}

int main(int argc, char *argv[]) {
  output_for_timing = (argc > 1);
  post_solve(solve());
}
