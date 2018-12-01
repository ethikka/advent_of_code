#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_set>

void solve() {
  long value;
  std::vector<long> freq;
  while (std::cin >> value) {
	  freq.push_back(value);
  }
  long res1 = 0;
  for (auto &fr: freq) {
	  res1 += fr;
  }

  int res2 = 0;
  long index = 0;
  std::unordered_set<long> fr2;
  while (fr2.count(res2) == 0)
  {
	  fr2.insert(res2);
	  res2 += freq[index % freq.size()];
	  index++;
  }

  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

