#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

int find_num(std::string input, bool including_nums, bool first) {
  int cnt(0);
  std::vector<std::string> nums = {"_________", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  while (cnt <= input.length()) {
    int idx = first ? cnt : input.length()-cnt;
    if (including_nums) for(auto s: nums) if (input.substr(idx, s.length()) == s) return std::find(nums.begin(), nums.end(), s)-nums.begin();
    if (input[idx] >= '0' && input[idx] <= '9') return (input[idx]-'0');
    cnt++;
  }
  return -1;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (!std::cin.eof()) {
    std::getline(std::cin, line);
    res.first += (find_num(line, false, true)*10)+find_num(line, false, false);
    res.second += (find_num(line, true, true)*10)+find_num(line, true, false);
  }
  return res;
}