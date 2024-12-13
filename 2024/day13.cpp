#include <sstream>
#include <vector>

#include "../common/vector2.h"
#include "../common/lib.h"

class claw {
   private:
    vector2<int64_t> a{0, 0};
    vector2<int64_t> b{0, 0};
    vector2<int64_t> target{0, 0};

   public:
    claw() {
        std::string i;
        std::cin >> i >> i >> i;
        a.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;
        a.y = std::stoi(i.substr(2));
        std::cin >> i >> i >> i;
        b.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;
        b.y = std::stoi(i.substr(2));
        std::cin >> i >> i;
        target.x = std::stoi(i.substr(2, i.size() - 3));
        std::cin >> i;
        target.y = std::stoi(i.substr(2));
    };
    int64_t optimum(int64_t offset = 0) {
        // https://en.wikipedia.org/wiki/Cramer's_rule#Explicit_formulas_for_small_systems
        // __         __   __       __     __         --
        // |  a.x  b.x |   | press_a |     |  target.x |
        // |  a.y  b.y | x | press_b |  =  |  target.y |
        // --         --   --       --     --         --
        int64_t det_norm = a.x * b.y - b.x * a.y;
        int64_t det_x = (target.x + offset) * b.y - (target.y + offset) * b.x;
        double x = (double)det_x / (double)det_norm;
        int64_t det_y = a.x * (target.y + offset) - (target.x + offset) * a.y;
        double y = (double)det_y / (double)det_norm;

        const double EPSILON = std::pow(10, -8);
        if (std::abs(x - std::llround(x)) > EPSILON || std::abs(y - std::llround(y)) > EPSILON) return 0;
        if (x < 0 || y < 0) return 0;
        return 3 * x + y;
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