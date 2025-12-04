#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "vector2.h"

template <typename T>
std::vector<T> offsets();

template <typename T>
struct automata_options {
    T bounds;
    bool wraparound;
    int num_layers;
    bool unbounded;
    int (*custom_rule)(int, int, std::vector<int>);
};

#pragma region Key helpers
//--------------------------------------------------------------------------------------------------------------------------------

template <>
std::vector<vector2<int>> offsets() { return {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; };
bool in_bounds(vector2<int> k, automata_options<vector2<int>> _opts) { return _opts.unbounded || ((k.x >= 0 && k.x < _opts.bounds.x) && (k.y >= 0 && k.y < _opts.bounds.y)); };
vector2<int> operator+(const vector2<int> &lhs, const vector2<int> &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; };
bool operator==(const vector2<int> &lhs, const vector2<int> &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };

namespace std {
template <>
struct std::hash<vector2<int>> {
    std::size_t operator()(const vector2<int> &k) const { return hash<long long>()(((long long)k.x) ^ (((long long)k.y) << 32)); };
};
}  // namespace std

/**  vector3 helper classes to use vector3 as key **/
struct vector3 {
    int x;
    int y;
    int z;
};

template <>
std::vector<vector3> offsets() { return {{-1, -1, -1}, {-1, -1, 0}, {-1, -1, +1}, {-1, 0, -1}, {-1, 0, 0}, {-1, 0, +1}, {-1, +1, -1}, {-1, +1, 0}, {-1, +1, +1}, {0, -1, -1}, {0, -1, 0}, {0, -1, +1}, {0, 0, -1}, {0, 0, +1}, {0, +1, -1}, {0, +1, 0}, {0, +1, +1}, {+1, -1, -1}, {+1, -1, 0}, {+1, -1, +1}, {+1, 0, -1}, {+1, 0, 0}, {+1, 0, +1}, {+1, +1, -1}, {+1, +1, 0}, {+1, +1, +1}}; };
bool in_bounds(vector3 k, automata_options<vector3> _opts) { return _opts.unbounded || ((k.x >= 0 && k.x < _opts.bounds.x) && (k.y >= 0 && k.y < _opts.bounds.y) && (k.z >= 0 && k.z < _opts.bounds.z)); };
vector3 operator+(const vector3 &lhs, const vector3 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; };
bool operator==(const vector3 &lhs, const vector3 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; };

namespace std {
template <>
struct std::hash<vector3> {
    std::size_t operator()(const vector3 &k) const { return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z); };
};
}  // namespace std
//--------------------------------------------------------------------------------------------------------------------------------

/**  vector4 helper classes to use vector4 as key **/
struct vector4 {
    int x;
    int y;
    int z;
    int w;
};

template <>
std::vector<vector4> offsets() { return {{-1, -1, -1, -1}, {-1, -1, -1, +0}, {-1, -1, -1, +1}, {-1, -1, +0, -1}, {-1, -1, +0, +0}, {-1, -1, +0, +1}, {-1, -1, +1, -1}, {-1, -1, +1, +0}, {-1, -1, +1, +1}, {-1, +0, -1, -1}, {-1, +0, -1, +0}, {-1, +0, -1, +1}, {-1, +0, +0, -1}, {-1, +0, +0, +0}, {-1, +0, +0, +1}, {-1, +0, +1, -1}, {-1, +0, +1, +0}, {-1, +0, +1, +1}, {-1, +1, -1, -1}, {-1, +1, -1, +0}, {-1, +1, -1, +1}, {-1, +1, +0, -1}, {-1, +1, +0, +0}, {-1, +1, +0, +1}, {-1, +1, +1, -1}, {-1, +1, +1, +0}, {-1, +1, +1, +1}, {+0, -1, -1, -1}, {+0, -1, -1, +0}, {+0, -1, -1, +1}, {+0, -1, +0, -1}, {+0, -1, +0, +0}, {+0, -1, +0, +1}, {+0, -1, +1, -1}, {+0, -1, +1, +0}, {+0, -1, +1, +1}, {+0, +0, -1, -1}, {+0, +0, -1, +0}, {+0, +0, -1, +1}, {+0, +0, +0, -1}, {+0, +0, +0, +1}, {+0, +0, +1, -1}, {+0, +0, +1, +0}, {+0, +0, +1, +1}, {+0, +1, -1, -1}, {+0, +1, -1, +0}, {+0, +1, -1, +1}, {+0, +1, +0, -1}, {+0, +1, +0, +0}, {+0, +1, +0, +1}, {+0, +1, +1, -1}, {+0, +1, +1, +0}, {+0, +1, +1, +1}, {+1, -1, -1, -1}, {+1, -1, -1, +0}, {+1, -1, -1, +1}, {+1, -1, +0, -1}, {+1, -1, +0, +0}, {+1, -1, +0, +1}, {+1, -1, +1, -1}, {+1, -1, +1, +0}, {+1, -1, +1, +1}, {+1, +0, -1, -1}, {+1, +0, -1, +0}, {+1, +0, -1, +1}, {+1, +0, +0, -1}, {+1, +0, +0, +0}, {+1, +0, +0, +1}, {+1, +0, +1, -1}, {+1, +0, +1, +0}, {+1, +0, +1, +1}, {+1, +1, -1, -1}, {+1, +1, -1, +0}, {+1, +1, -1, +1}, {+1, +1, +0, -1}, {+1, +1, +0, +0}, {+1, +1, +0, +1}, {+1, +1, +1, -1}, {+1, +1, +1, +0}, {+1, +1, +1, +1}}; };
bool in_bounds(vector4 k, automata_options<vector4> _opts) { return _opts.unbounded || ((k.x >= 0 && k.x < _opts.bounds.x) && (k.y >= 0 && k.y < _opts.bounds.y) && (k.z >= 0 && k.z < _opts.bounds.z) && (k.z >= 0 && k.z < _opts.bounds.w)); };
vector4 operator+(const vector4 &lhs, const vector4 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w}; };
bool operator==(const vector4 &lhs, const vector4 &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; };

namespace std {
template <>
struct std::hash<vector4> {
    std::size_t operator()(const vector4 &k) const { return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z) ^ std::hash<int>()(k.w); };
};
}  // namespace std
//--------------------------------------------------------------------------------------------------------------------------------
#pragma endregion

template <class K, class V, int num>
class automata {
   public:
    automata<K, V, num>(automata_options<K> opts) { _opts = opts; };

   private:
    automata_options<K> _opts;
    std::unordered_map<K, V> current_gen;

   public:
    void advance_generation() {
        /*
        Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        Any live cell with two or three live neighbours lives on to the next generation.
        Any live cell with more than three live neighbours dies, as if by overpopulation.
        Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        */
        std::unordered_map<K, V> newstate;
        std::unordered_map<K, int> sums;
        for (auto e : current_gen)
            for (const auto i : offsets<K>())
                sums[e.first + i]++;

        for (auto s : sums) {
            if (in_bounds(s.first, _opts)) {
                if (s.second == 3)
                    newstate[s.first] = true;
                else if (s.second == 2 && current_gen[s.first])
                    newstate[s.first] = true;
            }
        }
        current_gen = newstate;
    };

    void place_pixels(K key, std::vector<K> pixels, V l) {
        for (auto p : pixels) current_gen[key + p] = l;
    };
    void place_pixel(K key, V l) { current_gen[key] = l; };

    void print_automata(int generation) {
        printf("\033[2J");
        printf("\33[0;0HGeneration %d (%d on)", generation, count_on());
        for (auto n : current_gen)
            if (n.second)
                printf("\33[%d;%dH0", n.first.y + 2, n.first.x + 1);
        printf("\33[39;49m\n\33[%d;%dH", _opts.bounds.y + 3, 0);
        std::cout << std::flush;
    };

    int count_on() {
        int res(0);
        for (auto e : current_gen)
            if (e.second) res++;
        return res;
    };
};

class rgb_automata {
   public:
    rgb_automata(automata_options<vector2<int>> opts) { _opts = opts; };

   private:
    automata_options<vector2<int>> _opts;
    std::unordered_map<int, std::unordered_map<int, int>> current_gen;

   public:
    void advance_generation() {
        /*
        Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        Any live cell with two or three live neighbours lives on to the next generation.
        Any live cell with more than three live neighbours dies, as if by overpopulation.
        Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        */
        std::unordered_map<int, std::unordered_map<int, int>> newstate;
        for (int x = 0; x < _opts.bounds.x; x++)
            for (int y = 0; y < _opts.bounds.y; y++) {
                auto v = count_adjacent(x, y);
                int key((x * _opts.bounds.x) + y);
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
        for (int x = 0; x < _opts.bounds.x; x++)
            for (int y = 0; y < _opts.bounds.y; y++) {
                int key((x * _opts.bounds.x) + y);
                for (int c = 0; c < _opts.num_layers; c++)
                    current_gen[key][c] = newstate[key][c];
            }
    };

    std::vector<int> count_adjacent(int x, int y) {
        std::vector<int> res{0, 0, 0};
        for (auto i : std::vector<std::tuple<int, int>>{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}) {
            int xo = x + std::get<0>(i);
            int yo = y + std::get<1>(i);
            int key = (xo * _opts.bounds.x) + yo;
            if (_opts.wraparound)
                key = (((xo + _opts.bounds.x) % _opts.bounds.x) * _opts.bounds.x) + ((yo + _opts.bounds.y) % _opts.bounds.y);
            for (int c = 0; c < _opts.num_layers; c++)
                if (current_gen[key][c] == 255) res[c]++;
        }
        return res;
    };

    void clear_to_color(int r, int g, int b) {
        for (int c = 0; c < 3; c++)
            for (int x = 0; x < _opts.bounds.x; x++)
                for (int y = 0; y < _opts.bounds.y; y++) {
                    int key = (x * _opts.bounds.x) + y;
                    if (_opts.wraparound)
                        key = (((x + _opts.bounds.x) % _opts.bounds.x) * _opts.bounds.x) + ((y + _opts.bounds.y) % _opts.bounds.y);
                    current_gen[key][0] = r;
                    current_gen[key][1] = g;
                    current_gen[key][2] = b;
                }
    };

    void place_pixels(vector2<int> pos, std::vector<vector2<int>> pixels, int r, int g, int b) {
        for (auto p : pixels) {
            int key = ((pos.x + p.x) * _opts.bounds.x) + (pos.y + p.y);
            if (_opts.wraparound)
                key = ((((pos.x + p.x) + _opts.bounds.x) % _opts.bounds.x) * _opts.bounds.x) + (((pos.y + p.y) + _opts.bounds.y) % _opts.bounds.y);
            if (r != 0) current_gen[key][0] = r;
            if (g != 0) current_gen[key][1] = g;
            if (b != 0) current_gen[key][2] = b;
        }
    }

   public:  // Debugging functions
    void print_automata(int gen) {
        for (int x = 0; x < _opts.bounds.x; x++)
            for (int y = 0; y < _opts.bounds.y; y++)
                printf("\33[%d;%dH\33[48;2;%d;%d;%dm  ", y + 2, (x * 2) + 2, current_gen[(x * _opts.bounds.x) + y][0], current_gen[(x * _opts.bounds.x) + y][1], current_gen[(x * _opts.bounds.x) + y][2]);
        printf("\33[39;49m\n");
        std::cout << std::flush;
    };
};

#endif