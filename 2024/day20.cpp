#include <sstream>
#include <vector>
#include <map>
#include <queue>

#include "../common/grid2d.h"
#include "../common/vector2.h"
#include "../common/lib.h"

struct work {
    vector2<int> pos;
    int64_t score;
    int64_t cheatcount;
    bool cheated;
    bool operator<(const work &compare_to) const { return score < compare_to.score; }
};

std::pair<std::uintmax_t, std::uintmax_t> shortest_cheat_path(tbb::grid2d<char> g) {
    std::map<vector2<int>, std::pair<int64_t, int64_t>> scoremap;
    // clang-format off
    auto s = g.find_elements('S')[0]; g.remove_element(s); auto fs = g.floodfill(s);
    auto e = g.find_elements('E')[0]; g.remove_element(e); auto fe = g.floodfill(e);
    // clang-format on

    int64_t best;
    for (auto l : fs)
        if (best == 0 || best > (l.second + fe[l.first])) best = l.second + fe[l.first];
    std::cout << best << std::endl;

    std::pair<std::uintmax_t, std::uintmax_t> res{0, 0};
    for (auto se : fs) {
        for (auto ee : fe) {
            if (se == ee) continue;
            int64_t td = (se.first - ee.first).manhattanlength();
            if (td > 20 && td == 1) continue;
            int64_t l = (s - se.first).manhattanlength() + (ee.first - e).manhattanlength() + td;
            if (l >= best || (best - l < 100)) continue;
            auto p1 = fs[se.first];
            if (p1 >= best) continue;
            auto p2 = fe[ee.first];
            if ((best - p1 + td + p2) >= 100) {
                res.second++;
                if (td == 1) res.first++;
            }
        }
    }
    return res;
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    tbb::grid2d<char> g;
    g.read();
    return shortest_cheat_path(g);
}
