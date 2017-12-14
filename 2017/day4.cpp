#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <set>
#include <algorithm>
#include <chrono>

bool comp(char c1, char c2) {
  return c1 < c2;
}

void solve(void) {
  int res = 0;
  int res_b = 0;
  std::string passphrase;
  while (std::getline(std::cin, passphrase)) {
    std::istringstream words(passphrase);
    std::istream_iterator<std::string> begin(words), end;
    std::vector<std::string> words2(begin, end);
    std::set<std::string> tokens_partb;
    std::set<std::string> tokens;
    bool dup = false;
    bool dup2 = false;
    for (auto &s: words2) {
      if (tokens.count(s)) {
        dup = true;
      } else
        tokens.insert(s);
      std::sort(s.begin(), s.end(), comp);
      if (tokens_partb.count(s)) {
        dup2 = true;
      } else
        tokens_partb.insert(s);

    } 
    if (!dup) res++;
    if (!dup2) res_b++;
  }

  std::cout << "Amount of valid passphrases is " << res << std::endl;
  std::cout << "Amount of anagrammed valid passphrases is " << res_b << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}



