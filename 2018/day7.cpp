#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

void solve() {
  std::string line;
  int res1(0), res2(0);
  std::map<char,std::vector<char>> graph;
  std::set<char> available_steps;
  while (std::getline(std::cin, line)) {
    char step = line[36], needs = line[5];

    if (graph.count(step) == 0) {
      std::vector<char> depends_on;
      graph.emplace(step, depends_on);
    }
    graph[step].push_back(needs);
    available_steps.insert(step);
    available_steps.insert(needs);
  }
  // Debug
  /*
  for(auto i: graph) {
    std::cout << char(i.first) << ":";
    if (graph[i.first].size() > 0) 
      for(auto s: i.second)
        std::cout << char(s);
      std::cout << std::endl;
    }
  */

  // Part 1
  std::string order = "";
  std::set<char> done;
  while (order.size() < available_steps.size()) {
    for(auto step: available_steps) {
      if (done.count(step) == 0) {
        bool all_done(true);
        if (graph[step].size() > 0) 
          for(auto s: graph[step])
            all_done &= (done.count(s) > 0);
          if (all_done) {
            order += char(step);
            done.insert(step);
            break;
          }
        }
      }
    }

  // Part 2
  std::unordered_set<char> jobs;
  std::unordered_map<char, bool> done_b;
  int time = 0;

  const int numWorkers = 5;
  const int stepTime = 60;

  char workers[numWorkers];
  int counters[numWorkers];

  for(int i = 0; i < numWorkers; i++) counters[i] = -1;

  while(true) {
    std::vector<char> next;
    bool allCompleted;
    for(char step: available_steps) {
      allCompleted = true;
      for(char r: graph[step]) {
        if(!done_b[r]) { allCompleted = false; break; }
      }
      if(allCompleted && !jobs.count(step)) next.push_back(step);
    }

    std::sort(next.begin(), next.end());

    for(char n: next) {
      for(int i = 0; i < numWorkers; i++) {
        if(counters[i] == -1) {
          workers[i] = n;
          counters[i] = n - 'A' + stepTime + 1;
          jobs.insert(n);
          break;
        }
      }
    }

    if(jobs.empty()) break; 
  
    for(int i = 0; i < numWorkers; i++) {
      if(counters[i] > -1) {
        counters[i]--;
        if(counters[i] == 0) { 
          done_b[workers[i]] = true;
          counters[i] = -1;
          jobs.erase(workers[i]);
          available_steps.erase(workers[i]);
        }
      }
    }
    time++;
  }
  std::cout << "Solution part 1: " << order << std::endl << "Solution part 2: " << time << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

