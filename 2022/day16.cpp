#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include "../common/lib.h"

struct valve {
  int index;
  std::string name;
  int64_t flowrate;
  std::vector<std::string> points_to;
};

struct pw {
  pw(std::string _cv, int64_t _steps) { cv = _cv; steps = _steps; }
  std::string cv;
  int64_t steps;
};

std::map<int,std::map<int,int64_t>> memo;

std::istream &operator>>(std::istream &is, valve &v)
{
  std::string in;
  is >> in >> v.name >> in >> in >> in;
  v.flowrate = std::stoi(in.substr(5, in.size()-6));
  is >> in >> in >> in >> in;
  while (!is.eof()) {
    is >> in;
    if (in[in.size()-1] != ',') { v.points_to.push_back(in); return is; }
    else                          v.points_to.push_back(in.substr(0, in.size()-1));
  }
  return is;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::map<std::string,valve> valves;
  std::map<int,valve> valves_by_index;
  std::vector<int> valves_with_flowrate;
  while (!std::cin.eof()) {
    valve t;
    t.index = valves.size()+1;
    std::cin >> t;
    valves[t.name] = t;
    valves_by_index[t.index] = t;
    if (t.flowrate > 0) valves_with_flowrate.push_back(t.index);
  }

  int paths[valves.size()+1][valves.size()+1];
  for (int i = 0; i <= valves.size(); i++) for (int j = 0; j <= valves.size(); j++) paths[i][j] = -1;

  // create most efficient path map
  for (auto v: valves) {
    std::queue<pw> q;
    paths[v.second.index][v.second.index] = 0;
    q.push({ v.second.name, 0 });
    while (!q.empty()) {
      auto w = q.front();
      q.pop();
      for (auto p: valves[w.cv].points_to) 
        if (paths[v.second.index][valves[p].index] == -1 || paths[v.second.index][valves[p].index] > w.steps) {
          paths[v.second.index][valves[p].index] = paths[valves[p].index][v.second.index] = w.steps+1;
          q.push({p, w.steps+1});
        }
    }
  }

  do {
    int64_t pressure(0), minutes_left(30), cv(valves["AA"].index);
    for(auto i: valves_with_flowrate) {
      std::cout << "----------------------------" << std::endl;
      minutes_left -= (paths[cv][i]+1);
      if (minutes_left < 0) break;
      memo[i][minutes_left] = minutes_left*valves_by_index[i].flowrate;
      pressure += memo[i][minutes_left];
      cv = i;
      std::cout << valves_by_index[i].name << " +> " << pressure << " " << minutes_left << std::endl;
    }
    if (res.first == 0 || res.first < pressure) {
      res.first = pressure;
      std::cout << res.first << std::endl;

    }
  } while ( std::next_permutation(valves_with_flowrate.begin(), valves_with_flowrate.end()));
  return res;
}

//1552 too low