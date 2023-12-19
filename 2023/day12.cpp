#include <sstream>
#include <vector>
#include <unordered_map>
#include "../common/lib.h"

int64_t count(const std::string& s, int i, int j, int len, const std::vector<int>& group, std::unordered_map<std::string, int64_t>& cache) {
  if (j == group.size() || (j == group.size() - 1 && group[j] == len)) return (s.length() == i || s.find("#", i) == std::string::npos) ? 1 : 0;
  if (i == s.length()) return 0;

  std::string key = std::to_string(i) + "-" + std::to_string(len) + "-" + std::to_string(j);
  if (cache.find(key) != cache.end()) return cache[key];

  int64_t res = 0;
  if (len == group[j] && (s[i] == '.' || s[i] == '?')) 
    res = count(s, i + 1, j + 1, 0, group, cache);
  else if (len == 0) {
    if (s[i] == '?') {
      int64_t c1 = count(s, i + 1, j, 1, group, cache);
      int64_t c2 = count(s, i + 1, j, 0, group, cache);
      res = c1 + c2;
    } else if (s[i] == '#') 
      res = count(s, i + 1, j, 1, group, cache);
    else
      res = count(s, i + 1, j, 0, group, cache);
  } else if (s[i] == '#' || s[i] == '?') 
    res = count(s, i + 1, j, len + 1, group, cache);
  cache[key] = res;
  return res;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  int64_t answer = 0;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string part, groupStr;
    iss >> part >> groupStr;

    std::istringstream groupStream(groupStr);
    std::vector<int> groups;
    std::string groupSize;
    while (std::getline(groupStream, groupSize, ',')) groups.push_back(std::stoi(groupSize));

    std::unordered_map<std::string, int64_t> cache;
    res.first += count(part, 0, 0, 0, groups, cache);

    std::string s2 = part; for (int i = 1; i < 5; ++i) s2 += "?"+part;
    std::vector<int> expandedGroups = groups;
    for (int i = 1; i < 5; ++i) expandedGroups.insert(expandedGroups.end(), groups.begin(), groups.end());
    std::unordered_map<std::string, int64_t> cache_b;
    res.second += count(s2, 0, 0, 0, expandedGroups, cache_b);
  }
  return res;
}