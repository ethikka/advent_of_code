#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string input("3113322113");

  for (int i = 0; i < 50; i++) {
    std::string newstr;
    int count(0);
    char lastchar(input[0]);
    for(auto c: input)
      if (lastchar != c) {
        newstr += std::to_string(count);
        newstr += lastchar;
        count = 1;
        lastchar = c;
      } else count++;
    newstr += std::to_string(count);
    newstr += lastchar;
    if (i == 40) res.first = input.length();
    //std::cout << newstr << std::endl;
    input = newstr;
  }
  res.second = input.length();
  return res;
}