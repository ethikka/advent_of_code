#ifndef GRID2D_H
#define GRID2D_H

#include <iostream>
#include <map>
#include <cmath>

#include "vector2.h"

enum direction { north,
                 east,
                 south,
                 west,
                 none };
vector2<int> offsets[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
vector2<int> diagonals[8] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
std::string dir_from = "v<^>";
std::string dir_to = "^>v<";

direction rev_dir(direction d) { return (direction)((d + 2) % 4); };

std::vector<direction> all_but(direction dir) {
    switch (dir) {
        case north:
            return {west, north, east};
        case south:
            return {west, south, east};
        case east:
            return {north, east, south};
        case west:
            return {north, west, south};
        default:
            return {north, west, south, east};
    }
};

template <typename V>
V to_v(char c);

template <>
int to_v(char c) { return (c - '0'); };

template <>
char to_v(char c) { return c; };

std::map<char, std::map<direction, direction>> deflections = {
    {'\\', {{north, west}, {south, east}, {west, north}, {east, south}}},
    {'/', {{north, east}, {south, west}, {west, south}, {east, north}}}};

namespace tbb {
template <class V>
class grid2d {
   private:
    std::map<vector2<int>, V> map;

   public:
    int _x;
    int _y;
    grid2d() {
        _x = 0;
        _y = 0;
    }
    void read() { read(char(0)); }
    void read(char ignore) {
        char inp;
        int x(0), y(0), width(0);

        while (std::cin >> std::noskipws >> inp) {
            switch (inp) {
                case '\n':
                    if (x == 0) return;
                    width = x;
                    x = 0;
                    y++;
                    break; /*next line*/
                default:
                    if (ignore == 0 || ignore != inp) place_element({x, y}, to_v<V>(inp));
                    _x = std::max(_x, x);
                    _y = std::max(_y, y);
                    x++;
                    break;
            }
        }
    };
    void remove_element(vector2<int> key) { map.erase(key); };
    void wipe_elements(V val) {
        for (auto e : find_elements(val)) remove_element(e);
    }

    void place_element(vector2<int> key, V v) {
        map[key] = v;
    };
    void move_element(vector2<int> oldkey, vector2<int> newkey) {
        if (!has_element(newkey)) {
            place_element(newkey, get_element(oldkey).second);
            map.erase({oldkey});
        }
    };
    std::pair<vector2<int>, V> get_element(vector2<int> key) {
        if (map.find(key) != map.end()) return {key, map[key]};
        return {{0, 0}, '.'};
    };
    bool has_element(vector2<int> key) { return map.find(key) != map.end(); };
    bool in_bounds(vector2<int> v) { return ((v.x >= 0 && v.y >= 0 && v.x <= _x && v.y <= _y)); };
    std::vector<vector2<int>> find_elements(V val) {
        std::vector<vector2<int>> res;
        for (auto e : map)
            if (map[e.first] == val) res.push_back(e.first);
        return res;
    };
    void print() {
        printf("\033[2J");
        for (auto n : map)
            printf("\33[%d;%dH%c", n.first.y + 5, n.first.x + 5, n.second);
        printf("\33[39;49m\n\33[%d;%dH", 190, 0);
        std::cout << std::flush;
    };
    std::map<vector2<int>, V> get_raw() { return map; }
    int64_t count() { return map.size(); }

    void insert_row(int below_row, int amount = 1) {
        std::map<vector2<int>, V> newmap;
        for (auto e : map) newmap[{e.first.x, e.first.y + ((e.first.y > below_row) * amount)}] = e.second;
        map = newmap;
    }
    void insert_col(int right_of_col, int amount = 1) {
        std::map<vector2<int>, V> newmap;
        for (auto e : map) newmap[{e.first.x + ((e.first.x > right_of_col) * amount), e.first.y}] = e.second;
        map = newmap;
    }

    std::pair<vector2<int>, V> operator[](vector2<int> index) {
        return get_element(index);
    }
};
}  // namespace tbb

#endif
