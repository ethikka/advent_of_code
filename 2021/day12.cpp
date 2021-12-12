#include <sstream>
#include <vector>
#include <queue>
#include <map>
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
      bool _visited(std::count(route.begin(), route.end(), n) > 0);
      if (vc > 0 && route.back() == "end") return false;
      if (n[0] < 91) route.push_back(n);
      else if (part_b) {
        if (_visited && !small_dup && (n != "start") ) {
          small_dup = true;
          route.push_back(n);
        } else if (!-_visited) route.push_back(n);
      } else if (!_visited) route.push_back(n);
      return route.size() != vc;
    }
};

struct work {
  path p;
  std::string nd;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (std::cin >> line) {
    int p = line.find_first_of('-');
    possible_paths.insert({line.substr(0,p), line.substr(p+1)});
    possible_paths.insert({line.substr(p+1), line.substr(0,p)});
  }

  path _p;
  std::queue<work> q;
  q.push({ _p, "start" });
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    if (w.nd == "end") res.first++;
    if (w.p.canVisit(w.nd, false)) for (auto p: possible_paths) if (p.first == w.p.last()) q.push({w.p, p.second});
  }

  q.push({ _p, "start" });
  while (!q.empty()) {
    auto w = q.front();
    q.pop();
    if (w.nd == "end") res.second++;
    if (w.p.canVisit(w.nd, true)) for (auto p: possible_paths) if (p.first == w.p.last()) q.push({w.p, p.second});
  }
  return res;
}