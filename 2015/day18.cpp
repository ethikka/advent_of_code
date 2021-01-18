// 
#include <sstream>
#include <map>
#include <vector>
#include <random>
#include <thread>
#include "../common/lib.h"
#include "../common/automata.h"


std::pair<std::uintmax_t,std::uintmax_t> solve() {
  automata<vector2, bool, 1> a({100, 100, false, 1, false}), b({100, 100, false, 1, false});

  char inp;
  int x(0), y(0);
  while (std::cin >> inp) {
    if (inp == '#') {
      a.place_pixel({x, y}, true);
      b.place_pixel({x, y}, true);
    }
    x++;
    if (x == 100) { x = 0; y++; }
  }

  int count(0);
  while (count++ < 100) {
    a.advance_generation();
    b.place_pixels({0,0}, {{0,0},{0,99},{99,0},{99,99}}, true);
    b.advance_generation();
  } 
  b.place_pixels({0,0}, {{0,0},{0,99},{99,0},{99,99}}, true);

  return {a.count_on(),b.count_on()};
}
