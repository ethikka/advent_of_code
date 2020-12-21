#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "../common/lib.h"

struct ingredient_list {
  std::vector<std::string> ingredients;
  std::vector<std::string> allergens;
};

std::map<std::string, std::vector<int>> possible_allergens;

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;

  std::vector<ingredient_list> il;
  il.push_back({{},{}});
  bool ing(true);
  std::string line;
  while (std::cin >> line) {
    if (line[0] == '(') { ing = false; std::cin >> line; }
    if (!ing) {
      if (line.back() == ')') ing = true; 
      line.pop_back(); 
      std::sort(il.back().ingredients.begin(), il.back().ingredients.end());
      il.back().allergens.push_back(line);
      possible_allergens[line].push_back(il.size()-1);
      if (ing) il.push_back({{},{}});
    } else {
      il.back().ingredients.push_back(line);
    }
  }

  std::map<std::string, std::vector<std::string>> allergen_mappings;
  std::set<std::string> allergens;
  for(auto a: possible_allergens) {
    std::vector<std::string> pa = il.at(a.second.front()).ingredients;
    for (auto i: a.second) {
      std::vector<std::string>::iterator it;
      std::vector<std::string> tmp(200);
      it = std::set_intersection(pa.begin(), pa.end(), il.at(i).ingredients.begin(), il.at(i).ingredients.end(), tmp.begin());
      tmp.resize(it - tmp.begin());
      pa = tmp;
    }
    for(auto a: pa) allergens.insert(a);
    allergen_mappings[a.first] = pa;
  }

  bool not_all_known(true);
  std::set<std::string> skiplist;
  while (not_all_known) {
    std::string alg,name;
    for(auto a: allergen_mappings)
      if (a.second.size() == 1 && skiplist.count(a.first) == 0) {
        alg = a.first;
        name = a.second.front();
        skiplist.insert(alg);
      }

    for(auto& a: allergen_mappings)
      if (a.first != alg) 
        for (int i = a.second.size()-1; i >= 0; i--) 
          if (a.second[i] == name)
            a.second.erase(a.second.begin()+i);

    not_all_known = false;
    for(auto a: allergen_mappings)
      not_all_known |= (a.second.size() > 1);
  }
  std::string res2("");
  for(auto a: allergen_mappings) res2 += a.second.front()+",";
  res2.pop_back();
  if (!output_for_timing)
  std::cout << "Solution part b " << res2 << std::endl;

  for (auto ile: il) for (auto i: ile.ingredients) if (allergens.count(i) == 0) res.first++;

  return res;
}
