#include <sstream>
#include <stack>
#include <vector>
#include "../common/lib.h"

template<typename T>
void reverse(std::stack<T> &s)
{
    std::stack<T> reverse_stack;
    while(!s.empty()) {
        reverse_stack.push(std::move(s.top()));
        s.pop();
    }
    s = std::move(reverse_stack);
}

std::string print(std::stack<char> t[9]) {
  std::string tmp("");
  for (int i = 0; i < 9; i++) tmp += t[i].top();
  return tmp;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::stack<char> towers_a[9], towers_b[9];
  bool setup(true);

  while (setup) {
    std::getline(std::cin, line);
    if (line.length() == 0) {
      for (int i =0; i < 9; i++) reverse(towers_a[i]);
      setup = false;
    } else for (int i = 0; i < 9; i++) if (line.length() > i && line[1+(i*4)] != ' ') towers_a[i].push(line[1+(i*4)]);
  }
  for (int i =0; i < 9; i++) towers_b[i] = towers_a[i];

  std::string discard;
  int amount, src, dest;

  while (std::cin >> discard >> amount >> discard >> src >> discard >> dest) {
    char tt[amount];
    for (int x = 0; x < amount; x++) {
      towers_a[dest-1].push(towers_a[src-1].top());    tt[x] = towers_b[src-1].top();
      towers_a[src-1].pop();                           towers_b[src-1].pop();
    }
    for (int x = amount; x > 0; x--) towers_b[dest-1].push(tt[x-1]);
  }

  if (!output_for_timing) std::cout << "Part 1: " << print(towers_a) << std::endl << "Part 2: " << print(towers_b) << std::endl;
  return res;
}
