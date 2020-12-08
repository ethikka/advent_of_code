#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include "../common/lib.h"

std::vector<std::string> memory;

int run(int fixline) {
  if (fixline >= 0) {
    if      (memory[fixline].substr(0, 3) == "nop") memory[fixline] = "jmp" + memory[fixline].substr(3);
    else if (memory[fixline].substr(0, 3) == "jmp") memory[fixline] = "nop" + memory[fixline].substr(3);
  }
  std::set<int> acc;
  int ip(0), lacc(0);
  while (ip < memory.size()) {
    if (acc.find(ip) != acc.end()) {
      if (fixline >= 0) { // unfix it
        if      (memory[fixline].substr(0, 3) == "nop") memory[fixline] = "jmp" + memory[fixline].substr(3);
        else if (memory[fixline].substr(0, 3) == "jmp") memory[fixline] = "nop" + memory[fixline].substr(3);
      }
      return fixline == -1 ? lacc: -9999999;
    } else {
      int parm = std::stoi(memory[ip].substr(memory[ip].find(" ")+1));
      acc.insert(ip);
      if      (memory[ip].substr(0, 3) == "acc") lacc += parm;
      else if (memory[ip].substr(0, 3) == "jmp") { ip += parm-1; }
      ip++;
    }
  }
  return lacc;
}

std::pair<int,int> solve() {
  std::pair<int,int> res;

  std::string line;
  while (std::getline(std::cin, line)) 
    memory.push_back(line);

  res.first = run(-1);
  res.second = -9999999;
  for (int i = 0; i < memory.size() && res.second < 0; i++)
    if (memory[i].substr(0, 3) != "acc")
      res.second = std::max(res.second, run(i));
  return res;
}

int main(void) {
  post_solve(solve());
}
