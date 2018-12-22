#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <queue>

int erosion_level_divider(20183);
int geo_index_x(48271);
int geo_index_y(16807);
int depth(0);
int target_x(0), target_y(0);
int cave_margin(26); // 10 isn't enough
bool print_cave(false);

const std::string LEGENDA = ".=|";
const int directions[4][2] = {{-1, 0}, {0,  -1}, {0,  1}, {1,  0}};  // N, W, E, S

struct spelunking_work {
  int x;
  int y;
  int current_time;
  int tool;
  // need a < operator for priority_queue, returning the inverse so it prioritizes shorter paths
  bool operator <(const spelunking_work &compare_to) const { return current_time > compare_to.current_time; }
};


void solve() {
  std::string line;
  std::getline(std::cin, line);
  sscanf(line.c_str(), "depth: %d", &depth);
  std::getline(std::cin, line);
  sscanf(line.c_str(), "target: %d,%d", &target_x, &target_y);

  // test input
  //depth = 510; target_x = 10; target_y = 10;

  int64_t geo_map[target_y+1+cave_margin][target_x+1+cave_margin];
  int cave[target_y+1+cave_margin][target_x+1+cave_margin];

  int risk_index(0);
  for(int y = 0; y <= target_y+cave_margin; y++) {
    for(int x = 0; x <= target_x+cave_margin; x++) {
      if (x == 0 && y == 0)                    geo_map[y][x] = depth % erosion_level_divider;
      else if (x == target_x && y == target_y) geo_map[y][x] = depth % erosion_level_divider;
      else if (x == 0)                         geo_map[y][x] = ((y * geo_index_x)+depth) % erosion_level_divider;
      else if (y == 0)                         geo_map[y][x] = ((x * geo_index_y)+depth) % erosion_level_divider;
      else                                     geo_map[y][x] = ((geo_map[y-1][x]*geo_map[y][x-1])+depth) % erosion_level_divider;

      cave[y][x] = geo_map[y][x]%3;
      if (y <= target_y && x <= target_x) risk_index += cave[y][x];
      if (print_cave) {
        if (x == 0 && y == 0)                    std::cout << "M";
        else if (x == target_x && y == target_y) std::cout << "T";
        else                                     std::cout << LEGENDA[cave[y][x]];
      }
    }
    if (print_cave) std::cout << std::endl;
  }

  // part 2

  // N = 0, T = 1, C = 2 so I can check if cave[y][x] is the same as tool then we should switch
  std::priority_queue<spelunking_work> expedition;
  int visited[3][target_y+1+cave_margin][target_x+1+cave_margin];

  for(int y = 0; y <= target_y+cave_margin; y++) 
    for(int x = 0; x <= target_x+cave_margin; x++) 
      for (auto t: {0,1,2}) {
      visited[t][y][x] = 999999;
    }
  visited[1][0][0] = 0;

  expedition.push({0,0,0,1});
  while (!expedition.empty()) {
    spelunking_work w = expedition.top();
    expedition.pop();
    if (w.current_time > visited[w.tool][w.y][w.x]) continue;

    for (int newtool: {0,1,2}) {
      int newtime = w.current_time + 7;
      if (newtool != w.tool) 
        if (visited[newtool][w.y][w.x] > newtime) {
          visited[newtool][w.y][w.x] = newtime;
          expedition.push({w.x, w.y, newtime, newtool});
        }
    }

    for (auto d : directions) {
      int nx = w.x + d[0], ny = w.y + d[1];
      if (nx < 0 || ny < 0 || nx >= target_x+cave_margin || ny >= target_y+cave_margin) continue;

      for (int newtool: {0,1,2}) {
        if (newtool == cave[ny][nx] || newtool == cave[w.y][w.x]) continue;
          int newtime = w.current_time + 1 + (newtool == w.tool ? 0 : 7);
          if (visited[newtool][ny][nx] > newtime) {
              visited[newtool][ny][nx] = newtime;
              expedition.push({nx, ny, newtime, newtool});
          }
        }
    }
  };
  
  std::cout << "Solution part 1: " << risk_index << std::endl << "Solution part 2: " << visited[1][target_y][target_x] << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

