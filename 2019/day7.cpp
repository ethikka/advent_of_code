#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <array>
#include <algorithm>
#include "intcode.h"

int runsimulation(std::array<int,5> array, bool part_b, int res) {
  if (!part_b) {
    int boostres(0);
    for (int i=0;i<5;i++) {
      intcode interpreter;
      interpreter.load("./2019/fileinput.day7");
      interpreter.inputqueue({array[i], boostres});
      boostres = interpreter.run();
    }
    return std::max(res, boostres); 
  } else {
    intcode intps[5];
    for (int i = 0; i < 5; i++) {
      intps[i].load("./2019/fileinput.day7");
      intps[i].inputqueue({array[i]});
    }
    intps[0].inputqueue({0});

    int intidx(0);
    while (true) {
      int boostres = intps[intidx].run();
      if (intps[4].halted()) return std::max(res, boostres);
      ++intidx %= 5;
      intps[intidx].inputqueue({boostres});
    } 
  }
}

void solve() {
  int res1(0), res2(0);

  std::array<int,5> part_a{0, 1, 2, 3, 4};
  do  res1 = runsimulation(part_a, false, res1);
  while(std::next_permutation(part_a.begin(), part_a.end()));
  
  std::array<int,5> part_b{5, 6, 7, 8, 9};
  do  res2 = runsimulation(part_b, true, res2);
  while(std::next_permutation(part_b.begin(), part_b.end()));

  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "us" << std::endl;
}