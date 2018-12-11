#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <set>

struct pixel {
  int init_x;
  int init_y;
  int velo_x;
  int velo_y;
};

void print_at(std::vector<pixel> pixels, int time) {
  std::map<int, std::set<int>> pxs;

  for(auto p: pixels) {
    int px = p.init_x + (p.velo_x*time);
    int py = p.init_y + (p.velo_y*time);
    if (pxs.count(px) == 0) pxs.insert({ px, { py }});
    else
      pxs[px].insert(py);
  }

  int min_x(9999), max_x(0), min_y(9999), max_y(0);
  for(auto x: pxs) 
    for(auto y: pxs[x.first]) {
      if (x.first < min_x) min_x = x.first;
      if (y < min_y) min_y = y;
      if (x.first > max_x) max_x = x.first;
      if (y > max_y) max_y = y;
    }

  std::cout << std::endl;
  for(int yy = min_y; yy <= max_y; yy++) {
    for(int xx = min_x; xx <= max_x; xx++)
      std::cout << (pxs.count(xx) > 0 ? (pxs[xx].count(yy) > 0 ? "O" : ".") : ".");
    std::cout << std::endl;;
  }
}

void solve() {
  std::string line;
  std::vector<pixel> pixels;

  pixel forward, backwards;
  int min_pxl(99999), max_pxl(99999);

  while (std::getline(std::cin, line)) {
    pixel p;
    sscanf(line.c_str(), "position=<%d, %d> velocity=<%d,  %d>", &p.init_x, &p.init_y, &p.velo_x, &p.velo_y);
    if (p.velo_y ==  1 && min_pxl > p.init_y) { forward   = p;  min_pxl = p.init_y; }
    if (p.velo_y == -1 && max_pxl > p.init_y) { backwards = p;  max_pxl = p.init_y; }
    pixels.push_back(p);
  }

  int marge = 0;
  int middle = backwards.init_y-((backwards.init_y+forward.init_y)/2);
  std::cout << "At second " << middle << " the output looks like this" << std::endl;
  for(int i = middle-marge; i <= middle+marge; i++)
    print_at(pixels, i);
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

