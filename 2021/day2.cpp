#include <sstream>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  int64_t depth(0),move(0),pos(0),aim(0), depth_b(0);
  std::string instruction;
  while (std::cin >> instruction >> move) {
    if      (instruction == "forward") { pos   += move; depth_b += (aim*move); }
    else if (instruction == "down")    { depth += move; aim += move; }
    else if (instruction == "up")      { depth -= move; aim -= move; }
  }
  return {pos*depth, pos*depth_b};
}