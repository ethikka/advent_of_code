#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include "../common/lib.h"
#include "../common/insertordered_map.h"

class lens {
  private:
    std::string instr;
    int64_t HASH(std::string inp) { int r(0); for(auto c: inp) r = ((r+(int)c)*17) % 256; return r; }
  public:
    std::string label;
    int focallength;
    bool remove;
    lens(std::string inp) {
      instr = inp; 
      remove = inp[inp.size()-1] == '-';
      label = inp.substr(0, inp.size()-1);
      if (!remove) {
        focallength = std::stoi(inp.substr(inp.size()-1));
        label = inp.substr(0, inp.size()-2);
      };
    };
    int64_t part_a() { return HASH(instr); };
    int64_t box() { return HASH(label); };
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<lens> lenses;
  std::map<int64_t,tbb::insertordered_map<std::string,int64_t>> boxes;
  char c;
  std::string instr;

  while (std::cin >> c) if (c == ',') { lenses.push_back({instr}); instr = ""; } else instr += c;
  lenses.push_back({instr});

  for(auto l: lenses) {
    res.first += l.part_a();
    if (l.remove) boxes[l.box()].erase(l.label); else boxes[l.box()][l.label] = l.focallength;
  }

  for (auto b: boxes) {
    int64_t cnt(1);
    for (auto c: b.second.get_map()) 
      res.second += ((b.first+1)*cnt++*c.second);
  }
  return res;
}