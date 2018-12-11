#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

std::map<int,int> power_levels;

int calc_power_level(int serial, int x, int y) {
/*
  The rack ID is 3 + 10 = 13.
  The power level starts at 13 * 5 = 65.
  Adding the serial number produces 65 + 8 = 73.
  Multiplying by the rack ID produces 73 * 13 = 949.
  The hundreds digit of 949 is 9.
  Subtracting 5 produces 9 - 5 = 4.
  */
  return (((((x+10)*y)+serial)*(x+10)%1000)/100)-5;
}

int64_t calculate_power_cluster(int x, int y, int clustersize) {
  int64_t totalpower(0);
  for (int xo = 0; xo < clustersize; xo++)
    for (int yo = 0; yo < clustersize; yo++)
      totalpower += power_levels[((x+xo)*1000)+(y+yo)];
  return totalpower;
}


void solve() {
  int serial_number;
  std::cin >> serial_number;

  for (int x = 1; x <= 300; x++)
    for(int y = 1; y <= 300; y++) 
      power_levels[(x*1000)+y] = calc_power_level(serial_number, x, y);

  //std::cout << calculate_power_cluster(33, 45);
  int xx(0), yy(0), maxpower(-9999);
  for (int x = 1; x <= 297; x++)
    for(int y = 1; y <= 297; y++) {
      int totalpower = calculate_power_cluster(x, y, 3);
      if (totalpower > maxpower) {
        maxpower = totalpower;
        xx = x;
        yy = y;
      }
    }
  

  int xxx(0), yyy(0), maxpower2(-9999), siz(1);
  for (int size = 1; size <= 25 /* couldn't be larger right? */; size++) {
    for (int x = 1; x <= 300-size; x++)
      for(int y = 1; y <= 300-size; y++) {
        int totalpower = calculate_power_cluster(x, y, size);
        if (totalpower > maxpower2) {
          maxpower2 = totalpower;
          xxx = x;
          yyy = y;
          siz = size;
          std::cout << "New largest: " << xxx << "," << yyy << "," << siz << std::endl;
        }
      }
    std::cout << "Larger search area! " << size+1 << std::endl; 
  }


  std::cout << "Solution part 1: " << xx << "," << yy << std::endl << "Solution part 2: " << xxx << "," << yyy << "," << siz << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

