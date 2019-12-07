#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "intcode.h"

int opcodeparamcount[9] = { 0, 3, 3, 1, 1, 2, 2, 3, 3};

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
    memory.push_back(std::stoi(line));
  }
} 

bool intcode::halted() {
  return _halted;
}

int intcode::peek(int address) {
  return memory.at(address);
}

void intcode::poke(int address, int value) {
  memory.at(address) = value;
}

void intcode::inputqueue(std::vector<int> nums) {
  for(int i: nums)
    inputbuffer.push_back(i);
}

instruction intcode::parseinstruction(int pointer) {
  instruction ret;
  ret.opcode = (opcode)(memory.at(pointer) % 100);
  ret.paramcount = opcodeparamcount[ret.opcode];
  for (int i = 1; i <= ret.paramcount; i++)
    ret.parms.push_back(parameter(memory, memory.at(pointer+i), (parametermode)((int)(memory.at(pointer) / pow(10,i+1)) % 10) )); 
  // for the future me, opcode parametermode extraction => ((opcode / 10^(1+parameterval)) % 10) extracts the digit which corresponds 
  // to the parameters like zo: 54321..

  return ret;
}

void intcode::print_mem() {
  std::cout << std::endl;
  for(int i=0; i < memory.size(); i++)
    std::cout << memory.at(i) << " ";
  std::cout << std::endl;
}

void intcode::print_instruction(instruction inst) {
  std::cout << inst.opcode << ".";
  for(auto p: inst.parms)
    std::cout << p.parm << "|" << p.value() << "|" << p.mode << " ";
  std::cout << std::endl;
}

int intcode::run() {
  while (true) {
    instruction inst = parseinstruction(instructionpointer);
    std::chrono::time_point start_time  = std::chrono::high_resolution_clock::now();
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
        if (inputbuffer.size() > 0) {
          memory.at(inst.parms[0].parm) = inputbuffer.at(0);
          inputbuffer.erase(inputbuffer.begin());
        } else {
          std::cout << "INPUT: "; 
          int input(0);
          start_time = std::chrono::high_resolution_clock::now(); // how long did it take to input something
          std::cin >> input;
          std::cout << "Input took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() << "ms " << input << std::endl;    // how long did it take to input something
          memory.at(inst.parms[0].parm) = input/*1 part a*/;                                                   
        }
        break;
      case output     : 
        //std::cout << "DIAGNOSTIC "<< inst.parms[0].value() << std::endl;
        outputdiag = inst.parms[0].value();
        instructionpointer += (inst.paramcount+1);
        return outputdiag;                                                          
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
        _halted = true; 
        return outputdiag;
        break;
      case none: 
        break;
    }
    if (inst.opcode != jumpiffalse && inst.opcode != jumpiftrue)
      instructionpointer += (inst.paramcount+1);
  }
  return -1;
}

