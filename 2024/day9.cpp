#include <sstream>
#include <vector>

#include "../common/lib.h"

int64_t crc(std::string input, bool part_b) {
    std::istringstream ssl(input);
    std::vector<std::pair<int64_t, int>> map;
    char c;

    int64_t id = 0;
    bool f(true);
    while (ssl >> c) {
        map.push_back({f ? id++ : -1, c - '0'});
        f = !f;
    }

    for (int64_t i = map.size() - 1; i >= 0; i--) {
        if (map[i].first == -1) continue;

        for (size_t j = 0; j < i; j++) {
            if (map[j].first != -1 || (part_b && map[j].second < map[i].second))
                continue;

            if (map[j].second == map[i].second)
                std::swap(map[i], map[j]);
            else if (map[j].second > map[i].second) {
                int blocksLeft = map[j].second - map[i].second;
                map[j].second = map[i].second;
                std::swap(map[i], map[j]);
                map.insert(map.begin() + j + 1, {-1, blocksLeft});
            } else if (!part_b) {
                int blocksLeft = map[i].second - map[j].second;
                map[i].second = map[j].second;
                std::swap(map[i], map[j]);
                map.insert(map.begin() + i++, {map[j].first, blocksLeft});
            }
            break;
        }
    }

    int64_t block = 0, out = 0;
    for (size_t i = 0; i < map.size(); i++)
        if (map[i].first == -1)
            block += map[i].second;
        else
            for (int j = 0; j < map[i].second; j++)
                out += map[i].first * block++;
    return out;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::string line;
    std::getline(std::cin, line);
    return {crc(line, true), crc(line, false)};
}