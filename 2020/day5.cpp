#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<int,int> res; 
  char inp;
  std::set<int> seats;
  std::string num = "";
  std::string sublist = "F0B1L0R1";
  while (std::cin >> std::noskipws >> inp) {
    switch (inp) {
      case '\n': { 
        seats.insert(std::stoi(num, 0, 2));
        num = "";
        break;
      }
      default: num += sublist.substr(sublist.find(inp)+1, 1);
    }
  }

  for(auto iter=seats.begin(), prev=seats.end(); iter != seats.end(); prev=iter, ++iter )
    if(prev != seats.end())
      if ((*iter - *prev) > 1) res.second = *prev++;

  res.first = *seats.rbegin();
  return res;
}

int main(void) {
  post_solve(solve());
}
