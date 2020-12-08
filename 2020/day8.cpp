#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include "../common/lib.h"

int run(int fixline, std::vector<std::string> memory) {
  if (fixline >= 0) {
    if      (memory[fixline].substr(0, 3) == "nop") memory[fixline] = "jmp" + memory[fixline].substr(3);
    else if (memory[fixline].substr(0, 3) == "jmp") memory[fixline] = "nop" + memory[fixline].substr(3);
  }
  std::map<int,int> acc;
  int ip(0), lacc(0);
  while (ip < memory.size()) {
    if (acc.count(ip)) {
      if (fixline == -1)
        return lacc;
      else
        return -9999999;
    } else {
      int parm = std::stoi(memory[ip].substr(memory[ip].find(" ")+1));
      acc[ip] = lacc;
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
  std::vector<std::string> memory;
  while (std::getline(std::cin, line)) 
    memory.push_back(line);

  res.first = run(-1, memory);
  res.second = -9999999;
  for (int i = 0; i < memory.size() && res.second < 0; i++)
    res.second = std::max(res.second, run(i, memory));
  return res;
}

int main(void) {
  post_solve(solve());
}
