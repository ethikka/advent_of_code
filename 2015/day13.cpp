#include <sstream>
#include <algorithm>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string p, gl, n;
  int h(0);

  std::uintmax_t happiness[18][18];
  while (std::cin >> p >> n >> gl >> h >> n >> n >> n >> n >> n >> n >> n) 
    happiness[p[0]-65][n[0]-65] = ((gl == "gain") ? +1 : -1) * h;
  for (int i = 0; i < 13; i++) happiness[17][i] = happiness[i][17] = 0;

  int pa(-9999999), pb(-9999999);
  int a[] = {0, 1, 2, 3, 4, 5, 6, 12, 17}, b[] = {0, 1, 2, 3, 4, 5, 6, 12, 17}; // 17 = yourself, moet na 12 (M) komen voor next_permutation

  do {
    int happ(0);
    for (int idx = 0; idx < 8; idx++) happ += happiness[a[idx]][a[(idx+1)%8]] + happiness[a[(idx+1)%8]][a[idx]];
    if (pa < happ) pa = happ;
  } while (std::next_permutation(a, a+8));
  
  do {
    int happ(0);
    for (int idx = 0; idx < 9; idx++) happ += happiness[b[idx]][b[(idx+1)%9]] + happiness[b[(idx+1)%9]][b[idx]];
    if (pb < happ) pb = happ;
  } while (std::next_permutation(b, b+9));


  return { pa, pb };
}