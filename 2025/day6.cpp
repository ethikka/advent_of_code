#include <sstream>
#include <vector>
#include <thread>
#include <cmath>
#include "../common/lib.h"

char get(std::string s, int index) {
    if (index > s.length() - 1) return ' ';
    return s[index];
}

int64_t a(std::vector<std::stringstream>& homework) {
    int64_t res(0);
    while (!homework.at(homework.size() - 1).eof()) {
        int64_t acc(0), tr(0);
        std::vector<int64_t> accb;

        char op;
        homework.at(homework.size() - 1) >> op;
        homework.at(0) >> acc;

        for (int i = 1; i < homework.size() - 1; i++) {
            homework.at(i) >> tr;
            if (op == '*')
                acc *= tr;
            else
                acc += tr;
        }
        res += acc;
    }
    return res;
}

int64_t b(std::vector<std::string>& homework) {
    int64_t res(0);
    char op;

    int max(0);
    for (auto s : homework) max = std::max(max, (int)s.length());

    int64_t acc(0);
    for (int i = 0; i < max; i++) {
        char t = get(homework[homework.size() - 1], i);
        if (t != ' ') op = t;
        int64_t tmp(0);

        for (int c = 0; c < homework.size() - 1; c++) {
            if (get(homework[c], i) != ' ') {
                if (!tmp) {
                    tmp = (get(homework[c], i) - '0');
                } else {
                    tmp *= 10;
                    tmp += (get(homework[c], i) - '0');
                }
            }
        }
        if (!tmp) {
            res += acc;
            acc = 0;
        } else {
            if (!acc)
                acc = tmp;
            else if (op == '*')
                acc *= tmp;
            else
                acc += tmp;
        }
    }

    return res + acc;
}

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::string line;
    std::vector<std::stringstream> homework;
    std::vector<std::string> homework_b;
    while (std::getline(std::cin, line)) {
        homework.push_back(std::stringstream(line));
        homework_b.push_back(line);
    }
    return {a(homework), b(homework_b)};
}