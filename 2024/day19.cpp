#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <thread>

#include "../common/lib.h"

auto compare = [](std::string a, std::string b) { return a.size() > b.size(); };

class towel {
   private:
    std::string code;
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

   public:
    towel(std::string c) { code = c; };
    int64_t count_designs(std::vector<std::string> pt) { return number_of_designs(code, pt); };
    bool is_valid(std::vector<std::string> pt) {
        std::priority_queue<std::string, std::vector<std::string>, decltype(compare)> w;
        w.emplace(code);
        while (!w.empty()) {
            auto s = w.top();
            w.pop();
            if (s == "") return true;
            for (auto p : pt)
                if (s.ends_with(p)) w.emplace(s.substr(0, s.size() - p.size()));
        }
        return false;
    };
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::vector<std::string> pt;
    std::vector<towel> towels;
    std::string t;
    while (std::cin >> t) {
        if (t.back() == ',')
            pt.push_back(t.substr(0, t.size() - 1));
        else {
            pt.push_back(t);
            break;
        }
    }
    while (std::cin >> t) towels.push_back(towel(t));

    for (auto t : towels) {
        if (t.is_valid(pt)) res.first++;
        res.second += t.count_designs(pt);
    }
    return res;
}