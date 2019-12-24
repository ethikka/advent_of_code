#include <sstream>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
#include <chrono>

int offsets[4] = {-1, 1, -5, 5};

int count_adjecant_indeces(std::map<int,std::bitset<25>> state, std::vector<std::pair<int,int>> c) {
  int res(0);
  for(auto p: c) {
    res += (state[p.first][p.second]) ? 1 : 0;
  }
  return res;
}

std::vector<std::pair<int,int>> generate_pairs(int index, int level) {
  std::vector<std::pair<int,int>> res;
  if (index != 12){
    for (auto o: offsets)
      if (index+o >= 0 && index+o < 25 && index+o != 12 && (abs((index % 5) - ((index+o) % 5)) < 2))
        res.push_back(std::make_pair(level, index+o));
   
    if (index >= 0  && index < 5) res.push_back(std::make_pair(level-1, 7));
    if (index >= 20 && index < 25) res.push_back(std::make_pair(level-1, 17));
    if ((index % 5) == 0) res.push_back(std::make_pair(level-1, 11));
    if (((index+1) % 5) == 0) res.push_back(std::make_pair(level-1, 13));

    if (index ==  7) for (int xx = 0; xx < 5; xx++)   res.push_back(std::make_pair(level+1, xx));
    if (index == 17) for (int xx = 20; xx < 25; xx++) res.push_back(std::make_pair(level+1, xx));
    if (index == 11) for (int xx = 0; xx < 5; xx++)   res.push_back(std::make_pair(level+1, xx*5));
    if (index == 13) for (int xx = 1; xx < 6; xx++)   res.push_back(std::make_pair(level+1, (xx*5)-1));
  }
  return res;
}

int count_adjecant(std::bitset<25> state, int index) {
  int res(0);
  for (auto o: offsets) 
    if (index+o >= 0 && index+o < state.size() && (abs((index % 5) - ((index+o) % 5)) < 3)) 
      res += (state[index+o] ? 1 : 0);
  return res;
}

void solve() {
  std::bitset<25> state, initialstate;
  std::set<int64_t> memo;

  char inp;
  int count(0);
  int res1(0), res2(0);
  while (std::cin >> inp) 
    if (inp != 10)
      initialstate[count++] = (inp == '#');
  state = initialstate;

  while(memo.count(state.to_ullong()) == 0) {
    std::bitset<25> newstate;
    for (int i = 0; i < 25; i++) {
      int adj = count_adjecant(state, i);
      if      (state[i] && adj == 1)                newstate[i] = true;
      else if (!state[i] && (adj == 1 || adj == 2)) newstate[i] = true;
      else                                          newstate[i] = false;
    }
    memo.insert(state.to_ullong());
    state = newstate;
  }
  res1 = state.to_ullong();

  int minutes(200), levels(101);
  std::map<int, std::bitset<25>> infstate;
  infstate[0] = initialstate;
  for (int m = 0; m < minutes; m++) {
    std::map<int, std::bitset<25>> newstate;
    for (int l = -1*levels; l <= levels; l++) {
      for (int i = 0; i < 25; i++) {
        int adj = count_adjecant_indeces(infstate, generate_pairs(i, l));
        if      ( infstate[l][i] && (adj == 1))             newstate[l][i] = true;
        else if (!infstate[l][i] && (adj == 1 || adj == 2)) newstate[l][i] = true;
        else                                                newstate[l][i] = false;
      }
    }
    infstate = newstate;
  }

  for (auto s: infstate)
    for (int i = 0; i < 25; i++)
      if (s.second[i]) res2++;

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

