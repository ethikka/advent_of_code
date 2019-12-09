#ifndef INTCODE_H
#define INTCODE_H

#include <vector>

enum opcode { 
  none = 0, 
  add = 1,
  multiply = 2, 
  input = 3, 
  output = 4, 
  jumpiftrue = 5,
  jumpiffalse = 6,
  lessthan = 7,
  equals = 8,
  modbase = 9,
  halt = 99 };

enum parametermode { position = 0, immidiate = 1, relative = 2};

struct instruction;

class intcode
{
//  public:
//    intcode(std::string file) { load(file); };  
  private:
    std::vector<int64_t> inputbuffer;
    bool _halted = false;
    int64_t instructionpointer = 0;
    int64_t outputdiag = 0;
  public:
    std::vector<int64_t> memory;
    int64_t relative_offset = 0;

    void load(std::string filename); 
    void inputqueue(std::vector<int64_t> num);
    void poke(int64_t address, int64_t value);
    int64_t peek(int64_t address);
    int64_t run();
    bool halted();
    void checkmemsize(int64_t targetaddress);
    instruction parseinstruction(int64_t pointer);

  public: // Debugging functions
    void print_mem();
    void print_instruction(instruction inst);
};

struct parameter {
  parameter(intcode* comp, int64_t p, parametermode m) { 
    parm = p;
    mode = m; 
    intpr = comp; 
  }

  int64_t value() { 
    switch (mode) {
      case position: return intpr->memory.at(parm);
      case immidiate: return parm;
      case relative: return intpr->memory.at(intpr->relative_offset+parm); 
    }
  }
  intcode* intpr;
  int64_t parm;
  parametermode mode;
};

struct instruction {
  opcode opcode;
  int64_t paramcount;
  std::vector<parameter> parms;
};

#endif
