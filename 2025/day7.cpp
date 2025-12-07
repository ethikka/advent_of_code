#include <sstream>
#include <vector>
#include <unordered_map>
#include "../common/lib.h"

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;

    std::vector<std::string> tach;
    std::string line;
    while (std::getline(std::cin, line)) tach.push_back(line);

    std::size_t source{tach[0].find_first_of('S')};
    std::unordered_map<int, int64_t> current{{source, 1}};
    for (int level = 1; level < tach.size(); level++) {
        std::unordered_map<int, int64_t> next;
        for (auto beam : current) {
            if (tach[level][beam.first] == '^') {
                next[beam.first - 1] += beam.second;
                next[beam.first + 1] += beam.second;
                res.first++;
            } else
                next[beam.first] += beam.second;
        }
        current = next;
    }

    for (auto beam : current) res.second += beam.second;
    return res;
}
