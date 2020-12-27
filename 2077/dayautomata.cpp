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
  /*lwss*/  {{3,4},{3,1},{1,4},{2,0},{1,0},{0,3},{0,2},{0,1},{0,0}},
  /*barbell*/ {{0,0},{5,0},{1,1},{2,1},{3,1},{4,1},{0,2},{5,2}},  // cycles at 8 high 
  /*barbell*/ {{0,0},{0,5},{1,1},{1,2},{1,3},{1,4},{2,0},{2,5}},  // cycles at 8 high
  /*barbell*/ {{0,0},{6,0},{1,1},{2,1},{3,1},{4,1},{0,2},{6,2}}, 
};

int custom_rules(int layer, int current_val, std::vector<int> counts) {
  if (counts[layer] == 3) return 255;
  if (counts[layer] <  2 || counts[layer] > 3) return 0;
  if (counts[layer] == 2 && current_val) return 255;
  return 0;
};


std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::srand(std::time(NULL));
  automata a({32, 8, true, 3/*, &custom_rules*/});
  printf("\33c");
  for (int i = 0; i < 12; i++) 
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
