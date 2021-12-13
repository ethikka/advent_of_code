#include <iostream>
#include <vector>
#include <iterator>
#include "md5.h"
#include "../common/lib.h"

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  // md5(std::string)
  std::string secret;
  getline(std::cin, secret);
  int num = 0;
  int sol_a = 0;
  std::string res = "hjkhasjkfs";
  while (res.substr(0, 6) != "000000")
  {
    if (res.substr(0,5) == "00000" && sol_a == 0)
      sol_a = num;
    num++;
    res = md5(secret+std::to_string(num));
  }
  return { sol_a, num };
}