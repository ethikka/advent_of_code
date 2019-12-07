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
  halt = 99 };

enum parametermode { position = 0, immidiate = 1};

struct parameter {
  parameter(std::vector<int> mem, int p, parametermode m) { parm = p; mode = m; memory = mem;}

  int value() { 
    if (mode == position) 
      return memory.at(parm); 
    else 
      return parm; }
  
  std::vector<int> memory;
  int parm;
  parametermode mode;
};

struct instruction {
  opcode opcode;
  int paramcount;
  std::vector<parameter> parms;
};

class intcode
{
   private:
   	 std::vector<int> memory;
     std::vector<int> inputbuffer;
     bool _halted = false;
     int instructionpointer = 0;
     int outputdiag = 0;
   public:
     void load(std::string filename); 
     void inputqueue(std::vector<int> num);
     void poke(int address, int value);
     int peek(int address);
     int run();
     bool halted();

     instruction parseinstruction(int pointer);
     void print_mem();
     void print_instruction(instruction inst);
};

#endif
