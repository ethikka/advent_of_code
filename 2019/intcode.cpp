#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "intcode.h"

int opcodeparamcount[10] = { 0, 3, 3, 1, 1, 2, 2, 3, 3, 1};

/*-------------------------------------------------------------------------------------------------------*/
// intcode
/*-------------------------------------------------------------------------------------------------------*/
void intcode::load(std::string filename) {
  memory.clear();
  inputbuffer.clear();
  std::ifstream infile; 
  infile.open(filename);
  std::string line;
  while (std::getline(infile, line, ',')) {
    memory.push_back(std::stol(line));
  }
} 

bool    intcode::halted()                              { return _halted; }
int64_t intcode::peek(int64_t address)                 { return memory.at(address); }
void    intcode::inputqueue(std::vector<int64_t> nums) { for(int64_t i: nums) inputbuffer.push_back(i); }

void intcode::poke(int64_t address, int64_t value) {
  checkmemsize(address);
  memory.at(address) = value;
}

instruction intcode::parseinstruction(int64_t pointer) {
  instruction ret;
  ret.opcode = (opcode)(memory.at(pointer) % 100);
  ret.paramcount = opcodeparamcount[ret.opcode];
  for (int i = 1; i <= ret.paramcount; i++) {
    ret.parms.push_back(parameter(this, memory.at(pointer+i), (parametermode)((int)(memory.at(pointer) / pow(10,i+1)) % 10))); 
  }
  // for the future me, opcode parametermode extraction => ((opcode / 10^(1+parameterval)) % 10) extracts the digit which corresponds 
  // to the parameters like zo: 54321..
  return ret;
}

void intcode::print_mem() {
  std::cout << std::endl;
  for(int64_t i=0; i < memory.size(); i++) std::cout << memory.at(i) << " ";
  std::cout << std::endl;
}

void intcode::print_instruction(instruction inst) {
  std::cout << instructionpointer << " " << inst.opcode << "(" << memory.at(instructionpointer) << ").";
  for(auto p: inst.parms) std::cout << p.parm << "|" << p.value() << "|" << p.mode << " ";
  std::cout << std::endl;
}

void intcode::checkmemsize(int64_t targetaddress) {
  if (memory.size() < targetaddress) 
    memory.resize(targetaddress+2); 
}

int64_t intcode::run() {
  while (true) {
    instruction inst = parseinstruction(instructionpointer);
    //std::chrono::time_point start_time  = std::chrono::high_resolution_clock::now();
    //print_mem();
    //print_instruction(inst);
    switch(inst.opcode) {
      case add        : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), inst.parms[0].value() + inst.parms[1].value()); break;
      case multiply   : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), inst.parms[0].value() * inst.parms[1].value()); break;
      case input      :
        if (inputbuffer.size() > 0) {
          poke(inst.parms[0].parm + ((inst.parms[0].mode == relative) ? relative_offset : 0), inputbuffer.at(0));
          inputbuffer.erase(inputbuffer.begin());
        } 
        break;
      case output     : 
        //std::cout << "DIAGNOSTIC "<< inst.parms[0].value() << std::endl;
        outputdiag = inst.parms[0].value();
        instructionpointer += (inst.paramcount+1);
        return outputdiag;                                                          
      case jumpiftrue : instructionpointer = ((inst.parms[0].value() != 0) ? inst.parms[1].value(): instructionpointer + inst.paramcount + 1); break; 
      case jumpiffalse: instructionpointer = ((inst.parms[0].value() == 0) ? inst.parms[1].value(): instructionpointer + inst.paramcount + 1); break;
      case lessthan   : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), ((inst.parms[0].value() < inst.parms[1].value()) ? 1: 0));  break;
      case equals     : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), ((inst.parms[0].value() == inst.parms[1].value()) ? 1: 0)); break;
      case modbase    : relative_offset += inst.parms[0].value(); break;
      case halt       : _halted = true; return outputdiag;
      case none       : break;
    }
    if (inst.opcode != jumpiffalse && inst.opcode != jumpiftrue)
      instructionpointer += (inst.paramcount+1);
  }
  return -1;
}

