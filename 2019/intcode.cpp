#include <vector>
#include "intcode.h"

int intcode::run(std::vector<int> code, int pos_1, int pos_2) {
  int idx(0);
  code[1] = pos_1;
  code[2] = pos_2;

  while (true) {
    switch(code[idx]) {
      case  1: code[code[idx+3]] = code[code[idx+1]] + code[code[idx+2]];
               break;
      case  2: code[code[idx+3]] = code[code[idx+1]] * code[code[idx+2]];
               break;
      case 99: return code[0];
    }
    idx += 4;
  }
  return -1;
}

