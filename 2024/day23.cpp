#include <sstream>
#include <map>
#include <set>
#include <vector>
#include "../common/lib.h"

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::map<std::string, std::set<std::string>> network;
    std::string inp, c1, c2;
    while (std::cin >> inp) {
        c1 = inp.substr(0, 2);
        c2 = inp.substr(3);
        network[c1].emplace(c2);
        network[c2].emplace(c1);
    }
    std::set<std::set<std::string>> r;
    // clang-format off
    for (auto [k, v]: network) 
        if (k[0] == 't')
            for (auto s: v) for (auto t: network[s]) for (auto u: network[t])
                if (u == k)
                    r.emplace(std::set<std::string>{k, s, t});
    // clang-format on

    for (auto n : network) network[n.first].emplace(n.first);  // add own nodes to network for part 2

    size_t best = 0;
    std::set<std::string> ls;
    for (auto [k, v] : network) {
        std::set<std::string> c(v.begin(), v.end());
        for (const auto& ele : v) {
            if (!c.contains(ele)) continue;
            std::vector<std::string> inter, tmp2;
            std::set_intersection(v.begin(), v.end(), network[ele].begin(), network[ele].end(), std::back_inserter(inter));
            std::set_intersection(inter.begin(), inter.end(), c.begin(), c.end(), std::back_inserter(tmp2));
            c.clear();
            c.insert(tmp2.begin(), tmp2.end());
        }
        if (c.size() > best) {
            best = c.size();
            ls = c;
        }
    }
    std::string password;
    for (auto m : ls) password += (password.size() == 0 ? "" : ",") + m;
    std::cout << password << std::endl;
    return {r.size(), 0};
}