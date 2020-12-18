#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

void tokenize(std::string const &str, std::vector<std::string> &out)
{
    int start, end(0);
    while ((start = str.find_first_not_of(" ", end)) != std::string::npos) {
        end = str.find(" ", start);
        out.push_back(str.substr(start, end - start));
    }
}

int64_t calc(std::string expression, bool part_b) {
  std::vector<std::string> tokens;
  tokenize(expression, tokens);
  int64_t val(0);
  if (!part_b) {
    val = std::stoi(tokens[0]);
    for (int i = 1; i < tokens.size(); i++) {
      if      (tokens[i] == "+") val += std::stoi(tokens[++i]);
      else if (tokens[i] == "*") val *= std::stoi(tokens[++i]);
    }
  } else { // part b
    // zoek "{x} + {y}" in de token lijst en vervangen door "1 * {x+y}"
    while (std::find(tokens.begin(), tokens.end(), "+") != tokens.end()) {
      int idx = std::distance(tokens.begin(), std::find(tokens.begin(), tokens.end(), "+"));
      tokens[idx-1] = "1";
      tokens[idx] = "*";
      tokens[idx+1] = std::to_string(std::stoi(tokens[idx-1]) + std::stoi(tokens[idx+1]));
    }
    val = std::stoi(tokens[0]);
    for (int i = 2; i < tokens.size(); i += 2) 
      val *= std::stoi(tokens[i]);
  }
  return val;
}

int64_t eval(std::string expression, bool part_b) {
  std::string exp(expression);
  int ebrace(0);

  while (exp.find(')') != std::string::npos) {
    int ebrace(exp.find(')')), bbrace(ebrace);
    while (exp[bbrace] != '(') bbrace--;
    exp = exp.substr(0, bbrace)+std::to_string(eval(exp.substr(bbrace+1, ebrace-bbrace-1), part_b))+exp.substr(ebrace+1);
  }
  return calc(exp, part_b);
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
	while(std::getline(std::cin, line)) {
    res.first += eval(line, false);
    res.second += eval(line, true);
  }
  return res;
}