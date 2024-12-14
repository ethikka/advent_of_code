#include <sstream>
#include <vector>
#include <map>

#include "../common/vector2.h"
#include "../common/lib.h"

struct robot {
    vector2<int> pos;
    vector2<int> movement;
};

std::pair<std::uintmax_t, std::uintmax_t> simulate(std::vector<robot> guards, int cycles, int size_x, int size_y) {
    std::pair<std::uintmax_t, std::uintmax_t> res = {0, 0};
    std::vector<robot> gg;
    vector2<int> gridsize(size_x, size_y);
    int cnt(0);
    for (auto r : guards) gg.push_back(r);
    while (res.first == 0 || res.second == 0) {
        cnt++;
        for (auto& r : gg) r.pos = (r.pos + r.movement + gridsize) % gridsize;
        if (res.second == 0) {
            bool valid(true);
            std::map<vector2<int>, int> tree;
            for (auto r : gg) {
                tree[r.pos]++;
                valid &= (tree[r.pos] == 1);
            }
            if (valid) res.second = cnt;
        }
        if (cnt == cycles) {
            int c0(0), c1(0), c2(0), c3(0), mid_row((size_y - 1) / 2), mid_col((size_x - 1) / 2);
            for (auto r : gg) {
                if (r.pos.x < mid_col && r.pos.y < mid_row) c0++;
                if (r.pos.x > mid_col && r.pos.y < mid_row) c1++;
                if (r.pos.x < mid_col && r.pos.y > mid_row) c2++;
                if (r.pos.x > mid_col && r.pos.y > mid_row) c3++;
            }
            res.first = c0 * c1 * c2 * c3;
        }
    }
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::vector<robot> guards;
    std::string start, vec;
    while (std::cin >> start >> vec)
        guards.push_back(robot{vector2<int>(start.substr(2)), vector2<int>(vec.substr(2))});
    return simulate(guards, 100, 101, 103);
}