#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <chrono>

struct element {
  std::string result;
  int64_t amount;
  std::map<std::string, int64_t> elements;  
};

std::map<std::string,element> reactions;

int64_t ore_needed(std::string el, int amount) {
  std::map<std::string, int64_t> needed_elements;
  std::map<std::string, int64_t> leftovers;
  int64_t res(0);

  needed_elements[el] = amount;

  while (needed_elements.size() > 0) {
    std::string elem = needed_elements.begin()->first;
    int64_t mult = needed_elements.begin()->second;
    needed_elements.erase(needed_elements.begin());
    if (elem == "ORE") res += mult;
    else {
      if (leftovers.count(elem) > 0) {
        mult -= leftovers[elem];
        leftovers.erase(elem);
      }
      if (mult != 0) {
        int64_t multiplier = ceil((mult*1.0 / reactions[elem].amount*1.0));
        leftovers[elem] += (reactions[elem].amount*multiplier) - mult;
        for (auto s: reactions[elem].elements)
          needed_elements[s.first] += s.second*multiplier;
      }
    }
  }
  return res;
}

void solve() {
  std::string name, discard;
  int64_t amount;
  int64_t res2(0);
  element tmp;

  while (std::cin >> amount >> name) {
    if (name.back() == ',') 
      tmp.elements[name.substr(0, name.size()-1)] = amount;
    else  {
      tmp.elements[name] = amount;
      std::cin >> discard >> tmp.amount >> tmp.result;
      reactions[tmp.result] = tmp;
      element tmp2;
      tmp = tmp2;
    }
  }

  int idx(2), diff(1000000000);
  while (idx += diff) 
    if (ore_needed("FUEL", idx) > 1000000000000) {
      if (ore_needed("FUEL", idx-1) < 1000000000000) {
        res2 = idx-1;
        break;
      }
      idx -= diff;
      diff /= 2;
    } 
  
  std::cout << "Solution part 1: " << ore_needed("FUEL", 1) << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}