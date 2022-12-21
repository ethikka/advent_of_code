#include <sstream>
#include <vector>
#include <map>
#include <set>
#include "../common/lib.h"

std::string operators = " +-*/";
struct monkey;

std::map<std::string, monkey> monkeys;
std::set<std::string> route;

struct monkey {
  std::string name;
  std::uintmax_t _value = -1;
  std::string lm;
  std::string rm;
  int op;
  int64_t value() {
    if (lm != "") {
      switch (op) {
        case 1: return monkeys[lm].value()+monkeys[rm].value();
        case 2: return monkeys[lm].value()-monkeys[rm].value();
        case 3: return monkeys[lm].value()*monkeys[rm].value();
        case 4: return monkeys[lm].value()/monkeys[rm].value();
        default: return 0;
      }
    }
    else return _value;
  };

  void new_outcome(std::uintmax_t nv) {
    if (lm == "") {  _value = nv; return; }
    if (route.find(rm) != route.end()) { 
      switch (op) {
        case 1: monkeys[rm].new_outcome(nv-monkeys[lm].value()); return;
        case 2: monkeys[rm].new_outcome(monkeys[lm].value()-nv); return;
        case 3: monkeys[rm].new_outcome(nv/monkeys[lm].value()); return;
        case 4: monkeys[rm].new_outcome(monkeys[lm].value()/nv); return;
      }
    } else {
      switch (op) {
        case 1: monkeys[lm].new_outcome(nv-monkeys[rm].value()); return;
        case 2: monkeys[lm].new_outcome(monkeys[rm].value()+nv); return;
        case 3: monkeys[lm].new_outcome(nv/monkeys[rm].value()); return;
        case 4: monkeys[lm].new_outcome(monkeys[rm].value()*nv); return;
      }
    }
  };
};

std::istream &operator>>(std::istream &is, monkey &m)
{
  std::string s, n;
  std::getline(std::cin, s);
  m.name = s.substr(0, 4);
  s = s.substr(6);
  if (s.size() == 11) {
    m.lm = s.substr(0, 4);
    m.rm = s.substr(7, 4);
    m.op = operators.find(s.substr(5, 1));
  } else m._value = std::stoll(s);
  return is;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  while (!std::cin.eof()) {
    monkey m;
    std::cin >> m;
    monkeys[m.name] = m;
  }
  res.first = monkeys["root"].value();

  std::string key("humn");
  while (key != "root") for (auto m: monkeys) if (m.second.lm == key || m.second.rm == key) route.insert(route.begin(), key = m.second.name);

  if (route.find(monkeys["root"].rm) != route.end()) monkeys[monkeys["root"].rm].new_outcome(monkeys[monkeys["root"].lm].value());
  else                                               monkeys[monkeys["root"].lm].new_outcome(monkeys[monkeys["root"].rm].value());
  res.second = monkeys["humn"].value();
  return res;
}