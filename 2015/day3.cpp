#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <chrono>

void solve(void) {
  std::vector<char> input { std::istream_iterator<char>{ std::cin }, {}};
  int x = 0, y = 0, rx = 0, ry = 0;
  bool realsanta = true;
  std::map<std::pair<int,int>, int> roadmap;
  roadmap[std::make_pair(0 , 0)] = 1;
  for(auto& i: input) {
    if      (i == '^') realsanta ? x++ : rx++;
    else if (i == 'v') realsanta ? x-- : rx--;
    else if (i == '<') realsanta ? y-- : ry--;
    else if (i == '>') realsanta ? y++ : ry++;

    auto k = realsanta ? std::make_pair(x, y) : std::make_pair(rx, ry);
    if (roadmap.find(k) == roadmap.end()) 
      roadmap[k] = 0;
    roadmap[k]++;
    realsanta = !realsanta;
  }
  std::cout << "Santa (and RoboSanta =) delivered presents to  " << roadmap.size() << " houses" << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

