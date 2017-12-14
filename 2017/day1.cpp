#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

void solve(void) {
  std::string str;
  getline( std::cin, str);
  int resulta = 0;
  int resultb = 0;
  for(std::string::size_type i = 0; i < str.size(); ++i) {
    if (str[i] == str[(i+1)%str.size()])
      resulta += (int)(str[i] - '0');
    if (str[i] == str[(i+(str.size()/2))%str.size()])
      resultb += (int)(str[i] - '0');
  }
  std::cout << "Result part 1: " << resulta << std::endl << "Result part 2: " << resultb << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

