#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <utility>

#include "../common/grid2d.h"
#include "../common/vector2.h"
#include "../common/lib.h"

struct work {
    vector2<int> pos;
    direction facing;
    int64_t score;
    std::vector<vector2<int>> history;
    bool operator<(const work &compare_to) const { return score > compare_to.score; }
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    tbb::grid2d<char> grid;
    grid.read('.');
    vector2<int> end = grid.find_elements('E')[0];

    std::priority_queue<work> path;
    std::map<std::pair<vector2<int>, direction>, int64_t> visited;
    std::map<int64_t, std::set<vector2<int>>> seating;

    path.push({grid.find_elements('S')[0], east, 0});
    while (!path.empty()) {
        work w = path.top();
        w.history.push_back(w.pos);
        path.pop();
        if (grid[w.pos].second == '#') continue;
        if (w.score <= visited[{w.pos, w.facing}] || visited[{w.pos, w.facing}] == 0) {
            if (w.pos == end)
                for (auto p : w.history) seating[w.score].emplace(p);
            visited[{w.pos, w.facing}] = w.score;
            path.push(work{w.pos + offsets[w.facing], w.facing, w.score + 1, w.history});
            path.push(work{w.pos, ccw(w.facing), w.score + 1000, w.history});
            path.push(work{w.pos, cw(w.facing), w.score + 1000, w.history});
        }
    }

    int64_t res = seating.begin()->first;
    for (auto r : seating)
        if (res > r.first) res = r.first;
    return {res, seating[res].size()};
}