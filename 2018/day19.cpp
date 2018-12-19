#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <map>

struct instruction {
  std::string opcode;
  int64_t a;
  int64_t b;
  int64_t c;
};

void solve() {
  std::string dontcare;
  int ip_reg;
  std::array<int64_t,6> registers = {0,0,0,0,0,0};
  std::map<int,instruction> program;
  std::cin >> dontcare >> ip_reg;

  std::string opcode;
  int64_t a(0),b(0),c(0);
  while (std::cin >> opcode >> a >> b >> c) program[program.size()]  = { opcode, a, b, c };
  
  registers[ip_reg] = 0;
  while (registers[ip_reg] >= 0 && registers[ip_reg] < program.size()) {
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
    registers[ip_reg]++;
  }
  int res1(registers[0]);

/*  registers[0] = 1; registers[1] = 0; registers[2] = 0; registers[3] = 0; registers[4] = 0; registers[5] = 0;
  registers[ip_reg] = 0;

  while (registers[ip_reg] >= 0 && registers[ip_reg] < program.size()) {
    auto inst = program[registers[ip_reg]];
    std::cout << inst.opcode << "[" << std::setw(2) << inst.a << "|" << std::setw(2) << inst.b << "|" << std::setw(2) << inst.c << "]  "; 
    std::cout << std::setw(9) << registers[0] << std::setw(9) << registers[1] << std::setw(9) << registers[2] << std::setw(9) << registers[3] << std::setw(9) << registers[4] << std::setw(9) << registers[5] << " ---- ";

    // keyhole optimizations ;-)
    //if (registers[ip_reg] == 3 && registers[1] == 0) registers[3] = registers[2];
//if (false)    
    if (registers[ip_reg] == 4 && registers[1] == registers[3]) {
//      registers[0] += registers[3];
      registers[1]++;
      registers[3]++;
      registers[5] = 3;
      ip_reg = 4;
      inst = program[registers[ip_reg]];
      std::cout << std::endl << inst.opcode << "[" << inst.a << "|" << inst.b << "|" << inst.c << "]" << registers[0] << ","<< registers[1] << ","<< registers[2] << ","<< registers[3] << ","<< registers[4] << ","<< registers[5] << std::endl;
    }

    std::cout << std::setw(9) << registers[0] << std::setw(9) << registers[1] << std::setw(9) << registers[2] << std::setw(9) << registers[3] << std::setw(9) << registers[4] << std::setw(9) << registers[5] << std::endl;
    
    // execute instruction at pointer
         if (inst.opcode == "addr") registers[inst.c] = registers[inst.a]+registers[inst.b]; 
    else if (inst.opcode == "addi") registers[inst.c] = registers[inst.a]+inst.b; 
    else if (inst.opcode == "eqrr") registers[inst.c] = (registers[inst.a] == registers[inst.b]) ? 1 : 0; 
    else if (inst.opcode == "gtrr") registers[inst.c] = (registers[inst.a] > registers[inst.b]) ? 1 : 0; 
    else if (inst.opcode == "mulr") registers[inst.c] = registers[inst.a]*registers[inst.b]; 
    else if (inst.opcode == "muli") registers[inst.c] = registers[inst.a]*inst.b; 
    else if (inst.opcode == "setr") registers[inst.c] = registers[inst.a]; 
    else if (inst.opcode == "seti") registers[inst.c] = inst.a; 
    registers[ip_reg]++;
  }
  int res2(registers[0]);*/
  std::string res2("Sum of factors of REG[2] after some cycles on my input");
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}