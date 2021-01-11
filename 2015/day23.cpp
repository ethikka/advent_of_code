#include <sstream>
#include <vector>
#include "../common/lib.h"

int run(std::vector<std::string> instructions, int start_val_a) {
  int ip(0);
  int registers[2] = {start_val_a, 0};
  while(ip < instructions.size()) {
    std::stringstream sl(instructions[ip]);
    std::string inst, p1, p2;
    sl >> inst >> p1 >> p2;
    if      (inst == "hlf") registers[p1[0]-'a'] /= 2;
    else if (inst == "tpl") registers[p1[0]-'a'] *= 3;
    else if (inst == "inc") registers[p1[0]-'a'] += 1;
    else if (inst == "jmp") ip += std::stoi(p1)-1;
    else if (((inst == "jie") && (registers[p1[0]-'a']%2 == 0)) || 
             ((inst == "jio") && (registers[p1[0]-'a'] == 1))) ip += std::stoi(p2)-1;
    ip++;    
  }
  return registers[1];
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string line;
  std::vector<std::string> instructions;
  while (std::getline(std::cin, line)) instructions.push_back(line);
  return { run(instructions, 0), run(instructions, 1) };
}
