#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

void solve() {
  std::string quant, chr, pass;
  int res1(0), res2(0);
  while (std::cin >> quant >> chr >> pass) {
    int cnt = std::count(pass.begin(), pass.end(), chr[0]);
    int pos = quant.find('-');
    int minv = std::stoi(quant.substr(0, pos));
    int maxv = std::stoi(quant.substr(pos+1));
    if (cnt >= minv && cnt <= maxv)
      res1++;
    if (!(pass[minv-1] == chr[0]) != !(pass[maxv-1] == chr[0])) 
      res2++;
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

