#include <sstream>

#include "../common/lib.h"

auto compare = [](std::string a, std::string b) { return a.size() > b.size(); };

int64_t number_of_designs(std::string design, std::vector<std::string> patterns) {
    int n = design.size();
    std::vector<int64_t> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (auto pattern : patterns) {
            int len = pattern.size();
            if (i >= len && design.substr(i - len, len) == pattern) dp[i] += dp[i - len];
        }
    return dp[n];
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::vector<std::string> pt;
    std::string t;
    while (std::cin >> t) {
        if (t.back() == ',')
            pt.push_back(t.substr(0, t.size() - 1));
        else {
            pt.push_back(t);
            break;
        }
    }
    while (std::cin >> t) {
        auto r = number_of_designs(t, pt);
        if (r > 0) res.first++;
        res.second += r;
    }
    return res;
}