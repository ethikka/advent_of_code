#ifndef INTCODE_H
#define INTCODE_H

#include <vector>

class intcode
{
   public:
     int run(std::vector<int> code, int pos_1, int pos_2);
};

#endif
