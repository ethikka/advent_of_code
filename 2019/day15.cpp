#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <queue>
#include <cmath>
#include <thread>
#include "intcode.h"
#include "gif.h"

int x_size = 42;
int y_size = 42;
int delay = 1;
int framecounter = 0;
char statuschars[3] = {'#', '.', 'O'};
std::string colorcode[3] {"\33[37;47m", "\33[30;40m", "\33[34;44m"};

struct coord { int x; int y; };
enum dr { north = 1, south = 2, west = 3, east = 4 };
static const dr alldirections[] = { north, south, west, east };

void print_map(GifWriter* g, std::map<std::pair<int,int>,std::pair<int,int>> map, bool paintAnyway) {
  framecounter++;
  if ((framecounter % 4) != 0 && !paintAnyway) return; 
  int xoff(9999), yoff(9999);
  for(auto p: map) {
    xoff = std::min(p.first.first, xoff);
    yoff = std::min(p.first.second, yoff);
  }
  std::vector<uint8_t> black(x_size * y_size * 4, 0);
  for(auto p: map) {
    int x = p.first.first+(-1*xoff);
    int y = p.first.second+(-1*yoff);
    int offset = ((x+1)*x_size + (y+1)) * 4;
    switch (p.second.first)
    {
      case 1: 
        black[offset] = 255;
        black[offset+1] = 255;
        black[offset+2] = 255;
        break;
      case 2: 
        black[offset+2] = 255;
        break;
    }
  } 
  GifWriteFrame(g, black.data(), x_size, y_size, delay);
}

struct worker {
  intcode interpreter;
  dr direction; 
  std::pair<int,int> coord;
  int stepcount;
};

struct oxy {
  std::pair<int,int> coord;
  int stepcount;
};

std::pair<int,int> newcoord(std::pair<int,int> coord, dr direction) {
  switch (direction) {
    case north: return std::make_pair(coord.first, coord.second+1);
    case south: return std::make_pair(coord.first, coord.second-1);
    case west : return std::make_pair(coord.first-1, coord.second);
    case east : return std::make_pair(coord.first+1, coord.second);
  }
}

void solve() {
  int res1(0), res2(0);
  intcode interpreter("./2019/fileinput.day15");

  GifWriter g;
  GifBegin(&g, "day15.gif", x_size, y_size, delay);

  std::map<std::pair<int,int>,std::pair<int,int>> map;
  std::queue<worker> work;
  auto coord = std::make_pair(0,0);
  map[coord] = std::make_pair('.', 1);
  for(auto d: alldirections) 
    work.push(worker{interpreter.clone(), d, coord, 1});

  while(!work.empty()) {
    auto w = work.front();
    w.interpreter.inputqueue({w.direction});
    w.interpreter.run();
    int status = w.interpreter.output();
    auto coord = newcoord(std::make_pair(w.coord.first, w.coord.second), w.direction);
    map[coord] = std::make_pair(status, w.stepcount);
    if (status != 0) 
      for(auto d: alldirections) 
        if (map.count(newcoord(coord, d)) == 0) 
          work.push(worker{w.interpreter.clone(), d, coord, w.stepcount+1});
    work.pop();
    print_map(&g, map, false);
  }
  print_map(&g, map, true);

  std::pair<int,int> oxytank;
  for(auto p: map) 
    if (p.second.first == 2) {
      res1 = p.second.second;
      oxytank = p.first;
    }

  std::queue<oxy> oxygenete;
  for(auto d: alldirections) 
    if (map[newcoord(oxytank, d)].first == 1) 
      oxygenete.push(oxy{newcoord(oxytank, d), 1});

  while(!oxygenete.empty()) {
    auto o = oxygenete.front();
    res2 = std::max(res2, o.stepcount);
    if (map[o.coord].first == 1) {
      map[o.coord].first = 2;
      for(auto d: alldirections) 
        if (map[newcoord(o.coord, d)].first == 1) 
          oxygenete.push(oxy{newcoord(o.coord, d), o.stepcount+1});
      oxygenete.pop();
    print_map(&g, map, false);
    }  
  }
  print_map(&g, map, true);
  GifEnd(&g);
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

