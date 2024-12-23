#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <chrono>
#include <utility>
#include <string>
#include <iomanip>
#include <cmath>

bool output_for_timing(false);

auto start_time = std::chrono::high_resolution_clock::now();

void reset_start_timer() {
  start_time = std::chrono::high_resolution_clock::now();
}

void output_current_timer() {
  std::cout << std::fixed << std::setprecision(3) << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count())/1000.0f << "µs" << std::endl;
}

void post_solve(std::pair<std::uintmax_t,std::uintmax_t> res) {
  if (output_for_timing)
    std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_time).count());
  else
  {
    std::cout << "Solution part 1: " << res.first << std::endl << "Solution part 2: " << res.second << std::endl;
    std::cout << std::fixed << std::setprecision(3) << "Ran for " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count())/1000.0f << "µs" << std::endl;
  }
  ;
}

int manhattan(int x, int y) {
  return abs(x)+abs(y);
};

std::pair<std::uintmax_t,std::uintmax_t> solve();

/* Ugly, but effective ;-)) */
int main(int argc, char *argv[]) {
  std::string s = argv[0];
  s += " ";
  output_for_timing = (argc > 1);
  post_solve(solve());
}

#endif
