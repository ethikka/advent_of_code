#include <sstream>
#include <map>
#include <tuple>
#include <cmath>
#include "../common/lib.h"

std::map<std::string, bool> cc;
std::map<std::string, bool> hcc;
int startsize_x(3), startsize_y(3), startsize_z(1), startsize_w(1);

std::string to_key3(std::tuple<int,int,int> inp) {
  return std::to_string(std::get<0>(inp))+"#"+
         std::to_string(std::get<1>(inp))+"#"+
         std::to_string(std::get<2>(inp));
}

int count_adjecant3(int x, int y, int z) {
  int res(0);
  for(auto zo: {z-1,z,z+1}) 
  for(auto yo: {y-1,y,y+1}) 
  for(auto xo: {x-1,x,x+1}) {
    if (!(xo == x && yo == y && zo == z))
    if (cc[to_key3({zo, yo, xo})]) res++;
  }
  return res;
}  

void generation3(int gen) {
  std::map<std::string, bool> diff;
  for (int zz = 0-gen; zz < (startsize_z+gen); zz++) 
  for (int yy = 0-gen; yy < (startsize_y+gen); yy++) 
  for (int xx = 0-gen; xx < (startsize_x+gen); xx++) {
    std::string k = to_key3({zz, yy, xx});
    switch (count_adjecant3(xx, yy, zz)) {
      case 3: diff[k] = true; break;
      case 2: diff[k] = cc[k]; break;
      default: diff[k] = false;
    }
  }
  for(auto d: diff) cc[d.first] = d.second;
}

std::string to_key4(std::tuple<int,int,int,int> inp) {
  return std::to_string(std::get<0>(inp))+"#"+
         std::to_string(std::get<1>(inp))+"#"+
         std::to_string(std::get<2>(inp))+"#"+
         std::to_string(std::get<3>(inp));
}

int count_adjecant4(int x, int y, int z, int w) {
  int res(0);
  for(auto wo: {w-1,w,w+1}) 
  for(auto zo: {z-1,z,z+1}) 
  for(auto yo: {y-1,y,y+1}) 
  for(auto xo: {x-1,x,x+1}) {
    if (!(xo == x && yo == y && zo == z && wo == w))
    if (hcc[to_key4({wo, zo, yo, xo})]) res++;
  }
  return res;
}  

void generation4(int gen) {
  std::map<std::string, bool> diff;
  for (int ww = 0-gen; ww < (startsize_w+gen); ww++) 
  for (int zz = 0-gen; zz < (startsize_z+gen); zz++) 
  for (int yy = 0-gen; yy < (startsize_y+gen); yy++) 
  for (int xx = 0-gen; xx < (startsize_x+gen); xx++) {
    std::string k = to_key4({ww, zz, yy, xx});
    switch (count_adjecant4(xx, yy, zz, ww)) {
      case 3: diff[k] = true; break;
      case 2: diff[k] = hcc[k]; break;
      default: diff[k] = false;
    }
  }
  for(auto d: diff) hcc[d.first] = d.second;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  int x(0), y(0), z(0), w(0);
  char inp;
  while (std::cin >> std::noskipws >> inp) 
    if (inp == '\n') {
      startsize_x = x; x = 0; y++;
    } else {
      cc[to_key3({z, y, x})] = (inp == '#');
      hcc[to_key4({w, z, y, x++})] = (inp == '#');
    }
  startsize_y = y+1;

  for (int i = 1; i < 7; i++) {
    generation3(i);
    generation4(i);
  }
    
  for (auto c: cc) if (c.second) res.first++;
  for (auto c: hcc) if (c.second) res.second++;

  return res;
}
