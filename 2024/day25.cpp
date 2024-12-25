#include <sstream>

#include "../common/grid2d.h"
#include "../common/lib.h"

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::vector<std::string> keys_locks[2];

    while (!std::cin.eof()) {
        tbb::grid2d<char> g;
        g.read('.');
        bool is_key = !g.has_element({0, 0});
        std::string code;
        std::vector<int> res;
        while (res.size() < 5) {
            int v(0), rs = res.size();
            // clang-format off
            if (is_key) { for (int i = 5; i > 0; i--) if (g.has_element({rs, i})) v++; } 
            else {        for (int i = 1; i < 6; i++) if (g.has_element({rs, i})) v++; }
            // clang-format on
            res.push_back(v);
        }
        for (auto i : res)
            code += i + '0';
        keys_locks[is_key].push_back(code);
    }

    for (auto key : keys_locks[true])
        for (auto lock : keys_locks[false]) {
            bool valid(true);
            for (int i = 0; i < 5; i++)
                valid &= ((key[i] - '0') + (lock[i] - '0') <= 5);
            if (valid) res.first++;
        }
    return res;
}