#include <sstream>
#include <regex>
#include "../common/lib.h"

std::string strip_red(std::string input) {
  std::string tmp(input);
  int pos;
  while ((pos = tmp.find("\"red\"")) != tmp.npos) {
    if (tmp[pos-1] == ',' || tmp[pos-1] == '[')  // "red" is part of an array
      tmp = tmp.erase(pos, 5);
    else {
      int acnt(1), s = pos;
      while (acnt != 0) {
        if (tmp[s] == '{') acnt--;
        if (tmp[s] == '}') acnt++;
        s--;
      };

      int bcnt(1), e = pos;
      while (bcnt != 0) {
        if (tmp[e] == '{') bcnt++;
        if (tmp[e] == '}') bcnt--;
        e++;
      };
      tmp = tmp.erase(s+1, e-s-1);
    }
  }
  return tmp;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string inp;
  while (std::cin >> inp) {
    std::regex number_regex("([-0-9])+");
    std::string input_b = strip_red(inp);
    auto it = std::sregex_iterator();
    for (std::sregex_iterator i = std::sregex_iterator(inp.begin(), inp.end(), number_regex); i != it; ++i) res.first += std::stoi(i->str());
    for (std::sregex_iterator i = std::sregex_iterator(input_b.begin(), input_b.end(), number_regex); i != it; ++i) res.second += std::stoi(i->str());
  }
  return res;
}