#include <sstream>
#include <set>
#include <algorithm>
#include "../common/lib.h"

int places(std::string spot) {
  if (spot == "AlphaCentauri") return 0;
  else if (spot == "Snowdin") return 1;
  else if (spot == "Tambi") return 2;
  else if (spot == "Faerun") return 3;
  else if (spot == "Norrath") return 4;
  else if (spot == "Straylight") return 5;
  else if (spot == "Tristram") return 6;
  else if (spot == "Arbre") return 7;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res { 999999999, 0 };
  int64_t distances[8][8];
  std::string from, discard, to;
  int64_t distance;
  while (std::cin >> from >> discard >> to >> discard >> distance) {
    distances[places(from)][places(to)] = distance;
    distances[places(to)][places(from)] = distance;
  }

  int a[] = {0, 1, 2, 3, 4, 5, 6, 7};
  do {
    int64_t last(-1), dist(0);
    for (auto e: a) {
      if (last != -1) 
        dist += distances[last][e];
      last = e;
    }
    if (res.first > dist) res.first = dist;
    if (res.second < dist) res.second = dist;
  } while (std::next_permutation(a, a+8));
  return res;
}

//AlphaCentauri to Snowdin = 66



