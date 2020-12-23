#include <sstream>
#include <vector>
#include "../common/lib.h"

std::vector<int> input {3,6,4,2,9,7,5,8,1};

int64_t solver(int cycles, int size_count = 0, bool part_a = true) {
  std::vector<int> cuplist;
  int max = (size_count == 0 ? input.size() : size_count);
  cuplist.resize(max);
  for (int i = 0; i < input.size() - 1; i++) cuplist[input[i]-1] = input[i+1] - 1;
  for (int i = input.size(); i < max; i++) cuplist[i] = i+1;

  int current_cup = input[0]-1;
  if(size_count == 0) 
    cuplist[input.back()-1] = current_cup;
  else {
    cuplist[input.back()-1] = input.size();
    cuplist.back() = current_cup;
  }

  int move_start(0), forbidden(0), move_end(0);
  for(int i = 0; i < cycles; i++) {
    move_start = cuplist[current_cup];
    forbidden = cuplist[move_start];
    move_end = cuplist[forbidden];

    cuplist[current_cup] = cuplist[move_end];

    auto destination = current_cup;
    do {
      destination--;
      if (destination < 0)
        destination = max-1;
    } while (destination == move_start || destination == forbidden || destination == move_end);

    cuplist[move_end] = cuplist[destination];
    cuplist[destination] = move_start;
    current_cup = cuplist[current_cup];
  }

  if (part_a) {
    auto cur_cup = cuplist[0];
    std::string ret{};
    for (int i = 1; i < cuplist.size(); i++ ) {
      ret += std::to_string(cur_cup+1);
      cur_cup = cuplist[cur_cup];
    }
    return std::stoull(ret);
  } else {
    return (cuplist[0]+1)*(cuplist[cuplist[0]]+1);
  }
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  res.first = solver(100);
  res.second = solver(10000000, 1000000, false);
  return res;
}