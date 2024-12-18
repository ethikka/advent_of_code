#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <thread>

#include "../common/grid2d.h"
#include "../common/vector2.h"
#include "../common/lib.h"

vector2<int> end;

struct work {
    vector2<int> pos;
    int64_t score;
    std::vector<vector2<int>> history;
    bool operator<(const work &compare_to) const { return score < compare_to.score; }
};

int64_t path(std::vector<vector2<int>> bytes, int size, int number) {
    tbb::grid2d<char> g;
    for (int i = 0; i < number; i++) g.place_element(bytes.at(i) + vector2<int>(1, 1), '#');
    for (int i = -1; i <= size; i++)
        for (auto a : std::vector<vector2<int>>{{i + 1, 0}, {0, i + 1}, {i + 1, size + 1}, {size + 1, i + 1}}) g.place_element(a, '#');
    std::queue<work> path;
    std::map<vector2<int>, int64_t> visited;
    std::vector<vector2<int>> best_path;
    path.push({{1, 1}, 0});
    while (!path.empty()) {
        work w = path.front();
        path.pop();
        w.history.push_back(w.pos);
        if (w.score < visited[w.pos] || visited[w.pos] == 0) {
            if (w.pos.x == size && w.pos.x == size) {
                best_path.clear();
                for (auto e : w.history) best_path.push_back(e);
            }
            visited[w.pos] = w.score;
            for (auto o : offsets)
                if (g.in_bounds(w.pos + o) && (g[w.pos + o].second != '#'))
                    path.push({w.pos + o, w.score + 1, w.history});
        }
    }
    return visited[end];
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    char c;
    int x, y;
    std::vector<vector2<int>> bytes;
    while (std::cin >> x >> c >> y) bytes.push_back(vector2<int>(x, y));
    end = {70 + 1, 70 + 1};
    for (int i = 1025; i < bytes.size(); i++) {
        if (path(bytes, 71, i) == 0) {
            if (path(bytes, 71, i) == 0) {
                if (!output_for_timing)
                    std::cout << "Part b " << bytes.at(i - 1).to_string() << std::endl;
                return {path(bytes, 71, 1024), 0};
            }
        }
    }
    return {0, 0};
}