#include <sstream>
#include <vector>
#include "../common/lib.h"

int64_t get_top_n(std::vector<int> inp, int n) {
    std::vector<int> best(inp);
    while (best.size() > n) {
        // find first digit that has an increasing digit after it and remove it
        int idx(0);
        bool done(false);
        while (++idx < (best.size() - 1) && !done) {
            if (best.at(idx - 1) < best.at(idx)) {
                best.erase(best.begin() + idx - 1);
                done = true;
            }
        }
        if (!done && best.size() > n) best.erase(best.begin() + best.size() - 1);
    }
    int64_t res(0);
    for (auto i : best) res = (res * 10) + i;
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> inp;
        for (char c : line) inp.push_back(c - '0');
        res.first += get_top_n(inp, 2);
        res.second += get_top_n(inp, 12);
    }
    return res;
}