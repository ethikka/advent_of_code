#include <map>
#include <queue>
#include <set>
#include <sstream>

#include "../common/lib.h"
#include "../common/grid2d.h"
#include "../common/vector2.h"

struct work {
    vector2<int> p;
    direction d;
};

int64_t sol_a(tbb::grid2d<char>& grid) {
    vector2<int> guard = grid.find_elements('^')[0];
    direction d = north;

    std::set<vector2<int>> visited;
    std::queue<work> q;
    q.emplace(work{guard, d});
    while (!q.empty()) {
        auto w = q.front();
        q.pop();
        visited.emplace(w.p);
        vector2<int> np = w.p + offsets[(w.d) % 4];
        direction nd = w.d;
        if (grid.get_element(np).second == '#') {
            nd = direction((nd + 1) % 4);
            np = w.p + offsets[(nd) % 4];
        }
        if (grid.in_bounds(np)) q.emplace(work{np, nd});
    };
    return visited.size();
};

int64_t sol_b(tbb::grid2d<char>& grid) {
    int64_t pp = 0;
    vector2<int> guard = grid.find_elements('^')[0];
    direction d = north;

    for (int xx = 0; xx <= grid._x; xx++)
        for (int yy = 0; yy <= grid._y; yy++) {
            if (grid.get_element({xx, yy}).second == '.') {
                grid.place_element({xx, yy}, '#');

                std::set<vector2<int>> visited[4];
                std::queue<work> q;
                q.emplace(work{guard, d});
                while (!q.empty()) {
                    auto w = q.front();
                    q.pop();
                    vector2<int> np = w.p + offsets[(w.d) % 4];
                    direction nd = w.d;
                    if (grid.get_element(np).second == '#') {
                        if (visited[w.d].count(w.p)) {
                            pp++;
                            grid.remove_element({xx, yy});
                            continue;
                        }
                        visited[w.d].emplace(w.p);
                        while (grid.get_element(np).second == '#') {
                            nd = direction((nd + 1) % 4);
                            np = w.p + offsets[(nd) % 4];
                        }
                    };
                    if (grid.in_bounds(np)) q.emplace(work{np, nd});
                };
                grid.remove_element({xx, yy});
            }
        }
    return pp;
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    tbb::grid2d<char> grid;
    grid.read('.');
    return {sol_a(grid), sol_b(grid)};
}