#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include "../common/lib.h"

std::vector<std::string> file;
int fileptr(0);

struct node;
std::vector<node> nodes;
std::set<std::uintmax_t> sizes;
std::uintmax_t dirsize_a(0);

struct node {
  node(int64_t _p) { parent = _p; filesize = 0;}
  int64_t parent;
  std::uintmax_t filesize;
  std::vector<int64_t> children;

  std::uintmax_t calcsize() { 
    std::uintmax_t res(filesize);
    for (auto n: children) res += nodes[n].calcsize();
    sizes.emplace(res);
    if (res <= 100000) dirsize_a += res; 
    return res;
  }
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (std::getline(std::cin, line)) file.push_back(line);

  nodes.push_back(node(-1));
  int64_t ptr(0);

  for (int fileptr = 0; fileptr < file.size(); fileptr++) {
    switch (file[fileptr][2]) {
      case 'c': {
        switch (file[fileptr][5]) {
          case '.': ptr = nodes[ptr].parent; break;
          case '/': ptr = 0; break;
          default:
            nodes[ptr].children.push_back(nodes.size());
            nodes.push_back(node(ptr));
            ptr = nodes.size()-1;
        }
        break;}
      case 'l': {
        fileptr++;
        while (fileptr != file.size() && file[fileptr][0] != '$') {
          std::string size = file[fileptr].substr(0, file[fileptr].find_first_of(' '));
          if (size != "dir") nodes[ptr].filesize += std::stoul(size); 
          fileptr++;
        }
        fileptr--;
        break; }
    }
  }
  std::uintmax_t target = 30000000 - (70000000 - nodes[0].calcsize());
  for (auto s: sizes) if (s > target) return { dirsize_a, s };
  return res;
}