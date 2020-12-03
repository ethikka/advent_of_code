#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <map>

void solve() {
  char inp;
  int res1(0);
  int x(0), y(0), width(0);
  std::map<std::pair<int,int>,char> map;
  while (std::cin >> std::noskipws >> inp) {
    switch(inp) {
      case '#': map[std::make_pair(y,x++)] = inp; break; /*tree*/
      case '\n': width = x; x = 0; y++; break; /*next line*/
      default: x++;
    }
  }

  int64_t tot(1);
  std::vector<std::tuple<int,int>> inputs({{1,1},{3,1},{5,1},{7,1},{1,2}});
  for(auto i: inputs) {
    int nx(0), hits(0);
    for (int ny = 0; ny <= y; ny += std::get<1>(i)) {
      if (map.find(std::make_pair(ny, nx % width)) != map.end()) hits++;
      nx += std::get<0>(i);
    }
    if (std::get<0>(i) == 3) res1 = hits;
    tot *= hits;
  }

  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << tot << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << " microseconds" << std::endl;
}

