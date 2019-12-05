#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "intcode.h"

std::vector<int> memory;
int instructionpointer(0);

enum parametermode { position = 0, immidiate = 1};

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
  halt = 99};
int opcodeparamcount[9] = { 0, 3, 3, 1, 1, 2, 2, 3, 3};

struct parameter {
  parameter(int p, parametermode m) { parm = p; mode = m;}
  int value() { 
    if (mode == position) 
      return memory.at(parm); 
    else 
      return parm; }
  int parm;
  parametermode mode;
};

struct instruction {
  opcode opcode;
  int paramcount;
  std::vector<parameter> parms;
};

instruction parseinstruction(int pointer) {
  instruction ret;
  ret.opcode = (opcode)(memory.at(pointer) % 100);
  ret.paramcount = opcodeparamcount[ret.opcode];
  for (int i = 1; i <= ret.paramcount; i++)
    ret.parms.push_back(parameter(memory.at(pointer+i), (parametermode)((int)(memory.at(pointer) / pow(10,i+1)) % 10) ));
  return ret;
}

void print_mem() {
  std::cout << std::endl;
  for(int i=0; i < memory.size(); i++)
    std::cout << memory.at(i) << " ";
  std::cout << std::endl;
}

void print_instruction(instruction inst) {
  std::cout << inst.opcode << ".";
  for(auto p: inst.parms)
    std::cout << p.parm << "|" << p.value() << "|" << p.mode << " ";
  std::cout << std::endl;
}

/*-------------------------------------------------------------------------------------------------------*/
// intcode
/*-------------------------------------------------------------------------------------------------------*/
void intcode::load(std::string filename) {
  memory.clear();
  instructionpointer = 0;
  std::ifstream infile; 
  infile.open(filename);
  std::string line;
  while (std::getline(infile, line, ',')) {
    memory.push_back(std::stoi(line));
  }
} 

void intcode::poke(int address, int value) {
  memory.at(address) = value;
}

int intcode::run() {
  while (true) {
    instruction inst = parseinstruction(instructionpointer);
    //std::cout << instructionpointer << std::endl;
    //print_mem();
    //print_instruction(inst);
    switch(inst.opcode) {
      case add        : 
        memory.at(inst.parms[2].parm) = inst.parms[0].value() + inst.parms[1].value();                                            
        break;
      case multiply   : 
        memory.at(inst.parms[2].parm) = inst.parms[0].value() * inst.parms[1].value();                                            
        break;
      case input      : 
        std::cout << "INPUT: "; 
        int input;
        std::cin >> input;
        memory.at(inst.parms[0].parm) = input/*1 part a*/;                                         
        break;
      case output     : 
        std::cout << "DIAGNOSTIC "<< inst.parms[0].value() << std::endl;                                                          
        break;
      case jumpiftrue : 
        if (inst.parms[0].value() != 0) 
          instructionpointer = inst.parms[1].value(); 
        else
          instructionpointer += inst.paramcount+1; 
        break;
      case jumpiffalse: 
        if (inst.parms[0].value() == 0) 
          instructionpointer = inst.parms[1].value(); 
        else 
          instructionpointer += inst.paramcount+1; 
        break;
      case lessthan   : 
        memory.at(inst.parms[2].parm) = (inst.parms[0].value() < inst.parms[1].value()) ? 1: 0;                                   
        break;
      case equals     : 
        memory.at(inst.parms[2].parm) = (inst.parms[0].value() == inst.parms[1].value()) ? 1: 0;                                  
        break;
      case halt       : 
        return memory.at(0);
    }
    if (inst.opcode != jumpiffalse && inst.opcode != jumpiftrue)
      instructionpointer += (inst.paramcount+1);
  }
  return -1;
}

