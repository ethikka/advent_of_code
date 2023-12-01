#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::string untextify(std::string input) {
  int cnt(0);
  std::vector<std::string> nums = {"_________", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  while (cnt <= input.length()) {
    for(auto s: nums) if (input.substr(cnt, s.length()) == s) input.replace(cnt, 1, std::to_string(std::find(nums.begin(), nums.end(), s)-nums.begin()));
    cnt++;
  }
  return input;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;

  while (!std::cin.eof()) { 
    char c;
    std::getline(std::cin, line);

    std::istringstream ssl_a(line);
    std::vector<int> numbers_a;
    while (ssl_a >> c) if (c >= '0' && c <= '9') numbers_a.push_back((int)(c-'0'));

    std::istringstream ssl_b(untextify(line));
    std::vector<int> numbers_b;
    while (ssl_b >> c) if (c >= '0' && c <= '9') numbers_b.push_back((int)(c-'0'));

    res.first += (numbers_a.front()*10+numbers_a.back());
    res.second += (numbers_b.front()*10+numbers_b.back());
  }
  return res;
}