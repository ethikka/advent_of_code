#include <sstream>
#include <map>
#include <vector>
#include <thread>
#include <random>
#include "../common/lib.h"
#include "../common/automata.h"

std::vector<std::vector<std::pair<int,int>>> shapes{
  /*glider*/{{2,0},{2,1},{2,2},{1,2},{0,1}},
  /*glider*/{{0,0},{0,1},{0,2},{1,2},{2,1}},
  /*glider*/{{2,2},{2,1},{2,0},{1,0},{0,1}},
  /*glider*/{{0,2},{0,1},{0,0},{1,0},{2,1}},
  /*lwss*/  {{0,0},{0,3},{2,0},{1,4},{2,4},{3,1},{3,2},{3,3},{3,4}},
  /*lwss*/  {{3,0},{3,3},{1,0},{2,4},{1,4},{0,1},{0,2},{0,3},{0,4}},
  /*lwss*/  {{0,4},{0,1},{2,4},{1,0},{2,0},{3,3},{3,2},{3,1},{3,0}},
  /*lwss*/  {{3,4},{3,1},{1,4},{2,0},{1,0},{0,3},{0,2},{0,1},{0,0}}
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::srand(std::time(NULL));
  automata a(32, 8, true);
  printf("\33c");
  for (int i = 0; i < 16; i++) 
    a.place_pixels((rand()%64), (rand()%16), shapes[rand()%shapes.size()], (rand()%2)*255, (rand()%2)*255, (rand()%2)*255);
  
//  a.clear_to_color(255,255,0);
  int count(0);
  while (count++ < 500) {
    a.print_automata();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    a.advance_generation();
  }
  a.print_automata();
  return {0,0};
}
