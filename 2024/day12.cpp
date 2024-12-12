#include <sstream>
#include <queue>
#include <vector>
#include <map>

#include "../common/grid2d.h"
#include "../common/lib.h"

tbb::grid2d<char> grid;

std::map<int, std::set<std::pair<vector2<int>, vector2<int>>>> fences;
std::map<int, std::set<vector2<int>>> plots;

bool get_erasables() {
    int fc = fences.size();
    if (grid.count() == 0) return (plots[fc].size() > 0);
    auto vec = grid.get_raw().begin()->first;
    auto c = grid.get_raw().begin()->second;
    std::queue<vector2<int>> q;
    q.emplace(vec);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        plots[fc].emplace(v);
        if (grid.has_element(v))
            for (auto o : offsets) {
                if (grid.get_element(v + o).second == c) {
                    q.emplace(v + o);
                } else if (plots[fc].count(v + o) == 0)
                    fences[fc].emplace(std::make_pair(v, v + o));
            }
        grid.remove_element(v);
    }
    return (plots[fc].size() > 0);
}

void floodfill_and_erase() {
    while (get_erasables());
}

std::set<std::pair<vector2<int>, vector2<int>>> discount_fence(std::set<std::pair<vector2<int>, vector2<int>>> inp) {
    std::set<std::pair<vector2<int>, vector2<int>>> res(inp);
    for (auto e : inp)
        if (res.count(e)) {
            int mul(1);
            while (inp.count({e.first + (offsets[1] * mul), e.second + (offsets[1] * mul)})) res.erase({e.first + (offsets[1] * mul), e.second + (offsets[1] * mul++)});
            mul = 1;
            while (inp.count({e.first + (offsets[2] * mul), e.second + (offsets[2] * mul)})) res.erase({e.first + (offsets[2] * mul), e.second + (offsets[2] * mul++)});
        }
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    grid.read();
    floodfill_and_erase();
    for (int i = 0; i < fences.size(); i++) {
        res.first += fences[i].size() * plots[i].size();
        res.second += discount_fence(fences[i]).size() * plots[i].size();
    }
    return res;
}