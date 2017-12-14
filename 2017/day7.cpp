#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <utility>
#include <chrono>

class subprogram;

std::map<std::string,subprogram> container;

class subprogram {
  public:
    std::string name;
    int weight;
    int held_weight;
    std::vector<std::string> holds;
    std::string held_by;

  public:
    subprogram() { }
    subprogram(std::string _name) {
      name = _name;
    }

    bool is_balanced() const {
      int w = container[holds[0]].total_weight();
      bool balanced = true;
      for (auto& key: holds) {
        balanced &= (container[key].total_weight() == w);
      }
      return balanced;
    }

    int total_weight() const {
      return weight+held_weight;
    }

    std::pair<std::string,int> get_unbalanced() {
      std::map<int,std::string> h;
      int ww;
      for(auto& key: holds) {
        int w = container[key].total_weight();
        if (h.count(w) == 0) 
          h[w] = key;
        else
          ww = w;
      }
      for (auto& it: h) 
        if (it.first != ww)
          return std::make_pair(it.second, ww);
      return std::make_pair("", 0);
    }
};

void add_sub_program(std::string _name, int _weight, std::vector<std::string> _holds) {
  if (container.find(_name) == container.end()) {
    container[_name] = subprogram(_name);
  }
  container[_name].weight = _weight;
  container[_name].holds = _holds;
  container[_name].held_weight = 0;

  if (_holds.size() > 0)
    for (auto s: _holds) {
      if (s.size() > 0) {
        if (container.find(s) == container.end()) {
          container[s] = subprogram(s);
        }
        container[s].held_by = _name;
        container[s].held_weight = 0;
      }
    }
}

void solve(void) {
  std::string line;
  std::vector<std::string> lines;
  while (getline(std::cin, line)) 
    lines.push_back(line);

  for(auto& line: lines)
  {
    int idx1 = line.find("(");
    int idx2 = line.find(")");
    std::string linkstext;
    if (line.find("->") != std::string::npos)
      linkstext = line.substr(line.find(" -> ")+4, 255);
    std::string name = line.substr(0, idx1-1);
    int weight = std::stoi(line.substr(idx1+1, idx2-idx1-1));
    std::vector<std::string> links;
    int pos = linkstext.find(",");
    while (pos != std::string::npos)
    {
      links.push_back(linkstext.substr(0, pos));
      linkstext = linkstext.substr(pos+2, 255);
      pos = linkstext.find(",");
    }
    if (linkstext.size() > 0)
      links.push_back(linkstext.substr(0, linkstext.size()-1));
    add_sub_program(name, weight, links);
  }

  std::string rootnode;

  for(auto& i: container) {
    std::string newkey = i.second.held_by;
    while (newkey != "") {
      if (container[newkey].held_by.size() == 0) 
        rootnode = newkey;
      container[newkey].held_weight += i.second.weight;
      newkey = container[newkey].held_by;
    }
  }

  for(auto& i: container) {
    if (i.second.holds.size() > 0) {
      std::string key(i.second.name);
      while(container[key].is_balanced())
        key = container[key].held_by;

      std::string balkey(container[key].get_unbalanced().first);
      while (balkey.size() > 0) {
        key = balkey;
        balkey = container[balkey].get_unbalanced().first;
      }

      auto tup = container[container[key].held_by].get_unbalanced();
      int newweight = (container[tup.first].weight - (container[tup.first].total_weight() - tup.second));
      std::cout << "Solution a: " << rootnode << std::endl;
      std::cout << "Solution b: Node " << container[tup.first].name << "'s new weight is " << newweight << std::endl;
      break;
    }
  }
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

