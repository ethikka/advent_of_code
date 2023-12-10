#ifndef GRID2D_H
#define GRID2D_H

#include <map>
#include <cmath>
#include "vector2.h"

namespace tbb {
  template <class V>
  class grid2d {
    private:
      std::map<vector2,V> map;
    public:
      int _x;
      int _y;
      void read() {
        char inp;
        int x(0), y(0), width(0);
  
        while (std::cin >> std::noskipws >> inp) {
          switch(inp) {
            case '\n': width = x; x = 0; y++; break; /*next line*/
            default: 
              place_element({x++, y}, inp); break;
          }
        }
      };
      void place_element(vector2 key, V v) { map[key] = v; _x = std::max(_x, key.x); _y = std::max(_y, key.y); };
      std::pair<vector2,V> get_element(vector2 key) { if (map.find(key) != map.end()) return {key, map[key]}; return {{0,0},'.'};};
      bool has_element(vector2 key) { return map.find(key) != map.end(); };
      std::vector<vector2> find_elements(V val) {
        std::vector<vector2> res;
        for(auto e: map) if (map[e.first] == val) res.push_back(e.first);
        return res;
      };
      void print() {
        printf("\033[2J");
        for (auto n: map) 
          printf("\33[%d;%dH%c", n.first.y+15, n.first.x+15, n.second);
        printf("\33[39;49m\n\33[%d;%dH", 190, 0);
        std::cout << std::flush;
      };
      std::map<vector2,V> get_raw() { return map; }
      int64_t count() { return map.size(); }
  };
}

#endif
