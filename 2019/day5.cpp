#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "intcode.h"

void solve() {
  int res1(0), res2(0);

  intcode interpreter;
  interpreter.load("./2019/fileinput.day5");
  interpreter.inputqueue({1}); 
  while (!interpreter.halted()) {
    if (interpreter.run() == outputMode)
      res1 = interpreter.output();
  }
  
// 11933517
  intcode interpreter2;
  interpreter2.load("./2019/fileinput.day5");
  interpreter2.inputqueue({5}); 
  while (!interpreter2.halted())
    if (interpreter2.run() == outputMode)
      res2 = interpreter2.output();
// 10428568
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

