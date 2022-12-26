#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include "../common/lib.h"

std::vector<int64_t> flowrates;
std::vector<int64_t> memo;
std::vector<std::vector<int64_t>> tunnel_map;

int64_t sim(int64_t current_valve, int64_t valve_bitset, int64_t time, int64_t other_players) {
  if (time == 0) return other_players > 0 ? sim(0,valve_bitset,26,other_players-1) : 0;
  // key = valve_bitset (57 bits)|current_valve_index|time|part_2
  auto key = (valve_bitset*flowrates.size()*62) + (current_valve*62) + (time*2) + (other_players);
  // if the key already exists we can shortcut all the paths and return the value
  if(memo[key]>=0) return memo[key];

  int64_t ans(0);
  if(((valve_bitset & (1LL<<current_valve)) == 0) && flowrates[current_valve]>0) ans = std::max(ans, (time-1)*flowrates[current_valve] + sim(current_valve, (valve_bitset | (1LL<<current_valve)), time-1, other_players));
  for(auto& y : tunnel_map[current_valve]) ans = std::max(ans, sim(y, valve_bitset, time-1, other_players));
  memo[key] = ans;
  return ans;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::map<std::string, std::pair<int64_t, std::vector<std::string>>> valves_info;
  while(!std::cin.eof()) {
    std::string id;
    int64_t rate = 0;
    std::vector<std::string> leads_to;

    std::string in;
    std::cin >> in >> id >> in >> in >> in; 
    rate = std::stoi(in.substr(5, in.size()-6));
    std::cin >> in >> in >> in >> in >> in;
    while (in[in.size()-1] == ',') { leads_to.push_back(in.substr(0, in.size()-1)); std::cin >> in; }
    leads_to.push_back(in);
    valves_info[id] = make_pair(rate, leads_to);
  }

  int64_t n = valves_info.size();
  std::map<std::string, int> valve_index;
  std::vector<std::string> valves_in_order;
  int64_t nonzero(0);

  // mark AA as non zero so we don't skip it in the sim
  for(auto& p : valves_info) if(p.first == "AA")    { nonzero++; valve_index[p.first] = valves_in_order.size(); valves_in_order.push_back(p.first); }
  for(auto& p : valves_info) if(p.second.first > 0) { nonzero++; valve_index[p.first] = valves_in_order.size(); valves_in_order.push_back(p.first); }
  for(auto& p : valves_info) if(valve_index.count(p.first)==0) { valve_index[p.first] = valves_in_order.size(); valves_in_order.push_back(p.first); }

  flowrates = std::vector<int64_t>(n, 0);
  for(int64_t i=0; i<n; i++) flowrates[i] = valves_info[valves_in_order[i]].first;

  tunnel_map = std::vector<std::vector<int64_t>>(n, std::vector<int64_t>{});
  for(int64_t i=0; i<n; i++) for(auto& y : valves_info[valves_in_order[i]].second) tunnel_map[i].push_back(valve_index[y]); 

  memo = std::vector<int64_t>((1L<<nonzero) * n * 62, -1);
  return { sim(0,0,30,false), sim(0,0,26,true) };
}