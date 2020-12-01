#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

void solve() {
  int res1(0), res2(0), line(0);
  std::vector<int> e;
  while (std::cin >> line) {
    e.push_back(line);
  }

  for (int ii = 0; ii < e.size()-1; ii++)
    for (int jj = ii + 1; jj < e.size(); jj++)
      if (e[ii]+e[jj] == 2020) 
        res1 = e[ii] * e[jj];

  for (int ii = 0; ii < e.size()-2; ii++)
    for (int jj = ii + 1; jj < e.size()-1; jj++)
       for (int kk = jj + 1; kk < e.size(); kk++)
         if ((e[ii]+e[jj]+e[kk]) == 2020)
           res2 = e[ii] * e[jj] * e[kk];

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

