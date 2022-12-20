#include <sstream>
#include <vector>
#include "../common/lib.h"
#include "../common/circularlist.h"

struct mixnumber {
  mixnumber(int64_t _n) { number = _n; };
  int64_t number;
  mixnumber* next;
  mixnumber* prev;
};

int64_t mix(int number_of_mixes, tbb::circularlist<mixnumber*> numbers) {
  for (int i = 0; i < number_of_mixes; i++) {
    mixnumber* m = numbers.front_and_next();
    if (m->number != 0) {
      m->prev->next = m->next; m->next->prev = m->prev;
      int64_t offset = std::abs(m->number) % (numbers.size()-1);
      mixnumber *np, *nn;
      np = m->prev; nn = m->next;
      if (m->number > 0) {
        for (int move = 1; move <= offset; ++move) nn = nn->next;
        np = nn->prev;
      } else {
        for (int move = 1; move <= offset; ++move) np = np->prev;
        nn = np->next;
      }
      np->next = m; nn->prev = m; m->next = nn; m->prev = np;
    }
  }

  mixnumber *tmpn = numbers.front();
  while (tmpn->number != 0) tmpn = tmpn->next;
  std::uintmax_t res;
  for(int i = 0; i < 3001; ++i) {
    if (i == 1000 || i == 2000) res += tmpn->number;
    if (i == 3000) { res += tmpn->number; return res; }
    tmpn = tmpn->next;
  }
  return res;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  tbb::circularlist<mixnumber*> numbers, numbers_b;
  int n;
  mixnumber *fr;
  while (std::cin >> n) { numbers.enqueue(new mixnumber(n)); numbers_b.enqueue(new mixnumber(n*811589153));}
  for (int i = 0; i < numbers.size(); i++) { mixnumber* m = numbers.front_and_next(); mixnumber* n = numbers.front(); n->prev = m; m->next = n; }
  for (int i = 0; i < numbers_b.size(); i++) { mixnumber* m = numbers_b.front_and_next(); mixnumber* n = numbers_b.front(); n->prev = m; m->next = n; }
  fr = numbers.front();
  return {mix(numbers.size(), numbers), mix(10*numbers_b.size(), numbers_b)};
}