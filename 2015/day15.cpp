#include <sstream>
#include "../common/lib.h"

struct r {
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string d;
  int cap, dur, flv, txt, cal, idx;

  r ingredients[4];
  while (std::cin >> d >> d >> cap >> d >> dur >> d >> flv >> d >> txt >> d >> cal) ingredients[idx++] = {cap, dur, flv, txt, cal};

  for (int i1 = 0;  i1           <= 100; i1++) 
  for (int i2 = 0; (i1+i2)       <= 100; i2++) 
  for (int i3 = 0; (i1+i2+i3)    <= 100; i3++) 
  for (int i4 = 0; (i1+i2+i3+i4) <= 100; i4++) {
    int c(ingredients[0].capacity*i1 + ingredients[1].capacity*i2 + ingredients[2].capacity*i3 + ingredients[3].capacity*i4);
    int d(ingredients[0].durability*i1 + ingredients[1].durability*i2 + ingredients[2].durability*i3 + ingredients[3].durability*i4);
    int f(ingredients[0].flavor*i1 + ingredients[1].flavor*i2 + ingredients[2].flavor*i3 + ingredients[3].flavor*i4);
    int t(ingredients[0].texture*i1 + ingredients[1].texture*i2 + ingredients[2].texture*i3 + ingredients[3].texture*i4);
    int cal(ingredients[0].calories*i1 + ingredients[1].calories*i2 + ingredients[2].calories*i3 + ingredients[3].calories*i4);
    if (c > 0 && d > 0 && f > 0 && t > 0) {
      int score = c*d*f*t;
      if (res.first < score) res.first = score;
      if (cal == 500)
      if (res.second < score) res.second = score;
    }
  }
  return res;
}