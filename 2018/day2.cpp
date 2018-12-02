#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

void solve() {
  int res1;
  std::string res2;
  std::string line;
  std::vector<std::string> inputs;
  while (std::getline(std::cin, line)) {
    inputs.push_back(line);
  }

  int num_two(0), num_three(0);
 
  for (auto &inp: inputs) {
    std::string input(inp);
    std::sort(input.begin(), input.end());
    bool two(false), three(false);
    for (int i = 0; i < input.size(); i++) {
      int dups = 1;

      while (i+1 < input.size() && input[i] == input[i+1]) {
        ++dups;
        ++i;
      }
      two = (two || dups == 2);
      three = (three || dups == 3);
    } 
    if (two) num_two++;
    if (three) num_three++;
  }
  res1 = num_two*num_three;
  
  bool found(false);

  for (int i = 0; i < inputs.size(); i++) {
    for (int j = i+1; j < inputs.size(); j++) {
      int diff(0);
      for (int idx = 0; idx < inputs[i].size(); idx++)
      {
        if (inputs[i][idx] != inputs[j][idx])
        {
          diff++;
          if (diff > 1) break;
        }
      }
      if (diff == 1) {
        for (int idx = 0; idx < inputs[i].size(); idx++) {
          if (inputs[i][idx] == inputs[j][idx])
            res2 += inputs[i][idx];
        }
      }
    }
  }



  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

