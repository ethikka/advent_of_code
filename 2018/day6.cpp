#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <queue>
#include <set>
#include <map>

struct point {
  int x;
  int y;
};

struct gridpoint {
  bool isInf;
  int index;
};

void solve() {
  std::vector<point> hotspots;
  std::string line;
  int res1(0), res2(0);
  std::string _x, _y;
  while (std::cin >> _x >> _y) hotspots.push_back({stoi(_x.substr(0, _x.length()-1)), stoi(_y)});

  // Part 1 (not working YET!)
  std::map<int, gridpoint> grid;
  int xmin(99999), xmax(-99999), ymin(99999), ymax(-99999);
  for(auto p: hotspots) {  
    if (p.x < xmin) xmin = p.x;
    if (p.x > xmax) xmax = p.x;
    if (p.y < ymin) ymin = p.y;
    if (p.y > ymax) ymax = p.y;
  }

  for (int x(xmin-1); x <= xmax; x++)
    for (int y(ymin-1); y <= ymax; y++) {
      int lowestMD(100000);
      int idx(-1);
      for(int pos(0); pos < hotspots.size(); pos++) {
        int MD = abs(hotspots[pos].x-x)+abs(hotspots[pos].y-y);
        if (MD < lowestMD) {
          lowestMD = MD; 
          idx = pos;
        }
        if (MD == lowestMD) idx = -1;
      }
      gridpoint gp;
      gp.isInf = ((x == xmin || x == xmax || y == ymin || y == ymax));
      gp.index = idx;
      grid.emplace((x*10000)+y, gp);
    }

  int largest(0);
  for(int pos(0); pos < hotspots.size(); pos++) {
    int total(0);
    for(auto g: grid) {
      if (g.second.index == pos)
        total++;

      int x = (int)(g.first / 10000);
      int y = (int)(g.first % 10000);
      if (x == xmin || x == xmax || y == ymin || y == ymax)
        total -= 1000000000;
    }
    if (total > largest)
      largest = total;
  }

  // Part 2
  int totalx(0), totaly(0);
  for(auto p: hotspots) { totalx += p.x; totaly += p.y; }

  std::queue<point> work;
  std::set<int> visitedspots;
  work.push({(int)(totalx / hotspots.size()), (int)(totaly / hotspots.size())});
  int area(0);
  while(!work.empty()) {
    point p = work.front();
    visitedspots.emplace(p.x*10000000+p.y);
    int totalMD(0);
    for(auto pp: hotspots)
      totalMD += abs(pp.x - p.x) + abs(pp.y - p.y);
    if (totalMD < 10000) {
      area++;
      for (int xo : {-1, 0, 1})
        for (int yo : {-1, 0, 1}) 
          if (visitedspots.count(((p.x+xo)*10000000)+(p.y+yo)) <= 0) {
            work.push({p.x+xo, p.y+yo});
            visitedspots.emplace((p.x+xo)*10000000+p.y+yo);
          }
    }
    work.pop();
  }
  // Part 1: 5429  Part 2: 32614 
  std::cout << "Solution part 1: " << largest << std::endl << "Solution part 2: " << area << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

