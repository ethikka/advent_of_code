#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  res.first = 20151125;
  int row(2981), col(3075), cycles(0);
  for (int i = 1; i <= col; i++) cycles += i;
  for (int c = 1; c < row; c++) cycles += c+col-1;
  for (int i = 1; i < cycles; i++) res.first = (res.first*252533)%33554393;
  return res;
}