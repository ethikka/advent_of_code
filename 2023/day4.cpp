#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::map<int,int> stackssize;
  int num(0),score(0);
  std::string line;
  int counter(1);
  while (std::getline(std::cin, line)) {
    std::istringstream ssl(line);
    std::set<int> numbers;
    ssl.ignore(10);
    std::copy_n(std::istream_iterator<int>(ssl), 10, std::inserter(numbers, numbers.begin()));    
    ssl.ignore(3);
    stackssize[counter] = std::max(1, stackssize[counter]+1);

    int wins(0);
    while (ssl >> num) {
        if (numbers.count(num) > 0) {
            stackssize[counter+ ++wins] = std::max(stackssize[counter], stackssize[counter+wins]+stackssize[counter]);
            score = (score == 0) ? 1 : score * 2;
        }
    }
    res.first += score;
    score = 0; counter++;
  }

  for(auto ss: stackssize) res.second += ss.second;

  return res;
}