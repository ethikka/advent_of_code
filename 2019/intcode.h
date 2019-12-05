#ifndef INTCODE_H
#define INTCODE_H

#include <vector>

class intcode
{
   public:
     void load(std::string filename); 
     void poke(int address, int value);
     int run();
};

#endif
