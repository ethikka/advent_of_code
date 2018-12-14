#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

std::vector<int> recipes;
int input;
int res2(0);

bool part_a_finished() {
  return recipes.size() >= input+10;
}

bool part_b_finished() {
  if (res2 > 0) return true;
  int lastres(0), lastres2(0);
  for (int i = 1, mul = 1; i <= std::to_string(input).size(); i++, mul *= 10) {
    lastres += (recipes[recipes.size()-(1*i)]*mul);
    lastres2 += (recipes[recipes.size()-(1*(i+1))]*mul);
  }

  if (lastres == input && res2 == 0) res2 = recipes.size()-std::to_string(input).size();
  if (lastres2 == input && res2 == 0) res2 = recipes.size()-std::to_string(input).size()-1;
  return lastres == input;
}

void solve() {
  std::cin >> input;
  recipes.push_back(3);
  recipes.push_back(7);
  int elf_index_1(0), elf_index_2(1);
  while(!part_b_finished() || !part_a_finished()) {
    int newrecipe = recipes[elf_index_1]+recipes[elf_index_2];
    if (newrecipe > 9)
      recipes.push_back(newrecipe/10);
    recipes.push_back(newrecipe%10);
    elf_index_1 = (elf_index_1+1+recipes[elf_index_1]) % recipes.size();
    elf_index_2 = (elf_index_2+1+recipes[elf_index_2]) % recipes.size();
  }

  std::string res1;
  for (int i = 0; i < 10; i++)
    res1 += std::to_string(recipes[input+i]);

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

