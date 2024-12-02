#include <sstream>
#include <vector>
#include "../common/lib.h"

class report {
    std::vector<int> reports;
  public:
    void add(int n) { reports.push_back(n); }
    bool valid(std::vector<int> rr) {
      bool rising = rr.at(0) < rr.at(1);
      bool valid = true;
      for (int i = 1; i < rr.size(); i++) {
        int diff = rr.at(i-1)-rr.at(i);
        valid &= rising ? diff < 0 : diff > 0;
        diff = std::abs(diff);
        valid &= ((diff > 0) && (diff < 4));
      }
      return valid;
    };
    bool valid_a() { return valid(reports); }
    bool valid_b() {
      if (valid(reports)) return true;
      for (int i = 0; i < reports.size(); i++) {
        std::vector<int> subr;
        for (int j = 0; j < reports.size(); j++) if (i != j) subr.push_back(reports.at(j));
        if (valid(subr)) return true;
      }
      return false;
    };

  };

std::vector<report> reports;

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (std::getline(std::cin, line)) {
    report r;
    std::istringstream ssl(line);
    while (!ssl.eof()) {
      int ii;
      ssl >> ii;
      r.add(ii);
    }
    reports.push_back(r);
  }

  for(auto rr: reports) {
    if (rr.valid_a()) res.first++;
    if (rr.valid_b()) res.second++;
  }
  return res;
}