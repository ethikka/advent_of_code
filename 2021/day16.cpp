#include <sstream>
#include <vector>
#include <cmath>
#include "../common/lib.h"

std::vector<bool> rep;
int repptr(0);

std::vector<bool> hex_to_bin(int c) {
   // Note to future me:  have fun figuring this out  ;-)
   return {(c > 55), 
           (c > 51 && c != 56 && c != 57 && c != 65 && c != 66),
           (c == 50 || c == 51 || c == 54 || c == 55 || c == 65 || c == 66 || c == 69 || c == 70),
           (c == 49 || c == 51 || c == 53 || c == 55 || c == 57 || c == 66 || c == 68 || c == 70)};
}

int64_t read_bits(int num) {
  int m(1), res(0);
  repptr += num;
  for (int i = 1; i <= num; i++, m *= 2) res += (rep[repptr-i]?1:0) * m;
  return res;
}

class packet {
private:
  int version;
  int id;
public:
  int64_t literal = 0;
  std::vector<packet> subpackets;
  packet() { read_packet_data(); }
  void read_packet_data() {
    version = read_bits(3);
    id = read_bits(3);
    switch (id) {
      case 4: 
        while (rep[repptr++]) literal = (literal*16) + read_bits(4);
        literal = (literal*16) + read_bits(4);
        break;
      default:
        if (read_bits(1) == 0) {
          int n = read_bits(15);
          int nb = n+repptr;
          while (repptr < nb) { packet sp; subpackets.push_back(sp); }
        } else {
          int np = read_bits(11);
          for (int i = 0; i < np; i++) { packet sp; subpackets.push_back(sp); }
        }
    }
  }

  int64_t versionsum() {
    int64_t v(version);
    for(auto p: subpackets) v += p.versionsum();
    return v;
  }

  int64_t value() {
    int64_t r(subpackets.size() > 0 ? subpackets[0].value():0);
    switch (id) {
      case 0: for(int i=1; i < subpackets.size(); i++) r += subpackets[i].value(); return r;
      case 1: for(int i=1; i < subpackets.size(); i++) r *= subpackets[i].value(); return r;
      case 2: for(auto s: subpackets) r = std::min(r, s.value());                  return r;
      case 3: for(auto s: subpackets) r = std::max(r, s.value());                  return r;
      case 4: return literal; 
      case 5: return (subpackets[0].value()  > subpackets[1].value()) ? 1 : 0; 
      case 6: return (subpackets[0].value()  < subpackets[1].value()) ? 1 : 0; 
      case 7: return (subpackets[0].value() == subpackets[1].value()) ? 1 : 0; 
    }
    return 0;
  }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char c;
  while (std::cin >> std::hex >> c) for(auto b: hex_to_bin((int)c)) rep.push_back(b);

  packet p;
  return { p.versionsum(), p.value() };
}