#include <sstream>
#include <vector>
#include "../common/lib.h"

class report {
  private:
    std::vector<int> reports;
    bool _valid(std::vector<int> rr) {
      bool valid = true;
      for (int i = 1; i < rr.size(); i++) {
        valid &= ((rr.at(0) - rr.at(1)) ^ (rr.at(i-1)-rr.at(i))) >= 0;
        int diff = std::abs(rr.at(i-1)-rr.at(i));
        valid &= ((diff > 0) && (diff < 4));
      }
      return valid;
    };
  public:
    report(std::string input) { std::istringstream ssl(input); while (!ssl.eof()) { int ii; ssl >> ii; reports.push_back(ii); }}

    bool valid_a() { return _valid(reports); }
    bool valid_b() {
      if (_valid(reports)) return true;
      for (int i = 0; i < reports.size(); i++) {
        std::vector<int> subr;
        for (int j = 0; j < reports.size(); j++) if (i != j) subr.push_back(reports.at(j));
        if (_valid(subr)) return true;
      }
      return false;
    };
  };

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::vector<report> reports;

  while (std::getline(std::cin, line)) reports.push_back(line);

  for(auto rr: reports) {
    if (rr.valid_a()) res.first++;
    if (rr.valid_b()) res.second++;
  }
  return res;
}