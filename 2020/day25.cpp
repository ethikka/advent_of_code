#include <sstream>
#include <map>
#include "../common/lib.h"

int find_loop_counter(int64_t input) {
  int64_t tmp(7), loop(1);
  while (input != tmp && loop++) 
    tmp = (tmp * 7) % 20201227;
  return loop;
}

int64_t transform(int64_t input, int loop) {
  int64_t key(1);
  for(int i = 0; i < loop; i++)  
    key = (key*input)%20201227;
  return key;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{1,0};
  int64_t inp, pub_keys[2], loopcounts[2];
  std::cin >> pub_keys[0] >> pub_keys[1];
  for (int i: {0,1}) loopcounts[i] = find_loop_counter(pub_keys[i]);
  for(int i = 0; i < loopcounts[1]; i++) res.first = (res.first*pub_keys[0])%20201227;
  return res;
}
