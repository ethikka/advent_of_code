#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <thread>

#include "../common/grid2d.h"
#include "../common/vector2.h"
#include "../common/lib.h"

struct work {
    vector2<int> pos;
    int64_t score;
    std::vector<vector2<int>> history;
    bool operator<(const work &compare_to) const { return score < compare_to.score; }
};

int64_t path(std::vector<vector2<int>> bytes, int size, int number) {
    vector2<int> end = {size - 1, size - 1};
    tbb::grid2d<char> g;
    for (int i = 0; i <= number; i++) g.place_element(bytes.at(i), '#');
    std::queue<work> path;
    std::map<vector2<int>, int64_t> visited;
    std::vector<vector2<int>> best_path;
    path.push({{0, 0}, 0});
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
    std::map<int, int64_t> steps;
    int st(1024), mul(2048);
    while (true) {
        steps[st] = path(bytes, 71, st);
        mul /= 2;
        st += (mul * (steps[st] > 0 ? 1 : -1));
        if (steps.find(st) != steps.end()) {
            if (steps[st] == 0) std::cout << "Part b " << bytes.at(st).to_string() << std::endl;
            if (steps[st + 1] == 0) std::cout << "Part b " << bytes.at(st + 1).to_string() << std::endl;
            return {steps[1024], 0};
        }
    };
    return {0, 0};
}