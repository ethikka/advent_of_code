#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "intcode.h"


//<ESC>[{attr1};...;{attrn}m


std::string colors[6] {"  ", "##", "[]", "==", "()", " "};
std::string colorcode[6] {"\33[0m", "\33[37;47m", "\33[34;44m", "\33[35;46m", "\33[37;47m"};

void print_pixel(int x, int y, int val, int speed) {
  std::cout << std::endl;;
    if (x >= 0 && y >= 0 && val < 6 ) {
      if (val == 2)
        std::cout << "\33[" << ((x*97+y) % 5) + 31 << ";" << ((x*97+y) % 5) + 41 << "m";
      else
        std::cout << colorcode[val];
      std::cout << "\033[" << y+5 << ";" << x*2+5 << "f" << colors[val];
      std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}


int run_game(bool cheat) {
  int res(0);
  intcode interpreter;
  interpreter.load("./2019/fileinput.day13");
  if (cheat) {
    interpreter.poke(0, 2);
    for (int idx = 0;;idx++) 
      if (interpreter.peek(idx) == 0 && interpreter.peek(idx+1) == 3 && interpreter.peek(idx+2) == 0) {
        std::cout << "\33[26;8H" << "\33[0m" << "Building a wall ;-)";
        for (int idxrel = idx; interpreter.peek(idxrel) == 0; idxrel--) { interpreter.poke(idxrel, 1); print_pixel(idxrel-idx+19, 19, 1, 250); }
        for (int idxrel = idx+2; interpreter.peek(idxrel) == 0; idxrel++) { interpreter.poke(idxrel, 1); print_pixel(idxrel-idx+19, 19, 1, 250); }
        break;
      }
  }

  while (!interpreter.halted()) {
    if (cheat) interpreter.inputqueue({0});
    int x = interpreter.run(); 
    int y = interpreter.run();
    int val = interpreter.run();
    if (interpreter.halted()) { if (cheat) std::cout << "\33[28;0H"; return res; }
    print_pixel(x, y, val, 1);


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
  run_game(false);
  std::cout << /*"Solution part 1: " << run_game(false) << std::endl << "Solution part 2: " <<*/ run_game(true) << std::endl;
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}