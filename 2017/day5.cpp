#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>

int jumps(int offset, std::vector<int>& trampolines) {
  int ptr = 0;
  int jumps = 0;
  while (ptr < trampolines.size() && ptr > -1) {
    int oldptr = ptr;
    ptr += trampolines[ptr];
    jumps++;
    trampolines[oldptr] += trampolines[oldptr] >= 3 ? offset : 1;
  }
  return jumps;
}

void solve(void) {
  std::vector<int> trampolines {std::istream_iterator<int>{std::cin}, {}};
  std::vector<int> trampolinesb(trampolines);
  std::cout << "Solution a: " << jumps( 1, trampolines ) << std::endl;
  std::cout << "Solution b: " << jumps(-1, trampolinesb) << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

