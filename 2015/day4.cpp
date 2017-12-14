#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "md5.h"
#include <chrono>

void solve(void) {
  // md5(std::string)
  std::string secret;
  getline(std::cin, secret);
  int num = 0;
  int sol_a = 0;
  std::string res = "hjkhasjkfs";
  while (res.substr(0, 6) != "000000")
  {
    if (res.substr(0,5) == "00000" && sol_a == 0)
      sol_a = num;
    num++;
    res = md5(secret+std::to_string(num));
  }

  std::cout << "AdventCoins everywhere, but mostly at " << sol_a << " (solution a) and " << num << " (solution b)" << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

