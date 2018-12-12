// God bless https://en.wikipedia.org/wiki/Summed-area_table
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <stdio.h>

int power_levels[301][301];

void solve() {
  int serial_number;
  std::cin >> serial_number;

  for (int x = 1; x <= 300; x++)
    for(int y = 1; y <= 300; y++)  {
      int id = x+10;
      int p = (id*y)+serial_number;
      p = (p * id) /100 % 10 - 5;
      power_levels[x][y] = p + power_levels[x - 1][y] + power_levels[x][y - 1] - power_levels[x - 1][y - 1];
    }

  std::string part1 = "";
  int xx(0), yy(0), maxpower(-9999), siz(1);
  for (int size = 1; size <= 300; size++) {
    for (int x = size; x <= 300-size; x++)
      for(int y = size; y <= 300; y++) {
        int totalpower = power_levels[x][y] - power_levels[x-size][y] - power_levels[x][y-size] + power_levels[x-size][y-size];
        if (totalpower > maxpower) {
          maxpower = totalpower;
          xx = x;
          yy = y;
          siz = size;
        }
      }
    if (size == 3) {
      part1 = std::to_string(xx-2)+","+std::to_string(yy-2);
    }
  }
  std::cout << "Solution part 1: " << part1 << std::endl << "Solution part 2: " << xx-siz+1 << "," << yy-siz+1 << "," << siz << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

