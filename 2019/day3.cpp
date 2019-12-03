#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <cmath>

void solve() {
  std::string line;
  int res1(99999999), res2(99999999), wirecount(0);
  std::map<int,std::map<int,std::map<int,int>>> linemap;

  while (std::getline(std::cin, line)) {
    wirecount++;
    int x(0), y(0);
    std::istringstream line2(line);
    std::string coord;
    int stepcount(0);
    for (std::string coord; std::getline(line2, coord, ',');) {
      int cnt = stoi(coord.substr(1)); 
      for (int i = 0; i < cnt; i++) {
        stepcount++;
        switch (coord[0]) {
          case 'L': x--; break;
          case 'R': x++; break;
          case 'D': y++; break;
          case 'U': y--; break;
        }
        if (linemap[x][y][wirecount] == 0) linemap[x][y][wirecount] = stepcount;
      }
    }
  }

  int tmp(0);
  for (auto wx: linemap) 
    for (auto wy: linemap[wx.first]) 
        if (linemap[wx.first][wy.first].size() > 1) {
          tmp = abs(wx.first)+abs(wy.first);
          if (tmp < res1) res1 = tmp;
          tmp = 0;
          for (auto wc: linemap[wx.first][wy.first])
            tmp += wc.second;
          if (tmp < res2) res2 = tmp;
        }

  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

