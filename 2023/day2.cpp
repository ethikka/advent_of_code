#include <sstream>
#include <map>
#include <cmath>
#include "../common/lib.h"

int a(std::istringstream input) {
    std::string gamenr, color;
    int num;
    input >> gamenr >> gamenr;
    while (input >> num >> color) 
        if ((color[0] == 'r' && num > 12) || (color[0] == 'g' && num > 13) || (color[0] == 'b' && num > 14)) return 0;
    return std::stoi(gamenr.substr(0, gamenr.size()-1));;
}

int b(std::istringstream input) {
    std::map<char,int> die;
    std::string color;
    int num;
    input >> color >> color;
    while (input >> num >> color) die[color[0]] = std::max(die[color[0]], num);
    return die['r']*die['g']*die['b'];
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  while (!std::cin.eof()) { 
    std::getline(std::cin, line);
    res.first += a(std::istringstream(line));
    res.second += b(std::istringstream(line));
//    res.second += (find_num(line, true, true)*10)+find_num(line, true, false);
  }
  return res;

}