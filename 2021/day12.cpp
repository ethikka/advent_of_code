#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "../common/lib.h"

std::multimap<std::string,std::string> possible_paths;

class path {
  private:
    std::vector<std::string> route;
    bool small_dup = false;
  public:
    std::string last() { return route.back(); }
    bool canVisit(std::string n, bool part_b) {
      int vc = route.size();
      if (vc > 0 && route.back() == "end") return false;
      if (n[0] < 91) route.push_back(n);
      else if (std::count(route.begin(), route.end(), n) == 0) route.push_back(n); 
      else if (part_b) 
        if (!small_dup && (n != "start") ) {
          small_dup = true;
          route.push_back(n);
        }
      return route.size() != vc;
    }
};

struct work {
  path p;
  std::string nd;
};

int64_t run(bool part_b) {
  path _p;
  int64_t res(0);
  std::queue<work> q;
  q.push({ _p, "start" });
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    if (w.nd == "end") res++;
    if (w.p.canVisit(w.nd, part_b)) for (auto p: possible_paths) if (p.first == w.p.last()) q.push({w.p, p.second});
  }
  return res;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string line;
  while (std::cin >> line) {
    int p = line.find_first_of('-');
    possible_paths.insert({line.substr(0,p), line.substr(p+1)});
    possible_paths.insert({line.substr(p+1), line.substr(0,p)});
  }
  return { run(false), run(true)};
}