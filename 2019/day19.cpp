#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include "intcode.h"

int res2 = 0;
int width = 100;
int lastx;

int diag(int y, intcode intpr) {
  int res(0), x(lastx);
  while (res == 0) {
    auto i = intpr.clone();
    i.inputqueue({++x, y});
    res = i.run();
  }

  auto i = intpr.clone();
  i.inputqueue({x+99, y-99});
  if (i.run() == 1) {
    return (x*10000+y-99);
  }
  lastx = x-1;
  return 0;
}

void solve() {
  int res1(0);
  intcode interpreter("./2019/fileinput.day19");
  for (int x = 49; x >= 0; x--)
    for (int y = 49; y >= 0; y--){
      auto i = interpreter.clone();;
      i.inputqueue({x, y});
      int res = i.run();
      if (res == 1) res1++;
    }

  int x(900),step(1);
  int d(0);
  while (d == 0) {
    x++;
    d = diag(x, interpreter);
  }
  res2 = d;
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

