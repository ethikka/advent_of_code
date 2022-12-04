#include <sstream>
#include "../common/lib.h"

struct elf_pair
{
    int l1, l2;
    int r1, r2;
    bool part_a() { return (l1 <= r1 && l2 >= r2) || (r1 <= l1 && r2 >= l2); }
    bool part_b() { return !(l2 < r1 || r2 < l1); }
};

std::istream &operator>>(std::istream &is, elf_pair &p)
{
    char c;
    is >> p.l1 >> c >> p.l2 >> c >> p.r1 >> c >> p.r2;
    return is;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  elf_pair ep;
  while (std::cin >> ep) {
    if (ep.part_a()) res.first++;
    if (ep.part_b()) res.second++;
  }
  return res;
}