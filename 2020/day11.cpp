#include <sstream>
#include <vector>
#include <tuple>
#include "../common/lib.h"

int seats_x(0), seats_y(0);
char seats_a[128][128];
char seats_b[128][128];

int count_adjecant_a(int x, int y) {
  int res(0);
  for(auto xo: {-1, 0, 1})
    for(auto yo: {-1, 0, 1}) 
      if ((x+xo >= 0) && (x+xo < seats_x)) 
        if ((y+yo >= 0) && (y+yo < seats_y)) 
          if (!((xo == 0) && (yo == 0)))
            if (seats_a[x+xo][y+yo] == '#')
              res++;
  return res;
}

int generation_a() {
  int delta(0);
  char tmpboard[seats_x][seats_y];
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      switch(seats_a[x][y]) {
        case 'L': if (count_adjecant_a(x, y) == 0) tmpboard[x][y] = '#'; break;
        case '#': if (count_adjecant_a(x, y) >= 4) tmpboard[x][y] = 'L'; break;
      }
    
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      if (seats_a[x][y] != tmpboard[x][y] && (tmpboard[x][y] == '#' || tmpboard[x][y] == 'L')) {
        delta++;
        seats_a[x][y] = tmpboard[x][y];
      }
  return delta;
}

int count_adjecant_b(int x, int y) {
  int res(0);
  std::vector<std::tuple<int,int>> vectors({{-1,-1},{-1, 0},{-1, 1},{ 0,-1},{ 0, 1},{ 1,-1},{ 1, 0},{ 1, 1}});
  for(auto i: vectors) {
    int xo = x+std::get<0>(i);
    int yo = y+std::get<1>(i);
    while ((xo >= 0 || xo < seats_x) && (yo >= 0 || yo < seats_y) && seats_b[xo][yo] == '.') {
      xo += std::get<0>(i); 
      yo += std::get<1>(i);
    }
    if (seats_b[xo][yo] == '#') res++;
  }
  return res;
}

int generation_b() {
  int delta(0);
  char tmpboard[seats_x][seats_y];
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      switch(seats_b[x][y]) {
        case 'L': if (count_adjecant_b(x, y) == 0) tmpboard[x][y] = '#'; break;
        case '#': if (count_adjecant_b(x, y) >= 5) tmpboard[x][y] = 'L'; break;
      }
    
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      if (seats_b[x][y] != tmpboard[x][y] && (tmpboard[x][y] == '#' || tmpboard[x][y] == 'L') && seats_b[x][y] != '.') {
        delta++;
        seats_b[x][y] = tmpboard[x][y];
      }
  return delta;
}

void print_b() {
  for (int y = 0; y < seats_y; y++) {
    for(int x = 0; x < seats_x; x++) {
      std::cout << seats_b[x][y];
    }
    std::cout << " " << y << std::endl;
  }
  std::cout << std::endl << std::endl;
}

std::pair<int,int> solve() {
  std::pair<int,int> res; 
  char inp;
  while (std::cin >> std::noskipws >> inp) 
    switch (inp) {
      case '\n': seats_x = 0; seats_y++; break;
      default:   seats_a[seats_x][seats_y] = inp; seats_b[seats_x++][seats_y] = inp;
    }
  seats_y++; // also count last row

  int gen(0);
  while(generation_a() > 0);
  while(generation_b() > 0);

  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) {
      if (seats_a[x][y] == '#') res.first++;
      if (seats_b[x][y] == '#') res.second++;
    }    
  return res;
}

int main(void) {
  post_solve(solve());
}
