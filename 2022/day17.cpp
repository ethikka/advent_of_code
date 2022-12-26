#include <sstream>
#include <map>
#include <array>
#include <vector>
#include "../common/lib.h"
#include "../common/vector2.h"
#include "../common/circularlist.h"

tbb::circularlist<char> jets;

typedef std::vector<vector2> Rock;

void move_to_starting_height(Rock& rock, int highest) { for (auto& ele : rock) ele.y += highest + 3; }
void move(Rock& rock) { for (auto& ele : rock) ele.y--; }

bool intersection(const std::vector<std::array<char, 7>>& chamber, const Rock& rock) {
  for (const auto& ele : rock) if (ele.y < chamber.size()) if (chamber[ele.y][ele.x] == '#') return true;
  return false;
}

void add_rock_to_chamber(std::vector<std::array<char, 7>>& chamber, const Rock& rock) {
  for (const auto& ele : rock) while(chamber.size() <= ele.y) chamber.push_back({'.','.','.','.','.','.','.'});
  for (const auto& ele : rock) chamber[ele.y][ele.x] = '#';
}

void apply_jet(Rock& rock, char jet, const std::vector<std::array<char, 7>>& chamber) {
  const auto prev = rock;
  switch (jet) {
    case '>': { for (auto& ele : rock) { ele.x++; if (ele.x > 6) { rock = prev; return; }}} break;
    case '<': { for (auto& ele : rock) { ele.x--; if (ele.x < 0) { rock = prev; return; }}} break;
  }
  if (intersection(chamber, rock)) rock = prev;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  tbb::circularlist<char> jets;
  char c;
  while (std::cin >> c) jets.enqueue(c);

  tbb::circularlist<Rock> rocks;
  rocks.enqueue({
    Rock{vector2(0,0), vector2(1,0), vector2(2,0), vector2(3,0)},
    Rock{vector2(1,0), vector2(0,1), vector2(1,1), vector2(2,1), vector2(1,2)},
    Rock{vector2(2,2), vector2(2,1), vector2(0,0), vector2(1,0), vector2(2,0)},
    Rock{vector2(0,0), vector2(0,1), vector2(0,2), vector2(0,3)},
    Rock{vector2(0,0), vector2(1,0), vector2(0,1), vector2(1,1)}
  });

  for (auto& rock : rocks.buffer) for (auto& ele : rock) ele.x += 2;

  std::map<int64_t,std::vector<std::pair<int64_t,int64_t>>> states;

  int rock_count = 0;
  std::vector<std::array<char, 7>> chamber;
  chamber.push_back({'#','#','#','#','#','#','#'}); // bottom
  while (rock_count++ < 4700) { // why 4700? no more is needed for a stable repeating state ;-) if res.second = 0 then it probably needs a few more for your input
    auto rock = rocks.front_and_next();
    move_to_starting_height(rock, chamber.size());
    auto prev = rock;
    while (!intersection(chamber, rock)) {
      apply_jet(rock, jets.front_and_next(), chamber);
      prev = rock;
      move(rock);
    }
    add_rock_to_chamber(chamber, prev);
    states[jets.internal_index()+(rocks.internal_index()*100000)].push_back({chamber.size(), rock_count});
    if (rock_count == 2022) res.first = chamber.size()-1;
  }

  auto ss = states.at(jets.internal_index()+(rocks.internal_index()*100000));
  int ROCKCYCLE(ss.back().first), ROCKHEIGTH(ss.back().second);
  ss.pop_back();
  ROCKCYCLE -= ss.back().first; ROCKHEIGTH -= ss.back().second;

  int64_t cnt(0), ln(1000000000000);
  while (ln > 5100) { ln -= ROCKHEIGTH; cnt++; }

  for (auto s: states) for (auto ss: s.second) if (ss.second == ln) res.second = (ss.first+(ROCKCYCLE*cnt))-1;
  return res;
}