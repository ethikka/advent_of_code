#include <sstream>
#include <vector>

#include "../common/lib.h"

struct FileInfo {
    int64_t id = 0;
    int blocks;
};

int64_t crc(std::string input, bool part_b) {
    std::istringstream ssl(input);
    std::vector<FileInfo> map;
    char c;

    int64_t id = 0;
    bool f(true);
    while (ssl >> c) {
        map.push_back({f ? id++ : -1, c - '0'});
        f = !f;
    }

    for (int64_t i = map.size() - 1; i >= 0; i--) {
        FileInfo& info = map[i];
        if (info.id == -1) continue;

        for (size_t j = 0; j < i; j++) {
            FileInfo& space = map[j];
            if (space.id != -1 || (part_b && space.blocks < info.blocks))
                continue;

            if (space.blocks == info.blocks)
                std::swap(info, space);
            else if (space.blocks > info.blocks) {
                int blocksLeft = space.blocks - info.blocks;
                space.blocks = info.blocks;
                std::swap(info, space);
                map.insert(map.begin() + j + 1, {-1, blocksLeft});
            } else if (!part_b) {
                int blocksLeft = info.blocks - space.blocks;
                info.blocks = space.blocks;
                std::swap(info, space);
                map.insert(map.begin() + i, {space.id, blocksLeft});
                i++;
            }
            break;
        }
    }

    int64_t block = 0, out = 0;
    for (size_t i = 0; i < map.size(); i++)
        if (map[i].id == -1)
            block += map[i].blocks;
        else
            for (int j = 0; j < map[i].blocks; j++) out += map[i].id * block++;

    return out;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::string line;
    std::getline(std::cin, line);
    return {crc(line, true), crc(line, false)};
}