#include <sstream>
#include <vector>
#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

int64_t remove_layer(tbb::grid2d<char>& g) {
    std::vector<vector2<int>> re;
    for (auto c : g.get_raw()) {
        int ss(0);
        for (auto d : diagonals)
            if (g.in_bounds(c.first + d))
                if (g.has_element(c.first + d)) ss++;
        if (ss < 4) re.push_back(c.first);
    }
    int64_t res = re.size();
    for (auto r : re) g.remove_element(r);
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    int64_t f, s;
    tbb::grid2d<char> g('.');
    s = g.count();
    f = remove_layer(g);
    while (remove_layer(g));
    return {f, s - g.count()};
}