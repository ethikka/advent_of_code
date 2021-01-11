#include <sstream>
#include "../common/lib.h"

int unescape(std::string input) {
  std::string ns(input);
  while (ns.find("\\\\") != ns.npos) ns.replace(ns.find("\\\\"), 2, "#");
  while (ns.find("\\\"") != ns.npos) ns.replace(ns.find("\\\""), 2, "#");
  while (ns.find("\\x") != ns.npos) ns.replace(ns.find("\\x"), 4, "#");
  while (ns.find("\"") != ns.npos) ns.replace(ns.find("\""), 1, "");
  return ns.size();
}

int escape(std::string input) {
  std::string ns(input);
  while (ns.find("\\") != ns.npos) ns.replace(ns.find("\\"), 1, "##");
  while (ns.find("\"") != ns.npos) ns.replace(ns.find("\""), 1, "##");
  return ns.size()+2;
}


std::pair<std::uintmax_t,std::uintmax_t> solve() {
  int mem(0), chr(0), chrb(0);
  std::string line;
  while (std::cin >> line) {
    mem += line.size();
    chr += unescape(line);
    chrb += escape(line);
  }
  return {mem-chr, chrb-mem};
}