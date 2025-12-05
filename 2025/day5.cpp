#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

struct range {
    uint64_t min;
    uint64_t max;

    range(int64_t f, int64_t s) {
        min = f;
        max = s;
    }
    bool operator<(const range& b) const {
        return min < b.min;
    }
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::vector<range> fresh_ranges;
    std::string line;
    int64_t id1, id2;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) break;
        std::stringstream ssl(line);
        char d;
        ssl >> id1 >> d >> id2;
        fresh_ranges.emplace_back(range(id1, id2));
    }

    while (std::cin >> id1)
        for (auto r : fresh_ranges)
            if (!(id1 < r.min || id1 > r.max)) {
                res.first++;
                break;
            }

    std::sort(fresh_ranges.begin(), fresh_ranges.end());
    for (auto it = fresh_ranges.begin(); it != fresh_ranges.end();) {
        for (auto it2 = it + 1; it2 != fresh_ranges.end();) {
            if (it->min >= it2->min && it->max <= it2->max) {
                // second completely envelopes first, remove entirely
                it = fresh_ranges.erase(it);
                goto skip;
            }

            if (it->min <= it2->min && it->max >= it2->min) {
                if (it->max >= it2->max) {
                    // first completely envelopes second, remove entirely
                    it2 = fresh_ranges.erase(it2);
                    continue;
                }
                // overwrite start-element of second with start-element of first and remove first
                it2->min = it->min;
                it = fresh_ranges.erase(it);
                goto skip;
            }
            it2++;
        }
        res.second += (it->max - it->min) + 1;
        it++;
    skip:
    }
    return res;
}
