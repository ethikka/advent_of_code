#include <sstream>
#include <cmath>
#include <set>
#include "../common/lib.h"

std::pair<int,int> solve() {
  std::pair<int,int> res; 
  char inp;
  int row_up(127), row_low(0), seat_up(7), seat_low(0), max_seat_id(0);
  std::set<int> seats;
  while (std::cin >> std::noskipws >> inp) {
    switch (inp) {
      case 'F': row_up  = row_up  - ((row_up - row_low + 1)/2); break;
      case 'B': row_low = row_low + ((row_up - row_low + 1)/2); break;
      case 'L': seat_up  = seat_up  - ((seat_up - seat_low + 1)/2);break;
      case 'R': seat_low = seat_low + ((seat_up - seat_low + 1)/2);break;
      case '\n': 
        int seat_id = (row_up*8)+seat_up;
        max_seat_id = std::max(max_seat_id, seat_id);
        seats.insert(seat_id);
        row_up = 127; row_low = 0; seat_up = 7; seat_low = 0;
        break;
    }
  }

  int last(0);
  for(auto i: seats) {
    if (++last != i)
      res.second = last;
    last = i;
  }

  res.first = max_seat_id;
  return res;
}

int main(void) {
  post_solve(solve());
}
