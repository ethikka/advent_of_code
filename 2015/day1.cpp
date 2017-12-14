#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <chrono>

void solve(void) {
  std::vector<char> input { std::istream_iterator<char>{ std::cin }, {}};
  int currentfloor = 0;
  int steps = 0, basement = 0;
  for(auto& i: input) {
    if      (i == '(') currentfloor++;
    else if (i == ')') currentfloor--;
    steps++;
    if (currentfloor == -1 && basement == 0)
      basement = steps;
  }
  std::cout << "Santa ends up on floor " << currentfloor << " and stepped foot in the basement at " << basement << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

