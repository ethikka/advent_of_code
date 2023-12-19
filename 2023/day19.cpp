#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <regex>
#include <queue>
#include "../common/lib.h"

class part {
  public:
    std::map<char,int64_t> ratings;
    part(std::string input) { sscanf(input.c_str(), "{x=%ld,m=%ld,a=%ld,s=%ld", &ratings['x'], &ratings['m'], &ratings['a'], &ratings['s']); };
};

typedef std::function<std::string(part)> rulefunc;
struct func;
std::map<std::string,func> rules;

struct func {
  char c,o;
  int v;
  std::string tr,fa;
  rulefunc fx;
  std::string from_string(std::string name, std::string line) {
    std::regex regexp("(.)(.)([0-9]*):([A-Za-z]*),(.*)");
    std::smatch pieces_match;
    if (std::regex_match(line, pieces_match, regexp)) {
      char        lc  = c  = pieces_match[1].str()[0];
      char        lo  = o  = pieces_match[2].str()[0];
      int         lv  = v  = std::stoi(pieces_match[3].str());
      std::string ltr = tr = pieces_match[4].str();
      std::string lfa = fa = pieces_match[5].str();
      if (fa.find(':') != std::string::npos) {
        func fr; 
        lfa = fa = fr.from_string("sub"+name, fa);
      }
      if (o == '>') fx = [lc,lo,lv,ltr,lfa](part p) { return (p.ratings[lc] > lv)?ltr:lfa; };
      else          fx = [lc,lo,lv,ltr,lfa](part p) { return (p.ratings[lc] < lv)?ltr:lfa; };
    }
    rules[name] = *this;
    return name;
  };
};

struct work {
  std::string current_rule;
  std::map<char, std::pair<int64_t,int64_t>> ranges;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<part> parts;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line[0] == '{') parts.push_back(part(line));
    else if (line.size() > 0) {
      line.pop_back();
      std::string name = line.substr(0, line.find('{'));
      func f; f.from_string(name, line.substr(line.find('{')+1));
    };
  }

  for(auto p: parts) {
    std::string rr = "in";
    while (rr != "A" && rr != "R") rr = rules[rr].fx(p);
    if (rr == "A") res.first += p.ratings['x']+p.ratings['m']+p.ratings['a']+p.ratings['s'];
  }

  std::queue<work> q;
  work start{"in",{{'x', {1,4000}},{'m', {1,4000}},{'a', {1,4000}},{'s', {1,4000}}}};
  q.emplace(start);
  while (!q.empty()) {
    auto w = q.front(); q.pop();
    if      (w.current_rule == "R"); 
    else if (w.current_rule == "A") 
      res.second += (w.ranges['x'].second-w.ranges['x'].first+1)*(w.ranges['m'].second-w.ranges['m'].first+1)*(w.ranges['a'].second-w.ranges['a'].first+1)*(w.ranges['s'].second-w.ranges['s'].first+1);
    else {
      auto r3 = rules[w.current_rule];
      auto wl(w), wr(w); wl.current_rule = r3.tr; wr.current_rule = r3.fa;
      if (r3.o == '<') wl.ranges[r3.c].second = r3.v-1; else wl.ranges[r3.c].first = r3.v+1; 
      q.emplace(wl);
      if (r3.o == '<') wr.ranges[r3.c].first = r3.v; else wr.ranges[r3.c].second = r3.v; 
      q.emplace(wr);
    }
  }
  return res;
}