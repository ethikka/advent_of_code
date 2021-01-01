#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

struct automata_options {
  int x_size;
  int y_size;
  bool wraparound;
  int num_layers;
  int (*custom_rule)(int, int, std::vector<int>);
};

//template <class T, int>
class automata {
  public:
    automata(automata_options opts) { _opts = opts; };
  private:
    automata_options _opts;
    std::map<int,std::map<int,int>> current_gen;
  public:
    void advance_generation() {
      /*
      Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      Any live cell with two or three live neighbours lives on to the next generation.
      Any live cell with more than three live neighbours dies, as if by overpopulation.
      Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      */
      std::map<int,std::map<int,int>> newstate;
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

/*
std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::srand(std::time(NULL));
  automata a(32, 8, true);
  printf("\33c");
  for (int i = 0; i < 16; i++) 
    a.place_pixels((rand()%64), (rand()%16), shapes[rand()%shapes.size()], (rand()%2)*rand()%255, (rand()%2)*rand()%255, (rand()%2)*rand()%255);
  
//  a.clear_to_color(255,255,0);
  int count(0);
  while (count++ < 500) {
    a.print_automata();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    a.advance_generation();
  }
  a.print_automata();
  return {0,0};
}*/
#endif