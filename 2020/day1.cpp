#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cppitertools/combinations.hpp>

void solve() {
  int res1(0), res2(0), line(0);
  std::vector<int> e;
  while (std::cin >> line) 
    e.push_back(line);

  for (auto&& i: iter::combinations(e, 3)) {
    if (i[0] + i[1] == 2020 && res1 == 0)
      res1 = i[0] * i[1];
    if (i[0] + i[1] + i[2] == 2020 && res2 == 0)
      res2 = i[0] * i[1] * i[2];
  }
  
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << " microseconds" << std::endl;
}

