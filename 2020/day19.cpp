#include <sstream>
#include <map>
#include "../common/lib.h"
#include <regex>

std::map<int,std::string> rules;
std::vector<std::string> strings;

std::string generate_regex(int rule, bool part_2)
{
  std::string res("(");

  // 8: 42 | 42 8 => Match a continuous sequence of "42"s
  if (rule == 8 && part_2)     
    return '(' + generate_regex(42, part_2) + "+)";

  // 11: 42 31 | 42 11 31	=> match an equal amount of 42s and 31s next to each other, where amount is at least 1
  if (rule == 11 && part_2) { 
    for(int i = 1; i < 5; ++i) // maximum amount of nests is 5 (rule 41 and 31 become 8 characters for my input, longest input is 88 charachters, 6 sets would be 96 characters and thus impossible)
      res += generate_regex(42, part_2) + '{' + std::to_string(i) + '}' + generate_regex(31, part_2) + '{'+ std::to_string(i) + "}|";
    return res.substr(0, res.size()-1)+')';
  }

  std::stringstream cur_rule(rules[rule]);
  std::string token;
  while(cur_rule >> token)
    res += (std::isdigit(token[0]) ? generate_regex(std::stoi(token), part_2): token);

  return res + ')';
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;

  // read rules	
  while(std::getline(std::cin, line) && line.size() )
  {
    int pos = line.find_first_of(':');
    int num = std::stoi(line.substr(0, pos));
    std::string rule = line.substr(pos + 2);
    rule.erase(std::remove(rule.begin(), rule.end(), '\"'), rule.end());
    rules[num] = rule;
  };
  // read strings
  while(std::cin >> line) strings.push_back(line);

  std::regex part_1(generate_regex(0, false));
  std::regex part_2(generate_regex(0, true));

  for(auto s: strings) {
    res.first += std::regex_match(s, part_1);
    res.second += std::regex_match(s, part_2);
  }

  return res;
}