#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "intcode.h" 

std::vector<int64_t> createinput(std::string input) {
  std::vector<int64_t> res;
  for(char c: input)
    res.push_back((int)c);
  res.push_back(10);
  return res;
}

void solve() {
  std::string line;
  int res1(0), res2(0);

  intcode interpreter("./2019/fileinput.day17");
  interpreter.poke(0, 2);
  interpreter.inputqueue(createinput("A,B,A,C,B,A,C,B,A,C"));  
  interpreter.inputqueue(createinput("L,6,L,4,R,12"));  
  interpreter.inputqueue(createinput("L,6,R,12,R,12,L,8"));  
  interpreter.inputqueue(createinput("L,6,L,10,L,10,L,6"));  
  interpreter.inputqueue({(int)'n'});  

  int x, lastchar;
  while (!interpreter.halted()) {
    x = interpreter.run(); 
    if (x < 255) std::cout << (char)x;
    // if (lastchar == 10 && x == 10) std::cout << "\33[H" << std::endl;//uncomment if you enable videofeed mode
    lastchar = x;
  }
  //std::cout << std::endl << "\33[46;1HSolution part B = " << x << std::endl;//uncomment if you enable videofeed mode
  std::cout << std::endl << "Solution part B = " << x << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

