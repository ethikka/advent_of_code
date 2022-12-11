#include <sstream>
#include <vector>
#include <set>
#include <functional>
#include "../common/lib.h"

struct monkey {
  monkey() { inspection_counter = 0; mult = 1; addi = 0; read_input(); };
  std::vector<int64_t> items;
  int mult, addi, test__divisible_by, target_true, target_false, pow;
  std::int64_t inspection_counter;
  void read_input() {
    std::string line;
    std::getline(std::cin, line);
    std::getline(std::cin, line); std::istringstream s(line.substr(18)); while (std::getline(s, line, ',')) items.push_back(std::stoi(line));     
    std::getline(std::cin, line); if      (line[23] == '+') addi = std::stoi(line.substr(line.size()-2));
                                  else if (line[25] != 'o') mult = std::stoi(line.substr(line.size()-2));
    std::getline(std::cin, line); test__divisible_by = std::stoi(line.substr(line.size()-2));
    std::getline(std::cin, line); target_true  = std::stoi(line.substr(line.size()-1));
    std::getline(std::cin, line); target_false = std::stoi(line.substr(line.size()-1));
    std::getline(std::cin, line);
  };
};

int64_t round(std::vector<monkey> monkeys, int rounds, int64_t divider) {
  for(int c = 0; c < rounds; c++) 
    for(auto &m: monkeys) {
      for (int i = 0; i < m.items.size(); i++) {
        m.items[i] = (m.items[i]*m.mult) + m.addi;
        if (!m.addi && m.mult == 1) m.items[i] *= m.items[i]; 

        m.items[i] = (divider == 3) ? m.items[i] / divider: (m.items[i] % divider) + divider; 
        m.inspection_counter++;
        monkeys.at(((m.items[i] % m.test__divisible_by) == 0) ? m.target_true : m.target_false).items.push_back(m.items[i]);
      }
      m.items.clear();
    }

  std::set<int64_t> ic;
  for (auto m: monkeys) ic.emplace(m.inspection_counter); 
  
  int c(0);
  int64_t res = 1;
  for(auto i = ic.rbegin(); c < 2; c++) res *= *(i++);
  return res;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::vector<monkey> mb;
  while (!std::cin.eof()) mb.push_back(monkey());

  int64_t dv(1);
  for (auto m: mb) dv *= m.test__divisible_by;
  return { round(mb, 20, 3), round(mb, 10000, dv) };
}