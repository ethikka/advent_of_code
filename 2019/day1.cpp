#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

void solve() {
  std::string line;
  int res1(0), res2(0);
  float mass(0), fuelmass(0);
  while (std::cin >> mass) {
    mass = std::floor(mass / 3) - 2;
    res1 += mass;
    
    fuelmass = mass;
    while (fuelmass > 0) {
      fuelmass = std::floor(fuelmass / 3) - 2;
      if (fuelmass > 0) 
        res2 += fuelmass;
    }
  }
  res2 += res1;
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

