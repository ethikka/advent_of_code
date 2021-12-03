#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  int64_t depth(0),move(0),pos(0),depth_b(0);
  std::string instruction;
  while (std::cin >> instruction >> move) 
    if  (instruction == "forward") { pos += move; depth_b += (depth*move); }
    else depth = instruction[0]=='d' ? depth+move : depth-move;
  return {pos*depth, pos*depth_b};
}