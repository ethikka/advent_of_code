#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <map>
#include <set>

struct instruction {
  std::string opcode;
  int a;
  int b;
  int c;
};

void solve() {
  std::string dontcare;
  int ip_reg(0);
  std::array<int,6> registers = {0,0,0,0,0,0};
  std::map<int,instruction> program;
  std::cin >> dontcare >> ip_reg;
  int res1(0), res2(0);

  std::string opcode;
  int a(0),b(0),c(0);
  while (std::cin >> opcode >> a >> b >> c) program[program.size()]  = { opcode, a, b, c };

  registers[ip_reg] = 0;
  registers[0] = 0;
  std::set<int> halt_ints;
  int last_halt_int(0);
  
  while ((registers[ip_reg] >= 0) && (registers[ip_reg] < program.size()) && (res2 == 0)) {
    auto inst = program[registers[ip_reg]];

    // execute instruction at pointer
         if (inst.opcode == "addr") registers[inst.c] = registers[inst.a]+registers[inst.b]; 
    else if (inst.opcode == "addi") registers[inst.c] = registers[inst.a]+inst.b; 
    else if (inst.opcode == "eqrr") registers[inst.c] = (registers[inst.a] == registers[inst.b]) ? 1 : 0; 
    else if (inst.opcode == "gtrr") registers[inst.c] = (registers[inst.a] > registers[inst.b]) ? 1 : 0; 
    else if (inst.opcode == "mulr") registers[inst.c] = registers[inst.a]*registers[inst.b]; 
    else if (inst.opcode == "muli") registers[inst.c] = registers[inst.a]*inst.b; 
    else if (inst.opcode == "setr") registers[inst.c] = registers[inst.a]; 
    else if (inst.opcode == "seti") registers[inst.c] = inst.a; 
    // new instruction for day 21
    else if (inst.opcode == "bani") registers[inst.c] = registers[inst.a] & inst.b; 
    else if (inst.opcode == "eqri") registers[inst.c] = (registers[inst.a] == inst.b) ? 1 : 0; 
    else if (inst.opcode == "bori") registers[inst.c] = registers[inst.a] | inst.b; 
    else if (inst.opcode == "gtir") registers[inst.c] = (inst.a > registers[inst.b]) ? 1 : 0; 

    if (registers[ip_reg] == 28) {
      if ((halt_ints.size() % 100) == 0) std::cout << std::endl << std::setw(4) << halt_ints.size() / 100 << " ";
      if ((halt_ints.size() % 10) == 0) std::cout << "|";
      else                               std::cout << ".";

      if (res1 == 0)
        res1 = registers[4];
      if (halt_ints.count(registers[4]) > 0)
        res2 = last_halt_int;
      halt_ints.insert(registers[4]);
      last_halt_int = registers[4];
    }
    registers[ip_reg]++;
  }
  std::cout << std::endl << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}