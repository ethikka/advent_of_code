#include <sstream>
#include <vector>
#include <cmath>
#include "../common/lib.h"

std::string const str = "+*mM ><=";


std::vector<bool> rep;
int repptr(0);

std::vector<bool> hex_to_bin(char c) {
  switch (c) {
    case '0': return {false, false, false, false};
    case '1': return {false, false, false,  true};
    case '2': return {false, false,  true, false};
    case '3': return {false, false,  true,  true};
    case '4': return {false,  true, false, false};
    case '5': return {false,  true, false,  true};
    case '6': return {false,  true,  true, false};
    case '7': return {false,  true,  true,  true};
    case '8': return { true, false, false, false};
    case '9': return { true, false, false,  true};
    case 'A': return { true, false,  true, false};
    case 'B': return { true, false,  true,  true};
    case 'C': return { true,  true, false, false};
    case 'D': return { true,  true, false,  true};
    case 'E': return { true,  true,  true, false};
    case 'F': return { true,  true,  true,  true};
  };
  return {};
}

int read_bits(int num) {
  int m(1), res(0);
  repptr += num;
  for (int i = 1; i <= num; i++) {
    res += (rep[repptr-i]?1:0) * m;
    m *= 2;
  }
  return res;
}

class packet {
public:
  int version;
  int id;
  int64_t literal = 0;
  std::vector<packet> subpackets;
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
          while (repptr < nb) {
            packet sp;
            sp.read_packet_data();
            subpackets.push_back(sp);
          }
        } else {
          int np = read_bits(11);
          for (int i = 0; i < np; i++) {
            packet sp;
            sp.read_packet_data();
            subpackets.push_back(sp);
          }
        }
    }
  }

  int64_t versionsum() {
    int64_t v(version);
    for(auto p: subpackets)
      v += p.versionsum();
    return v;
  }

  int64_t value() {
    int64_t r(0);
    switch (id) {
      case 0: 
        for(auto p: subpackets) r += p.value();
        return r;
      case 1: 
        r = 1;
        for(auto p: subpackets) r *= p.value();
        return r;
      case 2: 
        r = subpackets[0].value();
        for(auto s: subpackets) r = std::min(r, s.value()); 
        return r;
      case 3: 
        r = subpackets[0].value();
        for(auto s: subpackets) r = std::max(r, s.value()); 
        return r;
      case 4: return literal; 
      case 5: return (subpackets[0].value() > subpackets[1].value()) ? 1 : 0; 
      case 6: return (subpackets[0].value() < subpackets[1].value()) ? 1 : 0; 
      case 7: return (subpackets[0].value() == subpackets[1].value()) ? 1 : 0; 
    }
    return 0;
  }

  void print() {
    std::cout << str[id];
    if (id == 4) std::cout <<  literal << " ";
    else {       std::cout << "( ";
                 for(auto s: subpackets) s.print();
                 std::cout << ") ";
         }
  }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  char c;
  while (std::cin >> std::hex >> c) for(auto b: hex_to_bin(c)) rep.push_back(b);
//- print binary representation
//  for(auto v: rep) std::cout << (v?1:0);
//  std::cout << std::endl;

  packet p;
  p.read_packet_data();
//  print visual representation
//  p.print();
  return { p.versionsum(), p.value() };
}