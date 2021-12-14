#include <sstream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

std::map<std::string,std::vector<std::string>> possible_paths;

int64_t run2(bool part_b) {
  int64_t res(0);
  std::queue<std::string> q;
  q.push({ "start" });
  while (!q.empty()) {
    std::string w = q.front();
    q.pop();
    std::string l = (w.find_last_of('-') == std::string::npos) ? w : w.substr(w.find_last_of('-')+1);
    if (l == "end") res++;
    else 
      for (std::string p: possible_paths[l]) {
        std::string s = "";
        if (p[0] < 91) q.push({w + "-" + p});
        else {
          size_t pp = w.find(p);
          if (pp == std::string::npos) q.push({w + "-" + p});
          else if (part_b) if (w[0] != '@') if (w.find(p, pp+1) == std::string::npos) q.push({'@' + w + "-" + p});
        }
      }
  }
  return res;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string line;
  while (std::cin >> line) {
    int p = line.find_first_of('-');
    std::string from(line.substr(0,p)), to(line.substr(p+1));
    if (to   != "start") possible_paths[from].push_back(to);
    if (from != "start") possible_paths[to].push_back(from);
  }
  return { run2(false), run2(true) };
}