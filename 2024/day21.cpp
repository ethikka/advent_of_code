#include <sstream>
#include <map>
#include <vector>
#include <queue>

#include "../common/lib.h"

std::map<uint64_t, int64_t> memo;

struct Visit {
    int r, c;
    std::string presses;
};

int64_t cheapestRobot(const std::string& presses, int nr);

uint64_t hash(int cr, int cc, int dr, int dc, int nr) { return (((((((cr * 4) + cc) * 4) + dr) * 4) + dc) * 30) + nr; }

int64_t cheapestDirPad(int cr, int cc, int dr, int dc, int nr) {
    uint64_t h = hash(cr, cc, dr, dc, nr);
    auto it = memo.find(h);
    if (it != memo.end()) return it->second;

    int64_t answer = 99999999999999;
    std::deque<Visit> q;
    q.push_back({cr, cc, ""});
    while (!q.empty()) {
        auto v = q.front();
        q.pop_front();
        if (v.r == dr && v.c == dc) {
            int64_t rec = cheapestRobot(v.presses + "A", nr - 1);
            answer = std::min(answer, rec);
            continue;
        }
        // clang-format off
        if (v.r == 0 && v.c == 0) continue; // dont use the empty space on 
        else { if (v.r < dr) { q.push_back({v.r + 1, v.c, v.presses + "v"}); } else
               if (v.r > dr) { q.push_back({v.r - 1, v.c, v.presses + "^"}); }
               if (v.c < dc) { q.push_back({v.r, v.c + 1, v.presses + ">"}); } else
               if (v.c > dc) { q.push_back({v.r, v.c - 1, v.presses + "<"}); }}
        // clang-format on
    }
    memo[h] = answer;
    return answer;
}

int64_t cheapestRobot(const std::string& presses, int nur) {
    if (nur == 1) return presses.length();

    int cr(0), cc(2);
    int64_t result = 0;
    std::string padConfig = "X^A<v>";

    for (int i = 0; i < presses.length(); i++)
        for (int nr = 0; nr < 2; nr++)
            for (int nc = 0; nc < 3; nc++)
                if (padConfig[nr * 3 + nc] == presses[i]) {
                    result += cheapestDirPad(cr, cc, nr, nc, nur);
                    cr = nr;
                    cc = nc;
                }
    return result;
}

int64_t cheapest(int cr, int cc, int dr, int dc, int depth) {
    int64_t answer = 99999999999999;
    std::deque<Visit> q;
    q.push_back({cr, cc, ""});
    while (!q.empty()) {
        auto v = q.front();
        q.pop_front();
        if (v.r == dr && v.c == dc) {
            int64_t rec = cheapestRobot(v.presses + "A", depth);
            answer = std::min(answer, rec);
            continue;
        }
        // clang-format off
        if (v.r == 3 && v.c == 0) continue;
        else { if (v.r < dr) { q.push_back({v.r + 1, v.c, v.presses + "v"}); } else 
               if (v.r > dr) { q.push_back({v.r - 1, v.c, v.presses + "^"}); }
               if (v.c < dc) { q.push_back({v.r, v.c + 1, v.presses + ">"}); } else
               if (v.c > dc) { q.push_back({v.r, v.c - 1, v.presses + "<"}); }
        }
        // clang-format on
    }
    return answer;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::pair<std::uintmax_t, std::uintmax_t> res;
    std::string s;
    while (std::cin >> s) {
        int64_t result_a(0), result_b(0);
        std::string padConfig = "789456123X0A";
        int cr = 3;
        int cc = 2;
        for (int i = 0; i < s.length(); i++)
            for (int nr = 0; nr < 4; nr++)
                for (int nc = 0; nc < 3; nc++)
                    if (padConfig[nr * 3 + nc] == s[i]) {
                        result_a += cheapest(cr, cc, nr, nc, 3);
                        result_b += cheapest(cr, cc, nr, nc, 26);
                        cr = nr;
                        cc = nc;
                    }

        int code = std::stoi(s.substr(0, s.size() - 1));
        res.first += result_a * code;
        res.second += result_b * code;
    }
    return res;
}