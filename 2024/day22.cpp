#include <sstream>
#include <set>
#include <map>
#include "../common/lib.h"

int64_t prune(int64_t a) { return a % 16777216; };
int64_t mix(int64_t a, int64_t b) { return a ^ b; };

std::map<uint64_t, uint64_t> bananas;

int64_t mutate(int64_t input, int cycle) {
    int64_t r(input);
    std::map<uint64_t, bool> v;
    int p = (input % 10), c(0);
    for (int cnt = 0; cnt < cycle; cnt++) {
        r = prune(mix(r, r * 64));
        r = prune(mix(r, std::floor(r / 32)));
        r = prune(mix(r, r * 2048));
        int np = (r % 10);
        int d = np - p + 9;  // transpose -9..9 to 0..19
        p = np;
        c = (c * 19 + d) % 130321;  // 130321 = 19*19*19*19
        if (!v[c]) {
            v[c] = true;
            bananas[c] += p;
        }
    }
    return r;
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    int64_t i;
    while (std::cin >> i) res.first += mutate(i, 2000);
    for (auto l : bananas)
        if (l.second > res.second) res.second = l.second;
    return res;
}