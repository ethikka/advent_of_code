#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include "../common/lib.h"

struct work {
  std::string mol;
  int stepcount;

  bool operator <(const work &compare_to) const { return (mol.size() < compare_to.mol.size()) && stepcount < compare_to.stepcount; }  
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string pre, d, post, mol;
  std::vector<std::pair<std::string,std::string>> reps;
  for (int i = 0; i < 43; i++) {
    std::cin >> pre >> d >> post;
    reps.push_back({pre, post});
  }
  std::cin >> mol;

  std::unordered_set<std::string> newm;
  for(auto r: reps) {
    int pos(0);
    while ((pos = mol.find(r.first, pos)) != mol.npos) {
      newm.insert(mol.substr(0, pos)+r.second+mol.substr(pos+r.first.size()));
      pos++;
    }
  }

  int sz(-1);
  for(int i = 0; i < mol.size(); i++) {
    auto k = mol.substr(i, 2);
    if (k == "Rn")          { std::cout << "("; i++; }
    else if (k == "Ar")     { std::cout << ")"; i++; }
    else if (mol[i] == 'Y') { sz -= 2; std::cout << ",";}
    else if (mol[i] > 'Z')  { }
    if (mol[i] <= 'Z')      { sz++; std::cout << "X";}
  }
  return {newm.size(), sz};
}