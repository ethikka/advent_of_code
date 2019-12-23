#include <sstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "intcode.h"

void solve() {
  int res1(0), res2(0);
  intcode interpreter("./2019/fileinput.day21");

  auto intpr = interpreter.clone();
  intpr.inputqueue_text({"OR A J",
                         "AND B J",
                         "AND C J",
                         "NOT J J",
                         "AND D J",
                         "WALK"});
  while(!intpr.halted()) {
    intpr.run();
    int x = intpr.output();
    if (x > 255) res1 = x;
    else         std::cout << (char)x;
  }

  auto intpr2 = interpreter.clone();
  intpr2.inputqueue_text({"OR A J",
                          "AND B J",
                          "AND C J",
                          "NOT J J",
                          "AND D J",
                          "OR E T",
                          "OR H T",
                          "AND T J",
                          "RUN"});

  while(!intpr2.halted()) {
    intpr2.run();
    int x = intpr2.output();
    if (x > 255) res2 = x;
    else         std::cout << (char)x;
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

