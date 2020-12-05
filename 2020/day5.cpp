#include <sstream>
#include <cmath>
#include <set>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<int,int> res; 
  char inp;
  std::set<int> seats;
  std::string num = "";
  while (std::cin >> std::noskipws >> inp) {
    switch (inp) {
      case '\n': seats.insert(std::stoi(num, 0, 2));
                 num = "";
                 break;
      default:   num += std::string("BR").find(inp) != std::string::npos ? "1": "0";
    }
  }

  for(auto iter=seats.begin(), prev=seats.end(); iter != seats.end(); prev=iter, ++iter )
    if(prev != seats.end() && (*iter - *prev) > 1) 
      res.second = *prev + 1;

  res.first = *seats.rbegin();
  return res;
}

int main(void) {
  post_solve(solve());
}
