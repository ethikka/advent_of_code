#include <sstream>
#include <vector>
#include <tuple>
#include "../common/lib.h"

int seats_x(0), seats_y(0);
char seats_a[128][128], seats_b[128][128];

int count_adjecant(char seats[][128], int x, int y, bool line_of_sight) {
  int res(0);
  for(auto i: std::vector<std::tuple<int,int>> {{-1,-1},{-1, 0},{-1, 1},{ 0,-1},{ 0, 1},{ 1,-1},{ 1, 0},{ 1, 1}}) {
    int xo = x+std::get<0>(i);
    int yo = y+std::get<1>(i);
    if (line_of_sight)
      while ((xo >= 0 || xo < seats_x) && (yo >= 0 || yo < seats_y) && seats[xo][yo] == '.') {
        xo += std::get<0>(i); 
        yo += std::get<1>(i);
      } 
    if (seats[xo][yo] == '#') res++;
  }
  return res;
}

bool generation(char seats[][128], int numseats, bool line_of_sight) {
  int delta(0);
  char tmpboard[seats_x][seats_y];
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      switch(seats[x][y]) {
        case 'L': if (count_adjecant(seats, x, y, line_of_sight) == 0) tmpboard[x][y] = '#'; break;
        case '#': if (count_adjecant(seats, x, y, line_of_sight) >= numseats) tmpboard[x][y] = 'L'; break;
      }
    
  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) 
      if (seats[x][y] != tmpboard[x][y] && seats[x][y] != '.') {
        delta++;
        seats[x][y] = tmpboard[x][y];
      }
  return delta > 0;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res; 
 
  char inp;
  while (std::cin >> std::noskipws >> inp) 
    switch (inp) {
      case '\n': seats_x = 0; seats_y++; break;
      default:   seats_b[seats_x++][seats_y] = seats_a[seats_x][seats_y] = inp;
    }
  seats_y++; // also count last row
  while(generation(seats_a, 4, false));
  while(generation(seats_b, 5, true));

  for (int y = 0; y < seats_y; y++) 
    for(int x = 0; x < seats_x; x++) {
      if (seats_a[x][y] == '#') res.first++;
      if (seats_b[x][y] == '#') res.second++;
    }    
  return res;
}