#include <sstream>
#include <vector> 
#include <algorithm>
#include "../common/lib.h"

int64_t test(int64_t t, int64_t d) {
  int64_t res(0);
  for (int z = 0; z < t; z++) if (((t-z)*z) > d) res++;
  return res;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{1,0};
  std::string time, dist;
  std::getline(std::cin, time); time = time.substr(10); std::istringstream sst(time);
  std::getline(std::cin, dist); dist = dist.substr(10); std::istringstream ssd(dist);
  time.erase(std::remove_if(time.begin(), time.end(), isspace), time.end()); int64_t b_time = std::stol(time);
  dist.erase(std::remove_if(dist.begin(), dist.end(), isspace), dist.end()); int64_t b_dist = std::stol(dist);

  std::vector<std::pair<std::uintmax_t,std::uintmax_t>> td;
  while (!sst.eof()) {
    int64_t t, d;
    sst >> t; ssd >> d;
    td.push_back({t, d});
  }

  for(auto t: td) res.first *= test(t.first, t.second);
  res.second = test(b_time, b_dist);
  return res;
}