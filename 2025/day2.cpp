#include <sstream>
#include <set>
#include <regex>
#include "../common/lib.h"

int64_t find_invalid_ids(const std::vector<std::pair<int64_t, int64_t>>& pairs, const std::string& regex) {
    const std::regex repeat_regex(regex);
    int64_t sum{0};

    for (const auto& pair : pairs) {
        for (int64_t num = pair.first; num <= pair.second; num++) {
            auto check_str = std::to_string(num);
            auto check_begin = std::sregex_iterator(check_str.begin(), check_str.end(), repeat_regex);
            auto check_end = std::sregex_iterator();

            for (std::sregex_iterator i = check_begin; i != check_end; ++i) {
                const std::smatch& match = *i;

                if (!match.empty()) {
                    sum += num;
                }
            }
        }
    }
    return sum;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::vector<std::pair<int64_t, int64_t>> pairs;
    while (!std::cin.eof()) {
        int64_t s, e;
        char d;
        std::cin >> s >> d >> e >> d;
        pairs.emplace_back(s, e);
    }
    return {find_invalid_ids(pairs, "(^\\d+)+\\1$"), find_invalid_ids(pairs, "(^\\d+)+\\1{1,}$")};
}