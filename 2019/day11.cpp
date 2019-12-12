#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <chrono>
#include "intcode.h"

std::string colors[2] {" ", "#"};
std::string directions[4] { "U", "R", "D", "L"};
std::string colornames[2] { "black", "white"};


void print_plate(std::map<std::pair<int,int>,int> plate) {
  for(auto p: plate) 
    std::cout << "\033[" << p.first.first+4 << ";" << p.first.second+1 << "H" << colors[p.second];
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
//    std::cout << "at (" << vy << "," << -1*vx << ") which is currently " << colornames[plate[coord]];
    interpreter.inputqueue({(int)plate[coord]});
    plate[coord] = interpreter.run();
//    std::cout << ", new color will be " << colornames[plate[coord]] << ", facing " << directions[direction] << std::endl;

    direction = (interpreter.run() == 1)? (++direction+4) % 4 : (--direction+4) % 4;
    switch (direction) {
      case /*up*/   0: vx--; break;
      case /*down*/ 2: vx++; break;
      case /*right*/1: vy++; break;
      case /*left*/ 3: vy--; break;
    }
  }
  if (output_map)
    print_plate(plate);
  return plate.size();
}

void solve() {
  std::cout << "Solution part 1: " << std::endl << run_robot(0, false) << std::endl;
  //std::cout << "Solution part 2: " << std::endl;
  //run_robot(1, true);
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << std::endl << "Ran for " << ms_count << "ms" << std::endl;
}