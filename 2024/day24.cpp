#include <sstream>
#include <vector>
#include <map>
#include <set>

#include "../common/lib.h"

struct instr {
    std::string g1;
    std::string g2;
    std::string op;
    std::string og;
    std::string to_string() const { return g1 + " " + op + " " + g2 + " -> " + og; }
};

bool operator<(const instr a, const instr b) { return (a.to_string() < b.to_string()); }

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

std::set<std::string> rewire(std::set<instr> instructions, int count) {
    std::set<std::string> res;
    std::string _xor, _and;
    // clang-format off
    for (auto i : instructions)
        if (i.g1.starts_with('x')) {
            if (i.op == "XOR") {
                if (i.og.starts_with('z')) res.emplace(i.og);
                else                       _xor = i.og;  // ab
            }
            if (i.op == "AND") {
                if (i.og.starts_with('z')) res.emplace(i.og);
                else                       _and = i.og;  // cob
            }
        }

    for (auto i : instructions)
        if (!i.g1.starts_with('x')) {
            if (i.op == "XOR") if (!i.og.starts_with('z')) res.emplace(i.og);
            if (i.op == "AND") if (i.og.starts_with('z'))  res.emplace(i.og); 
            if (i.op == "OR") {
                if (i.og.starts_with('z')) res.emplace(i.og);
                if (_xor == i.g1 || _xor == i.g2) { res.emplace(_and); res.emplace(_xor); }
            }
        }
    // clang-format on
    return res;
}

std::set<instr> get(std::vector<instr> instructions, int n) {
    std::set<instr> res;
    std::string nn = std::to_string(n);
    if (nn.size() == 1) nn = "0" + nn;
    for (auto i : instructions)
        if (i.g1 == "x" + nn || i.g2 == "y" + nn) {
            res.emplace(i);
            for (auto ii : instructions)
                if (ii.g1 == i.og || ii.g2 == i.og) {
                    res.emplace(ii);
                    if (ii.op == "AND")
                        for (auto iii : instructions)
                            if (iii.g1 == ii.og || iii.g2 == ii.og) res.emplace(iii);
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

    std::set<std::string> res_b;
    for (int i = 1; i < 44; i++)
        for (auto s : rewire(get(instructions, i), i)) res_b.emplace(s);

    std::string rb;
    for (auto b : res_b) rb += b + ',';
    std::cout << "Solution part 2: " << rb.substr(0, rb.size() - 1) << std::endl;

    return {sim(reg, instructions), 0};
}