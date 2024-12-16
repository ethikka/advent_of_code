#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../common/lib.h"

class elephant_math {
   private:
    int64_t result;
    std::vector<int> numbers;
    int64_t bt(int64_t res, int curr_idx) {
        if (curr_idx != numbers.size()) {
            res += numbers[curr_idx];
            if (!bt(res, curr_idx + 1)) {
                res = (res - numbers[curr_idx]) * numbers[curr_idx];
                if (!bt(res, curr_idx + 1)) return 0;
            }
        } else if (res != result)
            return 0;
        return result;
    }

    int64_t bt2(int64_t res, int curr_idx) {
        if (curr_idx != numbers.size()) {
            res += numbers[curr_idx];
            if (!bt2(res, curr_idx + 1)) {
                res = (res - numbers[curr_idx]) * numbers[curr_idx];
                if (!bt2(res, curr_idx + 1)) {
                    res /= numbers[curr_idx];
                    std::string cat =
                        std::to_string(res) + std::to_string(numbers[curr_idx]);
                    if (cat.length() < 20) {
                        res = stoll(cat);
                        if (!bt2(res, curr_idx + 1)) return 0;
                    } else
                        return 0;
                }
            }
        } else if (res != result)
            return 0;
        return result;
    }

   public:
    elephant_math(std::string input) {
        std::istringstream ssl(input);
        char d;
        int tmp;
        ssl >> result >> d;
        while (!ssl.eof()) {
            ssl >> tmp;
            numbers.push_back(tmp);
        }
    }

    int64_t can_solve_a() { return bt(0, 0); }
    int64_t can_solve_b() { return bt2(0, 0); }
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::string line;

    std::vector<elephant_math> equations;
    while (std::getline(std::cin, line))
        equations.push_back(elephant_math(line));
    for (auto e : equations) {
        res.first += e.can_solve_a();
        res.second += e.can_solve_b();
    }

    return res;
}