#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <set>
#include <vector>
#include <cmath>

struct point {
  int x;
  int y;
};

void solve() {
  char ch;
  int pos(0);
  int res1(0), res2(99999999);

  std::map<int,point> asteroids;
  while (std::cin >> ch) {
    if (ch == '#') 
      asteroids[asteroids.size()] = {pos / 24, pos % 24};
    pos++;
  }

  std::vector<int> keys;
  for (auto entry : asteroids) {
    keys.push_back(entry.first);
  }

  std::map<float, std::map<int,point>> bestdirections;

  for (auto a: asteroids) {
    std::map<float, std::map<int,point>> dirs;
    for (auto t: asteroids) 
      if (keys[a.first] != keys[t.first])
        dirs[fmod(std::atan2((t.second.y - a.second.y),(t.second.x - a.second.x))*180/M_PI+270, 360)][std::abs(t.second.x - a.second.x)+std::abs(t.second.x - a.second.x)] = t.second;
    int d = dirs.size();
    if (d > res1)
      bestdirections = dirs;
    res1 = std::max(res1, d);
  }

  float cld = bestdirections.lower_bound(90.0f)->first;
  int destructioncnt(0);
  while (destructioncnt <= 200) {
    if (bestdirections[cld].size() > 0) {
      if (destructioncnt == 199) {
        for (auto p: bestdirections[cld]) 
          res2 = std::min(res2, (p.second.y*100)+p.second.x);
      } else 
        bestdirections[cld].erase(bestdirections[cld].begin());
      destructioncnt++;
      std::cout << std::endl;
    }
    // volgende element in de map
    auto it = bestdirections.find(cld);
    if (it == bestdirections.begin())
      cld = bestdirections.rbegin()->first;
    else
      cld = std::next(it, -1)->first;
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
