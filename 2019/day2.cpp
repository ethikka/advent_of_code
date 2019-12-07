#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "intcode.h"

void solve() {
  int res1(0);
  intcode interpreter;
  interpreter.load("./2019/fileinput.day2");
  interpreter.poke(1, 12);
  interpreter.poke(2, 2);
  while (!interpreter.halted())
    res1 = interpreter.run();
  res1 = interpreter.peek(0);

  int res2(0);
  for (int i = 0; i < 100; i++) 
    for (int j = 0; j < 100; j++) {
      intcode interpreter2;
      interpreter2.load("./2019/fileinput.day2");
      interpreter2.poke(1, i);
      interpreter2.poke(2, j);
      int ress(0);
      while (!interpreter2.halted()) {
        interpreter2.run();
        if (interpreter2.peek(0) == 19690720)
          res2 = 100 * i + j;
      }
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
