#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

int run(std::vector<int> code, int pos_1, int pos_2) {
  int idx(0);
  code[1] = pos_1;
  code[2] = pos_2;

  while (true) {
    switch(code[idx]) {
      case  1: code[code[idx+3]] = code[code[idx+1]] + code[code[idx+2]];
               break;
      case  2: code[code[idx+3]] = code[code[idx+1]] * code[code[idx+2]];
               break;
      case 99: return code[0];
    }
    idx += 4;
  }
  return -1;
}

void solve() {
  std::string line;
  std::vector<int> intcode;
  int res2(0);
  while (std::getline(std::cin, line, ',')) 
    intcode.push_back(std::stoi(line));
 
  std::vector<int> intcode_b(intcode);
  for (int i = 0; i < intcode_b.size(); i++) 
		for (int j = 0; j < intcode_b.size(); j++) 
			if (run(intcode_b, i, j) == 19690720) 
				res2 = 100 * i + j;
  std::cout << "Solution part 1: " << run(intcode, 12, 2) << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

