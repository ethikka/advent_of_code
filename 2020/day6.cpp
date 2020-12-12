#include <sstream>
#include <map>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res; 
  char inp, last;
  int groupcount(0);
  std::map<char,int> answers;
  while (std::cin >> std::noskipws >> inp) {
    switch (inp) {
        case '\n': 
          if (last == '\n') {
            res.first += answers.size(); 
            for(auto a: answers)
              if (answers[a.first] == groupcount)
                res.second++;
            answers.clear();
            groupcount = 0;
          } else
            groupcount++;
          break;
        default: 
          answers[inp]++;
    }
    last = inp;
  }
  return res;
}