#include <sstream>
#include <vector>
#include <cmath>
#include "../common/lib.h"

class snailfish_num;

std::vector<snailfish_num*> sfn;

bool found(false);
snailfish_num *finder, *exp_node;

class snailfish_num {
public:  
  int64_t val = -1;
  snailfish_num* parent = NULL;
  snailfish_num* leftidx = NULL;
  snailfish_num* rightidx = NULL;

  snailfish_num(snailfish_num* p1, snailfish_num* p2) { leftidx = p1, rightidx = p2; leftidx->parent = this; rightidx->parent = this; };
  snailfish_num(snailfish_num* p) { this->read(); parent = p; };
  snailfish_num(snailfish_num* p, bool r) { if (r) this->read(); parent = p; };
  snailfish_num(snailfish_num* p, int64_t v) { parent = p; val = v;};

  void print() {
    if (val != -1) std::cout << val;
    else         { std::cout << "["; leftidx->print(); std::cout << ","; rightidx->print(); std::cout << "]"; }
  }

  void read() {
    char c;
    std::cin >> c;
    if (c == '[') {
      leftidx  = new snailfish_num(this); std::cin >> c; // skip ,
      rightidx = new snailfish_num(this); std::cin >> c; // discard closing bracket
    } else if (c != ']') 
      val = (int64_t)(c-48);
  };

  void find_left_val() {
    if (found) return;
    if (exp_node == this) found = true; 
    else if (val != -1) finder = this; 
    else { leftidx->find_left_val(); rightidx->find_left_val(); }
  }

  void find_right_val() {
    if (found) return;
    if (exp_node == this) found = true; 
    else if (val != -1) finder = this; 
    else { rightidx->find_right_val(); leftidx->find_right_val(); }
  }

  bool split() {
    if (val == -1)
      return leftidx->split() || rightidx->split();
    else if (val > 9) {
      leftidx = new snailfish_num(this, (int64_t)floor(val/2.0));
      rightidx = new snailfish_num(this, (int64_t)ceil(val/2.0));
      val = -1;
      return true;
    }
    return false;
  }

  bool explode() {
    if (val != -1) return false;
    bool exp(false);
    int depth(0);
    snailfish_num* ptr = this;
    while (ptr->parent != NULL) {
      ptr = ptr->parent;
      depth++;
    }
    exp = (depth > 3);
    if (exp) {
      exp_node = this; 
      finder = NULL; found = false; ptr->find_left_val();
      if (finder != NULL) finder->val += leftidx->val;
      finder = NULL; found = false; ptr->find_right_val();
      if (finder != NULL) finder->val += rightidx->val;
      leftidx = NULL; rightidx = NULL; val = 0;
      return exp;
    }
    return leftidx->explode() || rightidx->explode();
  }

  int64_t magnitude() {
    if (val != -1) return val;
    return ((leftidx->magnitude()*3) + (rightidx->magnitude()*2));
  }
};

snailfish_num* add(snailfish_num *a, snailfish_num *b) {
  found = false; finder = NULL; exp_node = NULL;
  snailfish_num *sf = new snailfish_num(a, b);
  while (sf->explode() || sf->split());
  return sf;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  snailfish_num *root = new snailfish_num(NULL, true);
  sfn.push_back(root);
  while (std::cin.peek() != EOF) sfn.push_back(new snailfish_num(NULL, true));
  for (int i = 1; i < sfn.size(); i++) root = add(root, sfn[i]);
  res.first = root->magnitude();
/*
  for (int i = 0; i < sfn.size(); i++)
    for (int j = i+1; j < sfn.size(); j++) {
      snailfish_num *p1 = add(sfn[i], sfn[j]); p1->print(); std::cout << std::endl;
      res.second = std::max((std::uintmax_t)p1->magnitude(), res.second);
      snailfish_num *p2 = add(sfn[j], sfn[i]); p2->print(); std::cout << std::endl;
      res.second = std::max((std::uintmax_t)p2->magnitude(), res.second);
    }
*/
  return res;
}