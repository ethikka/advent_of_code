#include <sstream>
#include <vector>
#include "../common/lib.h"

struct schematicpoint {
  int x;
  int y;
  int64_t content;
  std::vector<int64_t> in_range;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<schematicpoint> numbers;
  std::vector<schematicpoint> symbols;
  std::string line;
  int yy(0);
  while (std::getline(std::cin, line)) {
    int num(0), xx(0), xxx(0);
    char c;
    std::istringstream ssl(line);
    while (ssl >> c) {
      if (c >= '0' && c <= '9') {
        xxx = xx;
        do {
          num *= 10; num += (c - '0');
          ssl >> c;
          xx++;
        } while (c >= '0' && c <= '9' && !ssl.eof());
        numbers.push_back({xxx, yy, num});
        num = xxx = 0;
      }
      if (c != '.' && !(c >= '0' && c <= '9')) {
        symbols.push_back({xx, yy, (int)c});
      }
      xx++;
    }
    yy++; xx = 0;
  }
  // make a list of in range numbers per symbol
  for(auto &nn: numbers) {
    int minx(nn.x-1), maxx(nn.x+std::to_string(nn.content).length()), miny(nn.y-1), maxy(nn.y+1);
    for (auto &ss: symbols) 
      if (ss.x >= minx && ss.x <= maxx && ss.y >= miny && ss.y <= maxy) {
        ss.in_range.push_back(nn.content);
        nn.in_range.push_back(ss.content);
      }
  }

  for (auto nn: numbers) 
    if (nn.in_range.size() > 0)
      res.first += nn.content;
  
  for (auto ss: symbols) 
    if (ss.in_range.size() == 2 && ss.content == '*')
      res.second += ss.in_range.front()*ss.in_range.back();

  return res;
}