#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "intcode.h"

void solve() {
  intcode interpreter;
  std::string line;
  std::vector<int> intcode;
  int res2(0);
  while (std::getline(std::cin, line, ',')) 
    intcode.push_back(std::stoi(line));
 
  std::vector<int> intcode_b(intcode);
  for (int i = 0; i < 100; i++) 
		for (int j = 0; j < 100; j++) 
			if (interpreter.run(intcode_b, i, j) == 19690720) 
				res2 = 100 * i + j;
  std::cout << "Solution part 1: " << interpreter.run(intcode, 12, 2) << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

