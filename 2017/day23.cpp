#include <iostream>
#include <sstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>

typedef long long ll;

void part_a() {
}

void part_b() {
  ll h = 0;
  ll b = 81;
  ll c = b;
  b *= 100;
  b += 100000;
  c = b;
  c += 17000;
lbl2:
  ll f = 1;
  ll d = 2;

lbl:
  ll e = 2;

  ll g = d;
  if(b % d == 0 && b / d != 1) {
    f = 0;
  }

  d += 1;
  g = d;
  g -= b;
  if(g != 0) {
    goto lbl;
  }
  if(f == 0) {
    h++;
  }
  g = b - c;
  if(g != 0) {
    b += 17;
    goto lbl2;
  }

  std::cout << h << std::endl;
}

void solve() {
  part_a();
  part_b();
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

