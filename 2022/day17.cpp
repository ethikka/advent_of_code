#include <sstream>
#include <vector>
#include <map>
#include "../common/lib.h"
#include "../common/circularlist.h"

struct pos { int x; int y;};

struct block {
  std::vector<uint8_t> enc;
  block(std::string inp) {
    std::string tmp(inp);
    while (tmp.find('|') != std::string::npos) {
      int pos = tmp.find('|');
      pixels.push_back(tmp.substr(0, pos));
      tmp = tmp.substr(pos+1);
    }
    pixels.push_back(tmp);
    for (auto p: pixels) {
      uint8_t m(1), r(0);
      for (int i = 0; i < p.size(); i++) { if (p[i] == '#') r += m; m *= 2; }
      enc.push_back(r);
    }
  };
  std::vector<std::string> pixels;
  std::string offset(int o) {
    std::string res;
    for(uint8_t c: enc) res += (c << o);
    return res;
  }
};

struct chamber {
  chamber() { shaft = (char)127; /* bodem */ }
  int64_t height() { return 0; };
  std::string shaft;

  void simulate_block(block b, tbb::circularlist<char> &jets) {
    pos p = {2, static_cast<int>(b.pixels.size()+2+shaft.size())};
    bool collision(false);
    while (!collision) {
      switch (jets.front_and_next()) {
        case '<': if (p.x > 0) p.x--; break;
        case '>': if (p.x < (7-b.pixels[0].size())) p.x++; break;
      }
      auto bo = b.offset(p.x);
      std::cout << p.y << std::endl;
      if (p.y < 0) return;

      if ((p.y+b.pixels.size()-1) <= shaft.size()) {
        int cc(b.pixels.size());
        collision = true;
        for (char c: bo) {
          collision &= ((c && shaft[p.y-(cc--)]) == 0);
        }
      }

      // can move down?
      if (collision) {
        std::cout << "Krak " << p.y << std::endl;
        for (char c: bo) 
          shaft[p.y] |= c;
        // put block in shaft at current pos
        return;
      } else p.y--;
    }
  };
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  tbb::circularlist<char> jets;
  char c;
  while (std::cin >> c) jets.enqueue(c);

  tbb::circularlist<block> blocks;
  blocks.enqueue({block("####"),block(".#.|###|.#."),block("..#|..#|###"),block("#|#|#|#"),block("##|##")});

  chamber ch;

  int r(0);
  while (r++ < 5/*2022*/) ch.simulate_block(blocks.front_and_next(), jets);
  res.first = ch.height();
//  while (r++ < 2022) ch.simulate_block(blocks.front_and_next(), jets);
//  res.second = ch.height();
  return res;
}