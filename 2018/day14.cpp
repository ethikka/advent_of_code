#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

std::vector<int> recipes;
std::vector<int> inp;
int input;
int res2(0);

bool part_b_finished() {
  if (res2 == 0) {
    int size = inp.size();
    int recipesize = recipes.size();
    bool last(true), last_1(true);
    for (int i = 0; i < size; i++) {
      last &= (recipes[recipesize-i-1] == inp[size-i-1]);
      last_1 &= (recipes[recipesize-i-2] == inp[size-i-1]);
      if (!last && !last_1) return false;
    }

    if (last && res2 == 0) res2 = recipesize-size;
    if (last_1 && res2 == 0) res2 = recipesize-size-1;
    //return res2 > 0;
  }
  return res2 > 0;
}

void solve() {
  std::cin >> input;
  int tmp = input;
  while (input) {
    inp.insert(inp.begin(), input % 10);
    input /= 10;
  }

  recipes.push_back(3);
  recipes.push_back(7);
  int elf_index_1(0), elf_index_2(1);
  while(!part_b_finished()) {
    int newrecipe = recipes[elf_index_1]+recipes[elf_index_2];
    if (newrecipe > 9) recipes.push_back(1);
    recipes.push_back(newrecipe % 10);
    elf_index_1 = (elf_index_1+1+recipes[elf_index_1]) % recipes.size();
    elf_index_2 = (elf_index_2+1+recipes[elf_index_2]) % recipes.size();
  }

  std::string res1;
  for (int i = 0; i < 10; i++)
    res1 += std::to_string(recipes[tmp+i]);

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

