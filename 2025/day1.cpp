#include <sstream>
#include "../common/lib.h"

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::string line;
    int n(50);

    while (std::cin >> line) {
        int dd = std::stoi(line.substr(1));
        int m = (line[0] == 'L') ? -1 : 1;
        for (int i = 0; i < dd; i++) {
            n = (n + m) % 100;
            if (n == 0) res.second++;
        }
        if (n == 0) res.first++;
    }
    return res;
}