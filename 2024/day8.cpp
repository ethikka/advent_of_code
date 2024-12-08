#include <sstream>
#include <set>

#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

std::vector<vector2<int>> find_antinodes(tbb::grid2d<char> g, vector2<int> v1, vector2<int> v2, bool resonant) {
    std::vector<vector2<int>> res;
    vector2<int> diff = v1 - v2, vv1 = v1 + diff, vv2 = v2 - diff;
    res.push_back(vv1);
    res.push_back(vv2);

    if (resonant) {
        while (g.in_bounds(vv1)) {
            vv1 = vv1 + diff;
            res.push_back(vv1);
        }
        while (g.in_bounds(vv2)) {
            vv2 = vv2 - diff;
            res.push_back(vv2);
        }
        res.push_back(v1);
        res.push_back(v2);
    }

    return res;
};

int count_antinodes(tbb::grid2d<char> g, bool resonant) {
    std::set<char> pn;
    std::set<vector2<int>> an;
    for (auto e : g.get_raw()) pn.emplace(e.second);

    for (auto c : pn) {
        auto cn = g.find_elements(c);
        for (int i = 0; i < cn.size(); i++)
            for (int j = i + 1; j < cn.size(); j++)
                for (auto r : find_antinodes(g, cn.at(i), cn.at(j), resonant))
                    if (g.in_bounds(r))
                        an.emplace(r);
    }
    return an.size();
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    tbb::grid2d<char> grid;
    grid.read('.');
    return {count_antinodes(grid, false), count_antinodes(grid, true)};
}