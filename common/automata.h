#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>


struct vector3 {
  int x;
  int y;
  int z;
};

namespace std {
  template<> struct std::hash<vector3> {
    std::size_t operator()(const vector3& k)const {
      return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
    };
  };
}


template<typename T>
std::vector<T> offsets();

/**  vector2 helper classes to use vector2 as key **/
struct vector2 {
  int x;
  int y;
};

template<>
std::vector<vector2> offsets() { return {{-1,-1},{-1, 0},{-1, 1},{ 0,-1},{ 0, 1},{ 1,-1},{ 1, 0},{ 1, 1}}; };
vector2 operator +(const vector2 &lhs, const vector2 &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y }; };
bool operator ==(const vector2 &lhs, const vector2 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };

namespace std {
  template<> struct std::hash<vector2> {
    std::size_t operator()(const vector2& k)const { return hash<long long>()(((long long)k.x)^(((long long)k.y)<<32)); };
  };
}

struct automata_options {
  int x_size;
  int y_size;
  bool wraparound;
  int num_layers;
  bool unbounded;
  int (*custom_rule)(int, int, std::vector<int>);
};

template <class K, class V, int num>
class automata {
  public:
    automata<K,V,num>(automata_options opts) { _opts = opts; };
  private:
    automata_options _opts;
    std::unordered_map<K,V> current_gen;
  public:
    bool in_bounds(K k) { return ((k.x >= 0 && k.x < _opts.x_size) && (k.y >= 0 && k.y < _opts.y_size)) || _opts.unbounded; };
   
    void advance_generation() {
      /*
      Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      Any live cell with two or three live neighbours lives on to the next generation.
      Any live cell with more than three live neighbours dies, as if by overpopulation.
      Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      */
      std::unordered_map<K,V> newstate;
      std::unordered_map<K,int> sums;
      for (auto e: current_gen) 
        for(const auto i: offsets<K>()) {
          K k = e.first + i;
//          if (in_bounds(k)) 
            sums[k] = sums[k]+1;
        }

      int cb(0), ca(0);
      for (auto s: sums) {
        if (in_bounds(s.first)) {
            if (s.second == 3) newstate[s.first] = true;
            else if (s.second == 2 && current_gen[s.first]) newstate[s.first] = true;
        }
      }
      current_gen.clear();
      current_gen = newstate;
    };

    void place_pixels(K key, std::vector<K> pixels, V l) { for (auto p: pixels) current_gen[key+p] = l; };
    void place_pixel(K key, V l) { current_gen[key] = l; };

    void print_automata(int generation) {
      printf("\033[2J");
      printf("\33[0;0HGeneration %d (%d on)", generation, count_on());
      for (auto n: current_gen) 
        if (n.second)
          printf("\33[%d;%dH0", n.first.y+2, n.first.x+1);
      printf("\33[39;49m\n\33[%d;%dH", _opts.y_size+3, 0);
      std::cout << std::flush;
    };    

    int count_on() {
      int res(0);
      for (auto e: current_gen) if (e.second) res++;
      return res;
    };
};

class rgb_automata {
  public:
    rgb_automata(automata_options opts) { _opts = opts; };
  private:
    automata_options _opts;
    std::unordered_map<int,std::unordered_map<int,int>> current_gen;
  public:
    void advance_generation() {
      /*
      Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      Any live cell with two or three live neighbours lives on to the next generation.
      Any live cell with more than three live neighbours dies, as if by overpopulation.
      Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      */
      std::unordered_map<int,std::unordered_map<int,int>> newstate;
      for (int x = 0; x < _opts.x_size; x++)
        for (int y = 0; y < _opts.y_size; y++) {
          auto v = count_adjacent(x, y);
          int key((x*_opts.x_size)+y);
          for (int c = 0; c < _opts.num_layers; c++) {
            if (_opts.custom_rule) {
              newstate[key][c] = _opts.custom_rule(c, current_gen[key][c], v);
            } else {
              if (v[c] < 2 || v[c] > 3) newstate[key][c] = 0;
              if (v[c] == 3) newstate[key][c] = 255;
              if (v[c] == 2 && current_gen[key][c]) newstate[key][c] = 255;
            }
          }
        }
      for (int x = 0; x < _opts.x_size; x++)
        for (int y = 0; y < _opts.y_size; y++) {
          int key((x*_opts.x_size)+y);
          for (int c = 0; c < _opts.num_layers; c++)
            current_gen[key][c] = newstate[key][c];
        }
    };

    std::vector<int> count_adjacent(int x, int y) {
      std::vector<int> res{0,0,0};
      for(auto i: std::vector<std::tuple<int,int>>{{-1,-1},{-1, 0},{-1, 1},{ 0,-1},{ 0, 1},{ 1,-1},{ 1, 0},{ 1, 1}}) {
        int xo = x+std::get<0>(i);
        int yo = y+std::get<1>(i);
        int key = (xo*_opts.x_size)+yo;
        if (_opts.wraparound) 
          key = (((xo+_opts.x_size)%_opts.x_size)*_opts.x_size)+((yo+_opts.y_size)%_opts.y_size);
        for(int c = 0; c< _opts.num_layers; c++)
          if (current_gen[key][c] == 255) res[c]++;
      }
      return res;
    };

    void clear_to_color(int r, int g, int b) {
      for (int c = 0; c < 3; c++)
        for (int x = 0; x < _opts.x_size; x++)
          for (int y = 0; y < _opts.y_size; y++) {
            int key = (x*_opts.x_size)+y;
            if (_opts.wraparound) 
              key = (((x+_opts.x_size) %_opts.x_size)*_opts.x_size)+((y+_opts.y_size)%_opts.y_size);
            current_gen[key][0] = r;
            current_gen[key][1] = g;
            current_gen[key][2] = b;
          }
    };

    void place_pixels(int x, int y, std::vector<std::pair<int,int>> pixels, int r, int g, int b) {
      for (auto p: pixels) {
        int key = ((x+p.first)*_opts.x_size)+(y+p.second);
        if (_opts.wraparound) 
          key = ((((x+p.first)+_opts.x_size) %_opts.x_size)*_opts.x_size)+(((y+p.second)+_opts.y_size)%_opts.y_size);
        if (r != 0) current_gen[key][0] = r;
        if (g != 0) current_gen[key][1] = g;
        if (b != 0) current_gen[key][2] = b;
      }
    }

  public: // Debugging functions
    void print_automata() {
      for (int x = 0; x < _opts.x_size; x++) 
        for (int y = 0; y < _opts.y_size; y++)
          printf("\33[%d;%dH\33[48;2;%d;%d;%dm  ", y+2, (x*2)+2, current_gen[(x*_opts.x_size)+y][0], current_gen[(x*_opts.x_size)+y][1], current_gen[(x*_opts.x_size)+y][2]);
      printf("\33[39;49m\n");
      std::cout << std::flush;
    };
};


#endif