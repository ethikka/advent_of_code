#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <chrono>

typedef std::pair<int,int> point;
struct work {
  point pos;
  int stepcount;
  int level;
  bool teleported;
};

std::vector<std::string> donutmaze;

bool is_wormhole(int x, int y) {
  if (x < 0 || x >= donutmaze[y].size() || y < 0 || y >= donutmaze.size()) return false;
  return ((donutmaze[y][x] >= 'A') && (donutmaze[y][x] <= 'Z'));
}

bool check(int x, int y, char c) {
  if (x < 0 || x >= donutmaze[y].size() || y < 0 || y >= donutmaze.size()) return false;
  return (donutmaze[y][x] == c);
}

bool outerportal(int x, int y) {
  return (x <= 2 || x >= (donutmaze[y].size()-5) || y <= 2 || y >= (donutmaze.size()-5));
}

void solve() {
  int res1(0), res2(0);
  std::map<std::string,std::vector<point>> wormholes;
  std::map<point,point> wh;
  std::vector<point> offsets= { {-1,0}, {1,0}, {0,-1}, {0,1}};

  std::string line;
  while (std::getline(std::cin, line)) donutmaze.push_back(line);

  for(int y = 0; y < donutmaze.size()-1; y++) 
    for (int x = 0; x < donutmaze[y].size()-1; x++) 
      if (is_wormhole(x, y)) {
        if      (is_wormhole(x+1, y)) wormholes[{donutmaze[y][x], donutmaze[y][x+1]}].push_back({   (check(x+2,y,'.') ? x+2 : x-1), y});
        else if (is_wormhole(x, y+1)) wormholes[{donutmaze[y][x], donutmaze[y+1][x]}].push_back({x, (check(x,y+2,'.') ? y+2 : y-1)   });
      }

  for(auto w: wormholes) 
    if (w.second.size() == 2) {
      wh[w.second.at(0)] = w.second.at(1);
      wh[w.second.at(1)] = w.second.at(0);
    }

  /* Part A */
  std::queue<work> q;
  std::map<point,int> visited;
  q.push({wormholes["AA"][0], 0});
  visited[wormholes["AA"][0]] = 999;
  while (!q.empty()) {
    auto wk = q.front();
    q.pop();
    if (visited.count(wk.pos) == 0 || visited[wk.pos] > wk.stepcount) {
      visited[wk.pos] = wk.stepcount;
      for(point p : offsets) {
        point newpos = { wk.pos.first+p.first, wk.pos.second+p.second };
        if (check(newpos.first, newpos.second, '.')) { q.push({newpos, wk.stepcount+1}); }
        else if (wh.count(wk.pos) > 0)               { q.push({wh[wk.pos], wk.stepcount+1}); }
      }
    }
  }
  res1 = visited[wormholes["ZZ"][0]];

  /* Part B */
  std::map<int,std::map<point,int>> vis_b;

  q.push({wormholes["AA"][0], 0});
  vis_b[0][wormholes["AA"][0]] = 999;
  while (!q.empty()) {
    auto wk = q.front();
    if (vis_b[0].count(wormholes["ZZ"][0]) > 0) break;

    q.pop();
    if (vis_b[wk.level].count(wk.pos) == 0 || vis_b[wk.level][wk.pos] > wk.stepcount) {
      vis_b[wk.level][wk.pos] = wk.stepcount;

      if (wh.count(wk.pos) > 0 && !wk.teleported) {
        if (outerportal(wk.pos.first, wk.pos.second)) {
          if (wk.level > 0) {
            q.push({wh[wk.pos], wk.stepcount+1, wk.level-1, true}); 
          }
        }
        else {
          q.push({wh[wk.pos], wk.stepcount+1, wk.level+1, true});
        }
      } else {
        for(point p : offsets) {
          point newpos = { wk.pos.first+p.first, wk.pos.second+p.second };

          if ((wk.level == 0) && wk.pos == wormholes["ZZ"][0]) break;
          if (check(newpos.first, newpos.second, '.')) { q.push({newpos, wk.stepcount+1, wk.level, false}); }
        }
      }
    }
  }
  res2 = vis_b[0][wormholes["ZZ"][0]];

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

