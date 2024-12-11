#include <sstream>
#include <vector>
#include <map>

#include "../common/lib.h"

std::map<std::pair<int64_t, int>, int64_t> blink_map;

int length(int64_t num) {
    int i = 0;
    while (num > 0) {
        num /= 10;
        i++;
    }
    return i;
}

std::pair<int64_t, int64_t> split(int64_t num, int length) {
    const int64_t mask = pow(10, length / 2);
    return std::make_pair(num / mask, num % mask);
}

int64_t count(const int64_t number, const int blinks_to_go) {
    if (blinks_to_go == 0) return 1;
    int64_t ans;
    auto key = std::make_pair(number, blinks_to_go);
    if (blink_map.count(key) > 0) return blink_map[key];
    if (number == 0) {
        ans = count(1, blinks_to_go - 1);
        blink_map[key] = ans;
    } else {
        int nlen = length(number);
        if (nlen % 2 == 0) {
            auto sp = split(number, nlen);
            ans = count(sp.first, blinks_to_go - 1) + count(sp.second, blinks_to_go - 1);
            blink_map[key] = ans;
        } else {
            ans = count(number * 2024, blinks_to_go - 1);
            blink_map[key] = ans;
        }
    }
    return ans;
}

int64_t count_list(std::vector<int64_t> numbers, int n) {
    int64_t res;
    for (const int64_t i : numbers) res += count(i, n);
    return res;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    int64_t i;
    std::vector<int64_t> numbers;
    while (!std::cin.eof()) {
        std::cin >> i;
        numbers.push_back(i);
    }
    return {count_list(numbers, 25), count_list(numbers, 75)};
}