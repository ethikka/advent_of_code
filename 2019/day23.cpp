#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <chrono>
#include "intcode.h"

void solve() {
  int res1(0), res2(0);

  intcode interpreter("./2019/fileinput.day23");
  std::map<int,intcode> network;
  while (network.size() < 50) {
    auto tmp = interpreter.clone();
    tmp.inputqueue({(int)network.size()});
    network[network.size()] = tmp;
  }

  std::map<int,std::vector<int64_t>> outputs;
  std::vector<int64_t> nat;
  std::set<int64_t> natvalues;

  while (true) {
    int idleCount(0);
    for (int idx=0; idx < network.size(); idx++) {
      int64_t x(0), y(0), target(0);
      auto r = network[idx].run();
      if (r == inputMode) {
        network[idx].inputqueue({-1});
        r = network[idx].run();
      }
      if (r == outputMode) {
        auto rss = network[idx].output();
        outputs[idx].push_back(rss);
        if (outputs[idx].size() == 3) {
          int64_t target = outputs[idx].at(0);
          int64_t x = outputs[idx].at(1);
          int64_t y = outputs[idx].at(2);
          outputs[idx].clear();

          if (target == 255) {
            if (res1 == 0) 
              res1 = y;
            nat.clear();
            nat.push_back(x);
            nat.push_back(y);            
          } else if (target < 50) {
            network[target].inputqueue({x,y});
          }
        }
      } else if (r == inputMode) {
        idleCount++;
      }
    }
    if (idleCount == network.size() && !nat.empty()) {
      network[0].inputqueue({nat[0], nat[1]});
      if (natvalues.count(nat[1]) > 0) {
        res2 = nat[1];
        break;
      }
      natvalues.insert(nat[1]);
      nat.clear();
    }
  }
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

