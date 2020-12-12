#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string quant, chr, pass;
  while (std::cin >> quant >> chr >> pass) {
    int cnt = std::count(pass.begin(), pass.end(), chr[0]);
    int pos = quant.find('-');
    int minv = std::stoi(quant.substr(0, pos));
    int maxv = std::stoi(quant.substr(pos+1));
    if (cnt >= minv && cnt <= maxv)
      res.first++;
    if (!(pass[minv-1] == chr[0]) != !(pass[maxv-1] == chr[0])) 
      res.second++;
  }
  return res;
}

int main(int argc, char *argv[]) {
  output_for_timing = (argc > 1);
  post_solve(solve());
}

