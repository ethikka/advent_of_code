#ifndef GENERATIONGRID_H
#define GENERATIONGRID_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include "vector2.h"

template <class K>
class generationgrid {
  public:
    generationgrid<K>(K (*_check_node)(K,std::unordered_map<K,bool>), bool (*_check_change)(K, std::vector<K>)) { check_node = _check_node; check_change = _check_change; };
  private:
    K (*check_node)(K, std::unordered_map<K,bool>);
    bool (*check_change)(K, std::vector<K>);

    std::unordered_map<K,bool> current_gen;
  public:
    int number_of_changes_last_gen;
    void advance_generation() {
      number_of_changes_last_gen = 0;
      std::unordered_map<K,bool> newstate;
      std::map<K, std::vector<K>> changes;

      for (auto e: current_gen) {
        K np = check_node(e.first, current_gen);
        changes[np].push_back(e.first);
      }

      for (auto ch: changes) {
        if (check_change(ch.first, ch.second)) { newstate[ch.first] = true; number_of_changes_last_gen++; }
        else for (auto p: ch.second)             newstate[p] = true;
      }
      current_gen = newstate;
    };
    
    int box_size() {
      int64_t mx(-9999999), mix(9999999), my(-9999999), miy(9999999);
      for(auto s: current_gen) { mx = fmax(mx, s.first.x); mix = fmin(mix, s.first.x);
                                 my = fmax(my, s.first.y); miy = fmin(miy, s.first.y); }
      return (std::abs(mx-mix+1)*std::abs(my-miy+1));
    }
    
    void place_pixels(K key, std::vector<K> pixels, bool l) { for (auto p: pixels) current_gen[key+p] = l; };
    void place_pixel(K key, bool l) { current_gen[key] = l; };

    void print_automata(int generation) {
      printf("\033[2J");
      printf("\33[0;0HGeneration %d", generation);
      for (auto n: current_gen) 
        if (n.second)
          printf("\33[%d;%dH0", n.first.y+5, n.first.x+1);
      printf("\33[39;49m\n\33[%d;%dH", 20, 0);
      std::cout << std::flush;
    };    
    std::unordered_map<K,bool> get_raw() { return current_gen; }
};

#endif