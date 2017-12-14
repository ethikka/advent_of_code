
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <chrono>

std::map<int,int> scanners;

bool remove_char(char c)
{
  return c == ':';
}

int calc_penalty(int delay) {
  int penalty = 0;
  for(auto s: scanners) {
    if ((s.first + delay) % ((s.second -1) * 2) == 0)
      penalty += (delay == 0) ? (s.first * s.second) : 1;
    if (delay != 0 && penalty > 0)
      return 1;
  }
  return penalty;
}

void solve(void) {
  std::string line;
  while (std::getline(std::cin, line)) {
    int scanner_index, scannerlength;
    line.erase(std::remove_if(line.begin(), line.end(), &remove_char), line.end());
    std::istringstream ssl(line);

    ssl >> scanner_index >> scannerlength;
    scanners[scanner_index] = scannerlength;
  }
  int penalty = -1;
  int delay = 0;
  int penalty_part_1 = calc_penalty(0);
  while(penalty != 0) {
    delay++;
    penalty = calc_penalty(delay);
  }
  std::cout << "Solution part 1: " << penalty_part_1 << std::endl << "Solution part 2: " << delay << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

