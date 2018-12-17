#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <queue>

using span = std::array<int, 2>;

struct dripper {
  int y;
  int x;
};

std::map<int,std::map<int,char>> grid;

bool grid_value(int x, int y, std::string c) {
  if (grid[y].count(x) == 0)
    return false;
  bool contains = false;
  for(char a: c)
    contains |= (c.find(grid[y][x]) != std::string::npos);
  return contains;
}

span find_walls(int x, int y) {
  int left(x);
  while (!grid_value(left, y, "#") && (left > 0)) {
    if (!grid_value(left, y+1, "#~"))
      left *= -1;
    else
      left--; 
  }
  int right(x);
  while (!grid_value(right, y, "#") && (right > 0)) {
    if (!grid_value(right, y+1, "#~"))
      right *= -1;
    else
      right++; 
  }
  return {left, right};
}

void solve() {
  std::string line;
  int res1(0), res2(0);
  int mix(500), max(500), miy(10), may(10);

  grid[0][500] = 'o';
  while (std::getline(std::cin, line)) {
    int l_c(0), r_cs(0), r_ce(0);
    char l, r;
    sscanf(line.c_str(), "%c=%d, %c=%d..%d", &l, &l_c, &r, &r_cs, &r_ce);

    switch(l) {
      case 'x': {
        if (miy > r_cs) miy = r_cs;
        if (may < r_ce) may = r_ce;
        if (mix > l_c) mix = l_c-1;
        if (max < l_c) max = l_c+1;
        for(int y = r_cs; y <= r_ce; y++)
          grid[y][l_c] = '#';
        break;
      }
      case 'y': 
        if (mix > r_cs) mix = r_cs-1;
        if (max < r_ce) max = r_ce+1;
        if (miy > l_c) miy = l_c;
        if (may < l_c) may = l_c;
        for(int x = r_cs; x <= r_ce; x++)
          grid[l_c][x] = '#';
        break;
    }
  }

  std::queue<dripper> faucet;
  faucet.push({0, 500});
  while(!faucet.empty()) {
    dripper p = faucet.front();
    int low = p.y;
    while (!grid_value(p.x, low+1, "#~") && (low <= may)) {
      grid[low+1][p.x] = '|';
      low++;
    }

    if (low < may) {
      auto walls = find_walls(p.x, low);
      while ((walls[0] > 0) && (walls[1] > 0)) {
        for(int xx = walls[0]+1; xx < walls[1]; xx++)
          grid[low][xx] = '~';
        walls = find_walls(p.x, --low);
      }
      int xfrom = (walls[0] < 0) ? abs(walls[0]): walls[0]+1;
      int xto = (walls[1] < 0) ? abs(walls[1]): walls[1]-1;
      for (int xx = xfrom; xx <= xto; xx++)
        grid[low][xx] = '|';

      if (walls[0] < 0 && !grid_value(abs(walls[0]), low+1, "|~")) {
        faucet.push({low, -1*walls[0]});
      }
      if (walls[1] < 0 && !grid_value(abs(walls[1]), low+1, "|~")) {
        faucet.push({low, -1*walls[1]});
      }
    }
    faucet.pop();
  };

  for (int yy = miy; yy <= may; yy++) {
    for (int xx = mix; xx <= max; xx++) {
      if (grid_value(xx, yy, "~|")) res1++;
      if (grid_value(xx, yy, "~")) res2++;

//        std::cout << ((grid[yy].count(xx) > 0) ? grid[yy][xx] : '.');
    }
//    std::cout << std::endl;
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

