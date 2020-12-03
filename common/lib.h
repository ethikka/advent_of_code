#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <chrono>
#include <utility>
#include <string>
#include <iomanip>

auto start_time = std::chrono::high_resolution_clock::now();

void post_solve(std::pair<int,int> res) {
  std::cout << "Solution part 1: " << res.first << std::endl << "Solution part 2: " << res.second << std::endl;
  std::cout << std::setprecision(3) << "Ran for " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count())/1000.0f << " microseconds" << std::endl;
}

#endif
