#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

struct point {
  int index;
  int val;
  int posx;
  int posy;
};

bool exceeded_max = false;
int max = 0;

void addPoint(std::vector<point>& mem, int index, int x, int y) {
  int val = 0;
  if (!exceeded_max) {
    for (auto &item : mem) {
      if ((abs(item.posx - x) <= 1) && (abs(item.posy - y) <= 1))
        val += item.val;
    }
    exceeded_max |= (val > max);
  }
  mem.push_back({index, val, x, y});
}

void generateCircularMem(std::vector<point>& mem) {
  addPoint(mem, 1, 0, 0);
  mem[0].val = 1;
  int maxring = 3;
  int currentindex = 2;
  while (currentindex < max) {
    int offset = ((maxring - 1) / 2);
    for (int right = 1; right <= maxring - 1; right++) {
      addPoint(mem, currentindex, right+(offset*-1), offset);
      currentindex++;
    }
    for (int top = 1; top <= maxring - 1; top++) {
      addPoint(mem, currentindex, offset, offset+(top*-1));
      currentindex++;
    }
    for (int left = 1; left <= maxring - 1; left++) {
      addPoint(mem, currentindex, (left * -1) + offset, (offset * -1));
      currentindex++;
    }
    for (int bottom = 1; bottom <= maxring - 1; bottom++) {
      addPoint(mem, currentindex, offset * -1, bottom - offset);
      currentindex++;
    }
    maxring += 2;
  }
}

void solve(void) {
  std::cin >> max;
  std::vector<point> circularmem;
  generateCircularMem(circularmem);
  int manhattan = 0;
  int biggerval = 0;
  for (auto &item: circularmem) {
    if (biggerval == 0 && item.val > max)
      biggerval = item.val;
    if (manhattan == 0 && item.index == max)
      manhattan = abs(item.posx)+abs(item.posy);
  }
  std::cout << "Index " << max << " has a manhattan distance of " << manhattan << std::endl;
  std::cout << "First value larger then " << max << " is " << biggerval << std::endl;	
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

