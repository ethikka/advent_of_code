#include <sstream>
#include <thread>
#include <set>

#include "../common/grid2d.h"
#include "../common/lib.h"

int64_t solve_a(tbb::grid2d<char> grid, std::vector<std::string> instructions) {
    int64_t res(0);
    vector2<int> pos = grid.find_elements('@')[0];
    grid.remove_element(pos);

    for (auto line : instructions)
        for (auto m : line) {
            auto o = offsets[dir_to.find(m)];
            auto e = grid.get_element(pos + o);
            grid.wipe_elements('.');
            switch (e.second) {
                case 'O': {
                    auto bo = e.first + o;
                    while (grid.get_element(bo).second == 'O') bo = bo + o;
                    if (grid.get_element(bo).second == '.') {
                        while (bo != pos) {
                            grid.move_element(bo - o, bo);
                            bo = bo - o;
                        }
                        pos = pos + o;
                    }
                    break;
                }
                case '#':
                    break;
                default:
                    pos = pos + o;
            }
        }

    for (auto e : grid.find_elements('O')) res += (e.y * 100) + e.x;
    return res;
}

std::pair<std::set<vector2<int>>, bool> get_move_list(tbb::grid2d<char> grid, vector2<int> start_pos, vector2<int> offset) {
    std::set<vector2<int>> nodes;
    // clang-format off
    switch (grid[start_pos + offset].second) {
        case '[': nodes.emplace(start_pos + offset + vector2<int>{ 1, 0}); break;
        case ']': nodes.emplace(start_pos + offset + vector2<int>{-1, 0}); break;
        case '#': return {nodes, false};
        case '.': return {nodes, true};
    }
    // clang-format on
    nodes.emplace(start_pos + offset);
    for (auto n : nodes) {
        auto rr = get_move_list(grid, n, offset);
        if (!rr.second) return {nodes, false};
        for (auto rn : rr.first) nodes.emplace(rn);
    }
    return {nodes, true};
}

int64_t solve_b(tbb::grid2d<char> ogrid, std::vector<std::string> instructions) {
    tbb::grid2d<char> grid;
    for (auto e : ogrid.get_raw()) {
        vector2<int> npl = {e.first.x * 2, e.first.y}, npr = {(e.first.x * 2) + 1, e.first.y};
        // clang-format off
        switch (e.second) {
            case '@':   grid.place_element(npl, '@'); break;
            case '#': { grid.place_element(npl, '#'); grid.place_element(npr, '#'); break; }
            case 'O': { grid.place_element(npl, '['); grid.place_element(npr, ']'); break; }
        }
        // clang-format on
    }
    int64_t res(0);
    vector2<int> pos = grid.find_elements('@')[0];
    grid.remove_element(pos);

    for (auto line : instructions) {
        for (auto m : line) {
            auto o = offsets[dir_to.find(m)];
            auto e = grid.get_element(pos + o);
            grid.wipe_elements('.');
            // clang-format off
            switch (e.second) {
                case '[':
                case ']':
                    switch (m) {
                        case '^':
                        case 'v': {
                            auto r = get_move_list(grid, pos, o);
                            if (r.second) {
                                std::map<vector2<int>, char> oldvalues;
                                for (auto p : r.first) { oldvalues[p] = grid[p].second; grid.remove_element(p); }
                                for (auto p : r.first) grid.place_element(p + o, oldvalues[p]);
                                pos = pos + o;
                            }
                            break;
                        }
                        case '<':
                        case '>': {
                            auto bo = e.first + o;
                            while (grid.get_element(bo).second == '[' || grid.get_element(bo).second == ']') bo = bo + o;
                            if (grid.get_element(bo).second == '.') {
                                while (bo != pos) { grid.move_element(bo - o, bo); bo = bo - o; }
                                pos = pos + o;
                            }
                            break;
                        }
                    }
                    break;
                case '#': break;
                default:  pos = pos + o;
            }
            // clang-format on
        }
    }
    for (auto e : grid.find_elements('[')) res += (e.y * 100) + e.x;
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    tbb::grid2d<char> grid;
    grid.read('.');

    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(std::cin, line)) instructions.push_back(line);
    return {solve_a(grid, instructions), solve_b(grid, instructions)};
}