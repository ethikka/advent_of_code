#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

void solve() {
  std::string line;
  int res1(0), res2(0);

  int start_range(206938), end_range(679128);

  for (int i = start_range; i <= end_range; i++) {
    std::vector<int> digits;
    int tmp = i;
    while (tmp) {
      digits.push_back(tmp % 10);
      tmp /= 10;
    }

    bool repeats(false), increasing(true), exact_doubles(false);
    for (int cnt = 6; cnt > 0; cnt--) {
      repeats |= (digits[cnt] == digits[cnt-1]);
      increasing = increasing && (digits[cnt] <= digits[cnt-1]);
    }

    // only exact doubles =)
    exact_doubles = (                            (digits[6] == digits[5]) && (digits[6] != digits[4])) ||
                    ((digits[6] != digits[5]) && (digits[5] == digits[4]) && (digits[5] != digits[3])) ||
                    ((digits[5] != digits[4]) && (digits[4] == digits[3]) && (digits[4] != digits[2])) ||
                    ((digits[4] != digits[3]) && (digits[3] == digits[2]) && (digits[3] != digits[1])) ||
                    ((digits[3] != digits[2]) && (digits[2] == digits[1]) && (digits[2] != digits[0])) ||
                    ((digits[2] != digits[1]) && (digits[1] == digits[0]));

    if (increasing && repeats)                  res1++;
    if (increasing && repeats && exact_doubles) res2++;
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

