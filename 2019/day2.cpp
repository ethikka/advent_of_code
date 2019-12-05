#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "intcode.h"

void solve() {
  intcode interpreter;
  interpreter.load("./2019/fileinput.day2");
  interpreter.poke(1, 12);
  interpreter.poke(2, 2);
  int res1 = interpreter.run();

  int res2(0);
  for (int i = 0; i < 100; i++) 
    for (int j = 0; j < 100; j++) {
      intcode interpreter2;
      interpreter2.load("./2019/fileinput.day2");
      interpreter2.poke(1, i);
      interpreter2.poke(2, j);
      if (interpreter2.run() == 19690720) {
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

