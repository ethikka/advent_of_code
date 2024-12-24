#include <sstream>
#include <vector>
#include <map>

#include "../common/lib.h"

struct instr {
    std::string g1;
    std::string g2;
    std::string op;
    std::string og;
    std::string to_string() { return g1 + " " + op + " " + g2 + " -> " + og; }
};

int64_t sim(std::map<std::string, bool> reg, std::vector<instr> instructions) {
    std::vector<instr> i(instructions);

    auto it = i.begin();
    while (i.size() > 0) {
        if (reg.find(it->g1) != reg.end() && reg.find(it->g2) != reg.end()) {
            if (it->op == "AND") reg[it->og] = (reg[it->g1] && reg[it->g2]);
            if (it->op == "OR") reg[it->og] = (reg[it->g1] || reg[it->g2]);
            if (it->op == "XOR") reg[it->og] = (reg[it->g1] != reg[it->g2]);
            i.erase(it);
            it = i.begin();
        } else
            it = std::next(it);
    }
    int64_t res(0), mul(1);
    for (auto r : reg) {
        if (r.first.starts_with('z')) {
            res += (mul * r.second);
            mul *= 2;
        }
    }
    return res;
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::map<std::string, bool> reg;
    std::vector<instr> instructions;
    std::string g, init, op, g2, og;
    while (std::cin >> g >> init)
        if (g.ends_with(':'))
            reg[g.substr(0, g.size() - 1)] = (init == "1");
        else {
            std::cin >> g2 >> og >> og;
            instructions.push_back({(g < g2 ? g : g2), (g < g2 ? g2 : g), init, og});
            continue;
        }
    while (std::cin >> g >> op >> g2 >> op >> og >> og) instructions.push_back({(g < g2 ? g : g2), (g < g2 ? g2 : g), op, og});

    return {sim(reg, instructions), 0};
}