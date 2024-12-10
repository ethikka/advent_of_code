#include <sstream>
#include <queue>
#include <map>

#include "../common/lib.h"
#include "../common/grid2d.h"

std::pair<int64_t, int64_t> count_paths(tbb::grid2d<int> g, vector2<int> start) {
    std::queue<std::pair<vector2<int>, int>> q;
    std::map<vector2<int>, int> ends;
    q.emplace(std::pair<vector2<int>, int>{start, 0});
    while (!q.empty()) {
        auto c = q.front();
        q.pop();

        if (c.second == 9) ends[c.first]++;

        for (auto o : offsets)
            if (g.get_element(c.first + o).second == (c.second + 1))
                q.emplace(std::pair<vector2<int>, int>{c.first + o, c.second + 1});
    }
    int res = 0;
    for (auto e : ends) res += e.second;
    return {ends.size(), res};
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    tbb::grid2d<int> g;
    g.read();
    for (auto e : g.find_elements(0)) {
        auto r = count_paths(g, e);
        res.first += r.first;
        res.second += r.second;
    }

    return res;
}