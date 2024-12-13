#include <sstream>
#include <vector>

#include "../common/vector2.h"
#include "../common/lib.h"

class claw {
   private:
    vector2<int64_t> a{0, 0};
    vector2<int64_t> b{0, 0};
    vector2<int64_t> t{0, 0};

   public:
    claw() {
        // clang-format off
        std::string i;
        std::cin >> i >> i >> i; a.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;           a.y = std::stoi(i.substr(2));
        std::cin >> i >> i >> i; b.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;           b.y = std::stoi(i.substr(2));
        std::cin >> i >> i;      t.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;           t.y = std::stoi(i.substr(2));
        // clang-format on
    };

    int64_t optimum(int64_t offset = 0) {
        // https://en.wikipedia.org/wiki/Cramer's_rule#Explicit_formulas_for_small_systems
        // __         __   __       __     __         --
        // |  a.x  b.x |   | press_a |     |  t.x |
        // |  a.y  b.y | x | press_b |  =  |  t.y |
        // --         --   --       --     --         --

        double det_norm = (a.x * b.y - b.x * a.y) * 1.0;
        double x = ((t.x + offset) * b.y - (t.y + offset) * b.x) * 1.0 / det_norm;
        double y = ((t.y + offset) * a.x - (t.x + offset) * a.y) * 1.0 / det_norm;

        // if either x or y are not an exact integer it's not valid
        if (std::trunc(x) == x && std::trunc(y) == y) return 3 * x + y;
        return 0;
    }
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    while (!std::cin.eof()) {
        auto cl = claw();
        res.first += cl.optimum();
        res.second += cl.optimum(10000000000000);
    }
    return res;
}