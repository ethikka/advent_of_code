#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <map>
#include <chrono>

void solve(void) {
  std::vector<std::string> input { std::istream_iterator<std::string> { std::cin }, {}};
  int nice_strings = 0;
  int nicer_strings = 0;
  for(auto& line: input) {
    bool stillnice = true;
    bool doubleletter = false;
    int vowelcount = 0;
    std::string vowels("aeiou");
    if (vowels.find(line[0]) != std::string::npos)
      vowelcount++;
    for (int i = 1; i < line.size() && stillnice; i++) {
      if (line[i-1] == 'a' && line[i] == 'b') stillnice = false;
      if (line[i-1] == 'c' && line[i] == 'd') stillnice = false;
      if (line[i-1] == 'p' && line[i] == 'q') stillnice = false;
      if (line[i-1] == 'x' && line[i] == 'y') stillnice = false;
      if (line[i-1] == line[i]) doubleletter = true;
      if (vowels.find(line[i]) != std::string::npos)
        vowelcount++;
    }
    if (stillnice && (vowelcount >= 3) && doubleletter) {
      nice_strings++;
    }

    // part two!
    std::map<std::string,int> pairs;
    bool repeater = false;
    bool doubler = false;
    for (int i = 0; i < line.size()-1; i++) {
      // pairs opbouwen
      if (!doubler) {
        std::string pair(line.substr(i,2));
        auto pos = pairs.find(pair);
        if (pos == pairs.end())
          pairs[pair] = i;
        else
          if (i - pairs[pair] >= 2)
            doubler = true;
      }
      if (i > 0)
        repeater |= (line[i-1] == line[i+1]);
    }
    if (doubler && repeater)
      nicer_strings++;
  }
  std::cout << "A thick book containing " << nice_strings << " nice strings for nice things" << std::endl;
  std::cout << "And an addendum with extra joy, and also " << nicer_strings << " even nicer strings" << std::endl; 
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

