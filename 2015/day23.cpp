#include <sstream>
#include <vector>
#include "../common/lib.h"

int run(std::vector<std::string> instructions, int start_val_a) {
  int ip(0);
  int registers[2] = {start_val_a, 0};
  while(ip < instructions.size()) {
    std::cout << ip << std::endl;
    std::stringstream sl(instructions[ip]);
    std::string inst, p1, p2;
    sl >> inst >> p1;

    std::cout << "r " << p1[0]-'a' << std::endl;
    if      (inst == "hlf") registers[p1[0]-'a'] /= 2;
    else if (inst == "tpl") registers[p1[0]-'a'] *= 3;
    else if (inst == "inc") registers[p1[0]-'a'] += 1;
    else if (inst == "jmp") ip += std::stoi(p1)-1;
    else if (inst == "jie") { 
      if (registers[p1[0]-'a']%2 == 0) { 
        sl >> p2;
        ip += std::stoi(p2)-1;
      } 
    } else if (inst == "jio") {
      if (registers[p1[0]-'a'] == 1) { 
        sl >> p2;
        ip += std::stoi(p2)-1;
      } 
    }
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

/*
jio a, +19
inc a
tpl a
inc a
tpl a
inc a
tpl a
tpl a
inc a
inc a
tpl a
tpl a
inc a
inc a
tpl a
inc a
inc a
tpl a
jmp +23
tpl a
tpl a
inc a
inc a
tpl a
inc a
inc a
tpl a
inc a
tpl a
inc a
tpl a
inc a
tpl a
inc a
inc a
tpl a
inc a
inc a
tpl a
tpl a
inc a
jio a, +8
inc b
jie a, +4
tpl a
inc a
jmp +2
hlf a
jmp -7
*/