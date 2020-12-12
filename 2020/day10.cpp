#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int inp, cj, maxj(0);
  std::vector<int> pa{0};
  while (std::cin >> inp) {
    pa.push_back(inp);
    maxj = std::max(maxj, inp);
  }
  pa.push_back(maxj+3);

	std::sort(pa.begin(), pa.end());

  int j1(0), j3(0), last;
  for(auto a: pa) {
    if ((a - last) == 1) j1++;
    if ((a - last) == 3) j3++;
    last = a;
  }
  res.first = (j1 * j3);

	std::unordered_map<std::uintmax_t, std::uintmax_t> counts{{0,1}};
	for(auto a : pa)
		counts[a] += counts[a - 1] + counts[a - 2] + counts[a - 3];
  res.second = counts[pa.back()];
  return res;
}

int main(int argc, char *argv[]) {
  output_for_timing = (argc > 1);
  post_solve(solve());
}
