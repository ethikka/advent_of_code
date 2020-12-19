#include <sstream>
#include <map>
#include "../common/lib.h"
#include <regex>

std::map<int,std::string> rules;
std::vector<std::string> strings;

std::string generate_regex(int rule, bool part_2)
{
  if(part_2)
  {
    if (rule == 8) // 8: 42 | 42 8 => Match a continuous sequence of "42"s
      return '(' + generate_regex(42, part_2) + "+)";
    if (rule == 11) { // 11: 42 31 | 42 11 31	=> match an equal amount of 42s and 31s next to each other
        std::string res;
        res += '(';
        // my input needs 4 nests, you might want to increase the 4 below ;-)
        // if you increase it to 7 or beyond you need to #define _GLIBCXX_REGEX_STATE_LIMIT 1000000 before you include <regex>
        for(int i = 1; i < 4; ++i)
          res += generate_regex(42, part_2) + '{' + std::to_string(i) + '}' + generate_regex(31, part_2) + '{'+ std::to_string(i) + '}' + '|';
        res += generate_regex(42, part_2) + generate_regex(31, part_2) + ')';
        return res;
    }
  }

  std::stringstream cur_rule(rules[rule]);
  std::string res;
  std::string token;
  while( cur_rule >> token )
  {
    if(std::isdigit(token[0]))
      res += generate_regex(std::stoi(token), part_2);
    else res += token;
  }
  return '(' + res + ')';
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;

  // read rules	
  while(std::getline(std::cin, line) && line.size() )
  {
    int pos = line.find_first_of(':');
    int num = std::stoull(line.substr(0, pos));
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