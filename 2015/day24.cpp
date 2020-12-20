#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "../common/lib.h"

class combination {
    bool cont { true };
    std::vector <bool> v;
  public:
    combination (int n, int r) : v(r, true) {
      v.resize (n, false);
    }

    bool next (std::vector<int> & res) {
      if (!cont) return false;
      for (int i(0), j(0); i < v.size(); ++i)
        if (v[i])
          res[j++] = i;
      cont = std::prev_permutation(std::begin(v), std::end(v));
      return true;
    }
  };

int64_t check (const std::vector<int> & nums, int target) {
  int min(1);
  while(std::accumulate(nums.rbegin(), nums.rbegin() + ++min, 0) <= target);

  std::vector<int> ind(min);
  for (int r(min); true; ind.resize(++r)) {
    combination comb(nums.size(), r);
    while (comb.next(ind)) {
      int sum(0); 
      uint64_t prod(1);
      for (int index: ind)
        sum += nums[index], prod *= nums[index];
      if (sum == target) return prod;
    }
  }
  return 0;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::vector<int> pcks;
  int inp(0), total(0);

  while (std::cin >> inp) {
    pcks.push_back(inp);
    total += inp;
  }
  
  res.first = check(pcks, total/3);
  res.second = check(pcks, total/4);
  return res;
}
