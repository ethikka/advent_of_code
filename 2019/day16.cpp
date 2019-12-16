#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>

int basepattern[4] = { 0, 1, 0, -1 };
int offset = 0;

struct phase;

auto timer = std::chrono::high_resolution_clock::now();

/*
  i =   0 1 2 3 4 5 6
---------------------
d=0 [ _ 1 2 3 0 1 2 3 ]
d=1 [ _ 0 1 1 2 2 3 3 ]
d=2 [ _ 0 0 1 1 1 2 2 ]
d=3 [ _ 0 0 0 1 1 1 1 ...]
d=4 [ _ 0 0 0 0 1 1 1 ...]


(i / (d+1)) + 1

*/

int fft(int i, int d) {
  return ((i+1) / (d+1)) % 4;
};

struct phase {
  int phasenumber;
  std::vector<int> signal;

  phase permutate() {
    phase p;
    p.phasenumber = phasenumber+1;
    for(int idx = 0; idx < signal.size(); idx++) {
      int res(0);
      for (int iidx = idx; iidx < signal.size(); iidx++) 
        res += signal[iidx] * basepattern[fft(iidx, idx)];
      p.signal.push_back(abs(res) % 10);
    };
    return p;
  };

  phase permutate2() {
    phase p;
    p.phasenumber = phasenumber+1;
    p.signal.resize(signal.size());
    std::fill (p.signal.begin(),p.signal.end(),0);
    p.signal[signal.size()-1] = signal[signal.size()-1];

    for (int idx = p.signal.size()-2; idx >= offset; idx--) 
      p.signal[idx] = abs(signal[idx]+p.signal[idx + 1]) % 10;
    return p;
  };

  void print(int offset, int size) {
    for(int i = offset; i < offset + size; i++)
      std::cout << signal[i];
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
  int res1(0), res2(0);
  phase p;
  p.phasenumber = 0;

  while (std::cin >> c)  p.signal.push_back((int)c-48);

  phase p1(p);
  while (p1.phasenumber < 100) 
    p1 = p1.permutate();
  res1 = p1.res(offset);

  int multiplier(1000000);
  for (int i = 0; i < 7; i++) {
    offset += p.signal[i]*multiplier;
    multiplier /= 10;
  }

  phase p3(p);
  for (int i = 0; i < 9999; i++)
    for(int idx = 0; idx < p.signal.size(); idx++)
      p3.signal.push_back(p3.signal[idx]);

  while (p3.phasenumber < 100) 
    p3 = p3.permutate2();
  res2 = p3.res(offset);

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

