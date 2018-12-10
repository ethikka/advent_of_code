#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

struct pixel {
  int init_x;
  int init_y;
  int velo_x;
  int velo_y;
};

void solve() {
  std::string line;
  std::vector<pixel> pixels;

  // find opposing velocities!
  pixel forward, backwards;

  while (std::getline(std::cin, line)) {
    pixel p;
    scanf("position=<%d, %d> velocity=<%d,  %d>", &p.init_x, &p.init_y, &p.velo_x, &p.velo_y);
    if (p.velo_y == 1) forward = p;
    if (p.velo_y == -1) backwards = p;
    pixels.push_back(p);
  }
  // pixels pass each other at second [?]

  // -10003-125 = 125
  int middle = ((backwards.init_y+forward.init_y)/2);
  int seconds_b = (backwards.init_y - (middle*backwards.velo_y));
  int seconds_f = (forward.init_y - (middle*forward.velo_y));


  std::cout << middle << "#" << seconds_b << "::" << seconds_f<< std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

