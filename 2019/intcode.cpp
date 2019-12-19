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
intcode::intcode() {};
intcode::intcode(std::string filename) {
  load(filename);
};
intcode::intcode(int ip, int ro, std::vector<int64_t> mem) {
  instructionpointer = ip;
  relative_offset = ro;
  memory = mem;
};

intcode intcode::clone() {
  return intcode(instructionpointer, relative_offset, memory);
}

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
  for(auto p: inst.parms) std::cout << p.parm << "|" << p.mode << " ";
  std::cout << std::endl;
}

void intcode::checkmemsize(int64_t targetaddress) {
  if (memory.size() <= targetaddress) {
    memory.resize(targetaddress+64); 
  }
}

int64_t intcode::run() {
  while (true) {
    instruction inst = parseinstruction(instructionpointer);
    //std::chrono::time_point start_time  = std::chrono::high_resolution_clock::now();
    //print_mem();
    //print_instruction(inst);
    switch(inst.opcode) {
/*1*/ case add        : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), inst.parms[0].value() + inst.parms[1].value()); break;
/*2*/ case multiply   : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), inst.parms[0].value() * inst.parms[1].value()); break;
/*3*/ case input      :
        //std::cout << "INPUT " << inputbuffer.at(0) << std::endl;
        if (inputbuffer.size() > 0) {
          poke(inst.parms[0].parm + ((inst.parms[0].mode == relative) ? relative_offset : 0), inputbuffer.at(0));
          inputbuffer.erase(inputbuffer.begin());
        } 
        break;
/*4*/ case output     : 
        //std::cout << "DIAGNOSTIC "<< inst.parms[0].value() << std::endl;
        outputdiag = inst.parms[0].value();
        instructionpointer += (inst.paramcount+1);
        return outputdiag;                                                          
/*5*/ case jumpiftrue : if (inst.parms[0].value() != 0) instructionpointer = inst.parms[1].value();
                        else                            instructionpointer += (inst.paramcount + 1); break; 
/*6*/ case jumpiffalse: if (inst.parms[0].value() == 0) instructionpointer = inst.parms[1].value();
                        else                            instructionpointer += (inst.paramcount + 1); break;
/*7*/ case lessthan   : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), ((inst.parms[0].value() < inst.parms[1].value()) ? 1: 0));  break;
/*8*/ case equals     : poke(inst.parms[2].parm + ((inst.parms[2].mode == relative) ? relative_offset : 0), ((inst.parms[0].value() == inst.parms[1].value()) ? 1: 0)); break;
/*9*/ case modbase    : relative_offset += inst.parms[0].value(); break;
/*99*/case halt       : _halted = true; return outputdiag;
/*0*/ case none       : break;
    }
    if (inst.opcode != jumpiffalse && inst.opcode != jumpiftrue)
      instructionpointer += (inst.paramcount+1);
  }
  return -1;
}

