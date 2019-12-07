#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include "intcode.h"

int array[5] = {0,1,2,3,4};
bool part_b = false;
int res1(0), res2(0);

void swap(int x, int y){
  int temp = array[x];
  array[x]=array[y];
  array[y]=temp;
  return;
}

void runsimulation(int size){
  int i, boostres(0);
  if (!part_b) {
    for (i=0;i<size;i++) {
      intcode interpreter;
      interpreter.load("./2019/fileinput.day7");
      interpreter.inputqueue({array[i], boostres});
      boostres = interpreter.run();
    }
    res1 = std::max(res1, boostres); 
  } else {
    intcode intps[5];
    for (int i = 0; i < 5; i++) {
      intps[i].load("./2019/fileinput.day7");
      intps[i].inputqueue({array[i]});
    }
    intps[0].inputqueue({0});

    int intidx(0);
    while (true) {
      int res = intps[intidx].run();
      if (intps[4].halted()) {
        res2 = std::max(res2, res);
        return; 
      }
      ++intidx %= 5;
      intps[intidx].inputqueue({res});
    } 
  }
}

void permute(int k,int size){
  if (k==0)
    runsimulation(size);
  else {
    for (int i = k-1; i >= 0; i--) {
      swap(i, k-1);
      permute(k-1, size);
      swap(i, k-1);
    }
  }
}

void solve() {
  permute(5,5);
  part_b = true;
  for (int i = 0; i < 5; i++)
    array[i] += 5;
  permute(5,5);
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