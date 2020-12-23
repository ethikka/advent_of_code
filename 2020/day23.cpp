#include <sstream>
#include <vector>
#include "../common/lib.h"

struct cup {
  int64_t value;
  cup* left;
  cup* right;
};

std::vector<int> input {3,6,4,2,9,7,5,8,1};

int64_t solver(int pad_to, int rounds, bool part_a) {
  cup* cuplist[1000001];
  cup* first_cup = new cup{input[0], first_cup, first_cup};
  first_cup->left = first_cup; first_cup->right = first_cup;
  cup* current_cup(first_cup);
  cuplist[input[0]] = first_cup;
  for (int i = 1; i < input.size(); i++) {
    cup* new_cup = new cup{input[i], current_cup, current_cup->right};
    current_cup->right = new_cup;
    current_cup = current_cup->right;
    cuplist[input[i]] = current_cup;
  }
  for (int i = input.size()+1; i <= pad_to; i++) {
    cup* new_cup = new cup{i, current_cup, current_cup->right};
    current_cup->right = new_cup;
    current_cup = current_cup->right;
    cuplist[i] = current_cup;
  }

  current_cup = first_cup;
  for (int i = 0; i < rounds; i++) {
    int dest(current_cup->value-1);
    if (dest == 0) dest = pad_to;
    cup* left_cup = current_cup->right;
    current_cup->right = left_cup->right->right->right; // take 3 cups from the circle
    left_cup->right->right->right->left = current_cup;
    // zit dest in de 1 van 3 gepakte cups, doe dan -1 (en in t geval we onder de 1 geraken +9)
    while (   dest == left_cup->value 
           || dest == left_cup->right->value
           || dest == left_cup->right->right->value) {
      dest += (dest <= 1 ? +pad_to-1 : -1);
    }

    cup* dest_cup(cuplist[dest]);
    left_cup->right->right->right = dest_cup->right;
    dest_cup->right->left = left_cup->right->right;
    dest_cup->right = left_cup;
    left_cup->left = dest_cup;
    current_cup = current_cup->right;
  }

  while (current_cup->value != 1)
    current_cup = current_cup->right;
  if (part_a) {
    std::string r("");
    while (current_cup->value != 1 || r == "") {
        r += std::to_string(current_cup->value);
        current_cup = current_cup->right;
    }
    return std::stoull(r.substr(1));
  } else {
    return current_cup->right->value*current_cup->right->right->value;
  }
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  res.first = solver(9, 100, true);
  res.second = solver(1000000, 10000000, false);
  return res;
}