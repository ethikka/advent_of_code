#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include "../common/lib.h"

class vm {
   private:
    int64_t initial_a;
    std::map<char, int64_t> registers;

    int64_t rr(int ov) {
        // clang-format off
        if (ov == 4)      return registers['A'];
        else if (ov == 5) return registers['B'];
        else if (ov == 6) return registers['C'];
        else              return ov;
        // clang-format on
    };

   public:
    vm(int64_t a, int64_t b, int64_t c) {
        initial_a = a;
        registers['A'] = a;
        registers['B'] = b;
        registers['C'] = c;
    }
    std::string run(std::string instructions, bool part_a) {
        std::string outputstr;
        std::vector<int> inst;
        std::vector<int> output;
        for (int i = 0; i < instructions.size(); i = i + 2) inst.push_back(instructions[i] - '0');

        int ip(0);
        while (ip < inst.size()) {
            // clang-format off
            switch (inst.at(ip)) {
/* adv */       case 0: registers['A'] /= (std::pow(2, rr(inst.at(ip + 1)))); break;
/* bxl */       case 1: registers['B'] ^= inst.at(ip + 1); break;
/* bst */       case 2: registers['B'] = rr(inst.at(ip + 1)) % 8; break;
/* jnz */       case 3: if (registers['A'] != 0) ip = inst.at(ip + 1)-2; break; 
/* bxc */       case 4: registers['B'] ^= registers['C']; break;
/* out */       case 5: output.push_back(rr(inst.at(ip + 1)) % 8); break;
/* bdv */       case 6: registers['B'] = registers['A']/(std::pow(2, rr(inst.at(ip + 1)))); break;
/* cdv */       case 7: registers['C'] = registers['A']/(std::pow(2, rr(inst.at(ip + 1)))); break;
            }
            // clang-format om
            ip += 2;
        }
        for (int i = 0; i < output.size(); i++) outputstr = outputstr + (i == 0? "": ",") + (char)(output.at(i)+'0');
        if (part_a) std::cout << outputstr << std::endl;
        if (instructions.ends_with(outputstr)) return outputstr;
        return "";
    }
};

int64_t bf(std::string instructions) {
      int64_t n;
      for (int64_t i = 0; i < 100000000000000000; i++) {
        auto v = vm(i, 0, 0);
        auto r = v.run(instructions, false);
        if (r == instructions) return i;
        if (r.size() > instructions.size()) return -1;
        if (r.size() > 0) i = (i*8)-8;
      }
      return 0;
};

std::pair<std::uintmax_t, std::uintmax_t> solve() {
    std::string i;
    int64_t a, b, c;
    std::cin >> i >> i >> a >> i >> i >> b >> i >> i >> c >> i >> i;
    auto v = vm(a, b, c);
    std::cout << v.run(i, true) << std::endl;
 
    return {0, bf(i)};
}