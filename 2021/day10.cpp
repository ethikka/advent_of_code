#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::string const str = "-([{<";

int64_t check_line(std::string inp) {
  std::stack<char> cs;
  for(auto c: inp) {
    switch (c) {
      case ')': if (cs.top() == '(') cs.pop(); else return 3; break;
      case ']': if (cs.top() == '[') cs.pop(); else return 57; break;
      case '}': if (cs.top() == '{') cs.pop(); else return 1197; break;
      case '>': if (cs.top() == '<') cs.pop(); else return 25137; break;
      default: cs.push(c);
    }
  }

  int64_t res(0);
  while (!cs.empty()) {
    char c = cs.top();
    cs.pop();
    res *= 5;
    res += str.find(c);
  }
  return res*-1;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::vector<int64_t> br;
  while (std::cin >> line) {
    auto r = check_line(line);
    if (r > 0) res.first += r;
    if (r < 0) br.push_back(r*-1);
  }
  std::sort(br.begin(), br.end());
  res.second = br.at(br.size()/2);
  return res;
}