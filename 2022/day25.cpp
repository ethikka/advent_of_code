#include <sstream>
#include <algorithm>
#include <map>
#include "../common/lib.h"

std::string to_snafu(std::intmax_t num) {
  std::cout << num << std::endl;
  std::string res;
  while (num) {
    char c = '0' + (num % 5);
    bool high = c > '2';
    if (high)
      switch (c) {
        case '3':c = '='; break;
        case '4':c = '-'; break;
        default: c = '0';
      }
    res += c;
    num = num / 5 + high;  
  }
  std::reverse(res.begin(), res.end());
  return res;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::intmax_t res(0);
  std::string line;
  while (std::cin >> line) {
    int64_t number = 0;
    for (int64_t i = line.size()-1, power=1; i >= 0; --i, power*=5)
      switch (line[i]) {
      case '-': number -= power; break;
      case '=': number -= (2*power); break;
      default: number += power * (line[i]-'0');
      }
    res += number;
  }
  std::cout << to_snafu(res) << std::endl;
  return {0,0};
}