#include <sstream>
#include <regex>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  bool enabled = true;
  std::regex regexp(R"x((\d+?),(\d+?)[)].*)x");

  while (std::getline(std::cin, line)) {
    int pos = 0, pos_do = 0, pos_dont = 0;
    while ((pos = line.find("mul(")) != std::string::npos) {
      if ((pos_do = line.find("do()")) != std::string::npos && pos_do < pos) enabled = true;
      if ((pos_dont = line.find("don't()")) != std::string::npos && pos_dont < pos) enabled = false;
      if (pos_dont < pos && pos_do < pos && pos_do != std::string::npos  && pos_dont != std::string::npos) enabled = (pos_do > pos_dont);

      std::string test = line.substr(pos+4,8);
      std::smatch pieces_match;
      if (std::regex_match(test, pieces_match, regexp)) {
        int add = std::stoi(pieces_match[1].str()) * std::stoi(pieces_match[2].str());
        res.first += add;
        if (enabled) res.second += add;
      }
      line = line.substr(pos+5);
    }
  }
  return res;
}