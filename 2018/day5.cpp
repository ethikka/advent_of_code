#include <sstream>
#include <iostream>
#include <string>
#include <chrono>

class unit;

class unit {
  public:
    char c;
    unit *prev;
    unit *next;
    unit *orig_prev;
    unit *orig_next;
  public:
    unit() { next = orig_next = prev = orig_prev = 0; }

    unit* add(unit *u) { 
      orig_next = u; 
      next = u; 
      u->prev = this;
      u->orig_prev = this;
      return next;
    }

    int count_filtered(int asciival) { return ((c != asciival) && (c != asciival+32) && c); }

    unit* get_next_filtered(int asciival) { 
      if (!next) return next;
      if ((next->c != asciival) && (next->c != asciival+32))
        return next; 
      else
        return next->get_next_filtered(asciival);
    }

    unit* get_prev_filtered(int asciival) { 
      if (!prev) return prev;
      if ((prev->c != asciival) && (prev->c != asciival+32))
        return prev; 
      else
        return prev->get_prev_filtered(asciival);
    }

    void reset() {
      this->next = this->orig_next;
      this->prev = this->orig_prev;
      unit* iter = this->next;
      while (iter) {
        iter->next = iter->orig_next;
        iter->prev = iter->orig_prev;
        iter = iter->next;
      }
    }

    unit* collapse_filtered(int asciival) {
      if (this->get_prev_filtered(asciival) && (abs(this->c - this->get_prev_filtered(asciival)->c) == 32)) {
        if (!this->get_next_filtered(asciival))
          this->get_prev_filtered(asciival)->get_prev_filtered(asciival)->next = 0;
        else
        {
          this->get_next_filtered(asciival)->prev = this->get_prev_filtered(asciival)->get_prev_filtered(asciival);
          this->get_prev_filtered(asciival)->get_prev_filtered(asciival)->next = this->get_next_filtered(asciival);
        }
        return this->get_prev_filtered(asciival)->get_prev_filtered(asciival);
      }
      return this->get_next_filtered(asciival);
    }
};


void solve() {
  std::string line;
  int res1(-1);
  std::getline(std::cin, line);

  unit first;
  unit* iter = &first;
  for(char c: line) {
    unit *u = new unit;
    u->c = c;
    iter = iter->add(u);
  }

  // we hebben een linked list!
  iter = &first;
  while (iter) iter = iter->collapse_filtered(0);

  iter = &first;
  while (iter) {
    res1 += iter->count_filtered(0);
    iter = iter->get_next_filtered(0);
  }

  int shortest = 1000000;
  for (int i = 65; i <= 90; i++) {
    int tmpcnt = -1;
    iter = &first;
    iter->reset();
    while (iter) iter = iter->collapse_filtered(i);

    iter = &first;
    while (iter) {
      tmpcnt += iter->count_filtered(i);
      iter = iter->get_next_filtered(i);
    }
    if (shortest > tmpcnt) shortest = tmpcnt;
  } 
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << shortest << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

