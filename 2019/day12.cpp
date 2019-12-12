#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <cmath>
#include <regex>
#include <vector>
#include <iomanip>

struct moon {
  int pos[3];
  int vel[3];
  int delta[3];

  int64_t kinetic_energy() { return (abs(pos[0])+abs(pos[1])+abs(pos[2]))*(abs(vel[0])+abs(vel[1])+abs(vel[2])); };
};

int stepcount = 1000;

moon initialvals[4] = { {{8,0,8},{0,0,0},{0,0,0}}, {{0,-5,-10},{0,0,0},{0,0,0}}, {{16,10,-5},{0,0,0},{0,0,0}}, {{19,-10,-7},{0,0,0},{0,0,0}} };
moon moons[4] =       { {{8,0,8},{0,0,0},{0,0,0}}, {{0,-5,-10},{0,0,0},{0,0,0}}, {{16,10,-5},{0,0,0},{0,0,0}}, {{19,-10,-7},{0,0,0},{0,0,0}} };

void step_simulation() {
  for (int mc = 0; mc < 4; mc++) 
    for (int mcc = 0; mcc < 4; mcc++) 
      if (mc != mcc) 
        for (int i = 0; i < 3; i++)
          if (moons[mc].pos[i] < moons[mcc].pos[i]) moons[mc].delta[i]++; else if (moons[mc].pos[i] > moons[mcc].pos[i]) moons[mc].delta[i]--;

  for (int mc = 0; mc < 4; mc++) 
    for (int i = 0; i < 3; i++) {
      moons[mc].vel[i] += moons[mc].delta[i];
      moons[mc].pos[i] += moons[mc].vel[i];
      moons[mc].delta[i] = 0;
    }
}

int64_t greatest_common_divisor(int64_t a, int64_t b) {
  if (a == 0) return b;
  return greatest_common_divisor(b % a, a);
}

int64_t least_common_multiple(int64_t a, int64_t b) {
  return (a * b) / greatest_common_divisor(a, b);
}

void solve() {
  int res1(0);
  int64_t res2(0);

  int64_t dimension_periodical[3] = { -1, -1 ,-1} ;

  for (int cnt = 0;; cnt++) {
    if (cnt == stepcount) 
      for (int mc = 0; mc < 4; mc++) 
        res1 += moons[mc].kinetic_energy();

    step_simulation();

    for (int dim = 0; dim < 3; dim++) {
      if (dimension_periodical[dim] == -1) {
        bool circ = true;
        for (int mc = 0; mc < 4; mc++) circ &= ((moons[mc].pos[dim] == initialvals[mc].pos[dim]) && (moons[mc].vel[dim] == initialvals[mc].vel[dim]));
        if (circ) dimension_periodical[dim] = cnt+1;
      }
    }
    if (dimension_periodical[0] != -1 && dimension_periodical[1] != -1 && dimension_periodical[2] != -1) break;
  }
  res2 = least_common_multiple(dimension_periodical[0], least_common_multiple(dimension_periodical[1], dimension_periodical[2]));

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

