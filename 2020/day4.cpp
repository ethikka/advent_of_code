#include <sstream>
#include <vector>
#include <map>
#include "../common/lib.h"

bool between(std::string input, int min, int max) {
  int inp = std::stoi(input);
  return (inp >= min && inp <= max);
}

bool checkhgt(std::string input) {
  int pos = input.length()-2;
  if (input.substr(pos, 2) == "cm")
    return between(input.substr(0, pos), 150, 193);
  else
    return between(input.substr(0, pos), 59, 76);
}

bool checkhcl(std::string input) {
  if (input.size() != 7) return false;
  for (int i = 1; i < input.size(); i++)
    if (!isxdigit(input[i]))
      return false;
  return true;
}

bool checkecl(std::string input) {
  std::string colors =  " amb blu brn gry grn hzl oth ";
  return colors.find(" "+input+" ") != std::string::npos;
}

bool checkpid(std::string input) {
  if (input.size() != 9) return false;
  for (int i = 0; i < input.size(); i++)
    if (!isdigit(input[i]))
      return false;
  return true;
}

struct passport {
  std::map<std::string,std::string> properties;
  bool isValid() {
    return ((properties.size() == 7) && properties.count("cid") == 0) || (properties.size() == 8);
  }
  bool isValid2() {
    return (((properties.size() == 7) && properties.count("cid") == 0) || (properties.size() == 8))
           && between(properties["byr"], 1920, 2002) 
           && between(properties["iyr"], 2010, 2020) 
           && between(properties["eyr"], 2020, 2030) 
           && checkhgt(properties["hgt"]) 
           && checkhcl(properties["hcl"]) 
           && checkecl(properties["ecl"]) 
           && checkpid(properties["pid"])
           ;
  }
  void clear() { properties.clear(); }
  void add(std::string propname, std::string propvalue) { properties[propname] = propvalue; }
};

std::pair<int,int> solve() {
  std::pair<int,int> res;
  std::string line;
  passport newpass;
  while (std::getline(std::cin, line)) {
    if (line.length() == 0) {
      if (newpass.isValid()) res.first++;
      if (newpass.isValid2()) res.second++;
      newpass.clear();
    } else {
      std::stringstream sl(line);
      std::string prop;
      while (sl >> prop) {
        int pos = prop.find(':');
        newpass.add(prop.substr(0, pos), prop.substr(pos+1));
      }
    }
  }
  if (newpass.isValid()) res.first++;
  if (newpass.isValid2()) res.second++;
  return res;
}

int main(void) {
  post_solve(solve());
}
