#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct phase {
  int phasenumber;
  std::vector<int> signal;
  int basepattern[4] = { 0, 1, 0, -1 };

  void permutate() {
    phasenumber++;
    std::vector<int> newsignal;
    for(int idx = 0; idx < signal.size(); idx++) {
      int res(0);
      for (int iidx = idx; iidx < signal.size(); iidx++) 
        res += signal[iidx] * basepattern[((iidx+1) / (idx+1)) % 4];
      newsignal.push_back(abs(res) % 10);
    };
    signal = newsignal;
  };

  void permutate2(int offset) {
    phasenumber++;
    for (int idx = signal.size()-2; idx >= offset; idx--) 
      signal[idx] = abs(signal[idx]+signal[idx + 1]) % 10;
  };

  int res(int offset) {
    int multiplier(10000000);
    int result(0);
    for (int i = offset; i < offset+8; i++) {
      result += signal[i]*multiplier;
      multiplier /= 10;
    }
    return result;
  }
};

void solve() {
  char c;
  phase p;
  p.phasenumber = 0;
  int offset = 0;

  while (std::cin >> c) 
    p.signal.push_back((int)c-48);

  phase p1(p);
  while (p1.phasenumber < 100) 
    p1.permutate();

  for (int i = 0, multiplier = 1000000; i < 7; i++, multiplier /= 10) 
    offset += p.signal[i]*multiplier;

  phase p2(p);
  for (int i = 0; i < 9999; i++)
    for(int idx = 0; idx < p.signal.size(); idx++)
      p2.signal.push_back(p2.signal[idx]);

  while (p2.phasenumber < 100) 
    p2.permutate2(offset);

  std::cout << "Solution part 1: " << p1.res(0) << std::endl << "Solution part 2: " << p2.res(offset) << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

