#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <stack>

std::map<int,std::map<int,int>> rooms;
std::stack<std::pair<int,int>> branchpoints;

void solve() {
  char input;
  int x(0), y(0);
  int current_route(0), longest_route(0);

  while (std::cin >> input) {
    if (rooms[y][x] < current_route && rooms[y][x] != 0)
      current_route = rooms[y][x];
    rooms[y][x] = current_route;
    switch (input) {
      case 'N': --y; current_route++;      break;
      case 'E': ++x; current_route++;      break;
      case 'S': ++y; current_route++;      break;
      case 'W': --x; current_route++;      break;
      case '(': branchpoints.push({x, y}); break;
      case ')': {
                auto p = branchpoints.top();  
                x = p.first; 
                y = p.second;
                branchpoints.pop();
                break; 
              }
      case '|': {
                auto p = branchpoints.top();  
                x = p.first; 
                y = p.second;
                break; 
              }
    }
    if (current_route > longest_route) longest_route = current_route;
  }
  int res2(0);

  for(auto y: rooms) 
    for (auto x: y.second) 
      if (x.second >= 1000)
        res2++;
  std::cout << "Solution part 1: " << longest_route << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

