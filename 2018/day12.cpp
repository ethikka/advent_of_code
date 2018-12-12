#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

std::map<std::string, std::string> rules;
int64_t start_index = -3;

std::string trim_empty_pots(std::string input) {
  int64_t endpos = input.find_last_not_of(".");
  int64_t startpos = input.find_first_not_of(".");
  start_index += startpos;
  return input.substr(startpos, endpos-startpos+1);
}

void solve() {
  int64_t res1(0), res2(0), last_start_index(start_index);
  std::string line;
  std::getline(std::cin, line);
  std::string last_state("..." + line.substr(15, line.size()-16) + "...");

  std::string _predicate, _output, dontcare;
  while (std::cin >> _predicate >> dontcare >>  _output) rules[_predicate] = _output;

  int64_t generations(50000000000);
  for(int64_t i = 0; i < generations; i++) {
    // part 1  
    if (i == 19) {
      int64_t idx_ = start_index;
      for (char c: last_state) {
        res1 += (c == '#') ? idx_ : 0;
        idx_++;
      }
    }
    std::string new_state = "..";
    for (int64_t idx = 2; idx < last_state.size()-1; idx++) 
      new_state += rules[last_state.substr(idx-2, 5)];

    std::string new_state_trimmed = "..." + trim_empty_pots(new_state) + "...";
    last_state.resize(new_state_trimmed.size());
    start_index -= 3; // prepended 3 dots, so the first 'pot' is -3
    
    // Pattern repeats, fastforward to the max generation
    if (last_state == new_state_trimmed) {
      start_index += (generations-i-1);
      i += (generations-i);
    }
    last_state = new_state_trimmed;
  }

  int64_t idx = start_index;
  for (char c: last_state) {
    res2 += (c == '#') ? idx : 0;
    idx++;
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

