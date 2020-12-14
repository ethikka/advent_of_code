#include <sstream>
#include <bitset>
#include <map>
#include <vector>
#include <cmath>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string inp;
  std::map<int,int> currentmask;
  std::vector<int> mask2;
  std::map<int64_t,int64_t> memory;
  std::map<int64_t,int64_t> memory_b;
  while (std::cin >> inp) {
    if (inp == "mask") {
      currentmask.clear();
      mask2.clear();
      std::string cmask;
      std::cin >> inp >> cmask;
      for (int i = 0; i < 36; i++) 
        if (cmask[i] != 'X') currentmask[35-i] = (cmask[i] == '1');
        else mask2.push_back(35-i);
    } else {
      std::string tmp = inp.substr(4);
      tmp.pop_back();
      int64_t num, memaddress = std::stoi(tmp);
      std::cin >> inp >> num;

      std::bitset<36> bs(num);
      std::bitset<36> ma(memaddress);
      for(auto b: currentmask) { 
        bs.set(b.first, b.second); 
        if (b.second == 1) ma.set(b.first, 1); 
      }
      memory[memaddress] = bs.to_ulong();

      // part b
      for (int i = std::pow(2, mask2.size())-1; i >=0; i--) {
        std::bitset<36> os(i);
        for (int j = 0; j < mask2.size(); j++) ma.set(mask2[j], os[j]);
        memory_b[ma.to_ulong()] = num;
      }
    }
  }

  for(auto m: memory) res.first += m.second;
  for(auto m: memory_b) res.second += m.second;
  
  return res;
}