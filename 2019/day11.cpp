#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <chrono>
#include <thread>
#include "intcode.h"

std::string colors[2] {"  ", "##"};

void print_plate(std::map<std::pair<int,int>,int> plate, int xx, int yy) {
  std::cout << "\033[0;0H" << std::endl; /* buffering gaat dan beter? geen idee waarom*/
  for(auto p: plate) 
    std::cout << "\033[" << p.first.first+5 << ";" << p.first.second*2+1 << "H" << colors[p.second];
  if (xx != -1)
    std::cout << "\033[" << xx+5 << ";" << yy*2+1 << "H" << "[]";
}

int run_robot(int initial_val, bool output_map) {
  int vx(0), vy(0);
  int direction = 0;
  std::map<std::pair<int,int>,int> plate;

  intcode interpreter;
  interpreter.load("./2019/fileinput.day11");
  plate[std::make_pair(vx, vy)] = initial_val;
  while (!interpreter.halted()) {
    auto coord = std::make_pair(vx, vy);
    interpreter.inputqueue({(int)plate[coord]});
    int col;
    if (interpreter.run() == outputMode)
       col = interpreter.output();  // no more rogue pixel
    if (interpreter.halted()) break;
    plate[coord] = col;
    if (output_map) {
      print_plate(plate, vx, vy);
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    interpreter.run();

    direction = (interpreter.output() == 1)? (++direction+4) % 4 : (--direction+4) % 4;
    switch (direction) {
      case /*up*/   0: vx--; break;
      case /*down*/ 2: vx++; break;
      case /*right*/1: vy++; break;
      case /*left*/ 3: vy--; break;
    }
  }
  if (output_map)
    print_plate(plate, -1, -1);
  return plate.size();
}

void solve() {
  std::cout << "Solution part 1: " << std::endl << run_robot(0, false) << std::endl;
  std::cout << "Solution part 2: " << std::endl;
  run_robot(1, true);
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << std::endl << "Ran for " << ms_count << "ms" << std::endl;
}