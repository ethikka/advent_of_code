#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "intcode.h"

int run_game(bool cheat) {
  int res(0);
  intcode interpreter;
  interpreter.load("./2019/fileinput.day13");
  if (cheat) {
    interpreter.poke(0, 2);
    for (int idx = 0;;idx++) 
      if (interpreter.peek(idx) == 0 && interpreter.peek(idx+1) == 3 && interpreter.peek(idx+2) == 0) {
        for (int idxrel = idx; interpreter.peek(idxrel) == 0; idxrel--) interpreter.poke(idxrel, 1);
        for (int idxrel = idx+2; interpreter.peek(idxrel) == 0; idxrel++) interpreter.poke(idxrel, 1);
        break;
      }
  }

  while (!interpreter.halted()) {
    if (cheat) interpreter.inputqueue({0});
    interpreter.run(); interpreter.run(); interpreter.run();
    int x = interpreter.output();; 
    int y = interpreter.output();
    int val = interpreter.output();
    if (interpreter.halted()) return res;
    if (!cheat && val == 2) 
      res++;
    else if (cheat && x == -1 && y == 0) 
      res = val;
  }
}

int main(void) {
  std::cout << "\33[?12l";
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  std::cout << "Solution part 1: " << run_game(false) << std::endl << "Solution part 2: " << run_game(true) << std::endl;
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}