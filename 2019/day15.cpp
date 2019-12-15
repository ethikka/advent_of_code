#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <queue>
#include <cmath>
#include <thread>
#include "intcode.h"

char statuschars[3] = {'#', '.', 'O'};
struct coord { int x; int y; };
enum dr { north = 1, south = 2, west = 3, east = 4 };

static const dr alldirections[] = { north, south, west, east };

void print_map(std::map<std::pair<int,int>,std::pair<char,int>> map) {
  std::cout << "\033[2J";
  int xoff(0), yoff(0);
  for(auto p: map) {
    xoff = std::min(p.first.first, xoff);
    yoff = std::min(p.first.second, yoff);
  }
  for(auto p: map) std::cout << "\033[" << p.first.first+(-1*xoff)+5 << ";" << p.first.second+(-1*yoff)+5 << "f" << p.second.first << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

  std::map<std::pair<int,int>,std::pair<char,int>> map;
  std::queue<worker> work;
  auto coord = std::make_pair(0,0);
  map[coord] = std::make_pair('.', 1);
  for(auto d: alldirections) 
    work.push(worker{interpreter.clone(), d, coord, 1});

  while(!work.empty()) {
    auto w = work.front();
    w.interpreter.inputqueue({w.direction});
    int status = w.interpreter.run();
    auto coord = newcoord(std::make_pair(w.coord.first, w.coord.second), w.direction);
    map[coord] = std::make_pair(statuschars[status], w.stepcount);
    if (status != 0) 
      for(auto d: alldirections) 
        if (map.count(newcoord(coord, d)) == 0) 
          work.push(worker{w.interpreter.clone(), d, coord, w.stepcount+1});
    work.pop();
  }
  //print_map(map);

  std::pair<int,int> oxytank;
  for(auto p: map) 
    if (p.second.first == 'O') {
      res1 = p.second.second;
      oxytank = p.first;
    }

  std::queue<oxy> oxygenete;
  for(auto d: alldirections) 
    if (map[newcoord(oxytank, d)].first == '.') 
      oxygenete.push(oxy{newcoord(oxytank, d), 1});

  while(!oxygenete.empty()) {
    auto o = oxygenete.front();
    res2 = std::max(res2, o.stepcount);
    if (map[o.coord].first == '.') {
      map[o.coord].first = 'O';
      for(auto d: alldirections) 
        if (map[newcoord(o.coord, d)].first == '.') 
          oxygenete.push(oxy{newcoord(o.coord, d), o.stepcount+1});
      oxygenete.pop();
    }  
  }
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

