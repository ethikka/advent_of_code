#include <sstream>
#include <map>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<int,int> res; // res.first = solution for part a, res.second = solution for part b
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

int main(int argc, char *argv[]) {
  output_for_timing = (argc > 1);
  post_solve(solve());
}
