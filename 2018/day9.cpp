#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

struct marble {
  int64_t value;
  marble* prev;
  marble* next;
};

int64_t solve_int(int64_t max_players, int64_t max_marble) {
  std::map<int64_t,int64_t> player_scores;
  marble* current_marble = new marble;
  current_marble->prev = current_marble;
  current_marble->next = current_marble;
  int64_t current_elf(1);

  for (int64_t marble_value = 1; marble_value <= max_marble; marble_value++, current_elf++) {
    if ((marble_value % 23) == 0) {
      int64_t elf = (current_elf%max_players);
      if (player_scores.count(elf) == 0) player_scores.insert(std::pair<int64_t,int64_t>(elf, 0));
      player_scores[elf] += marble_value;

      marble *tmpmarble(current_marble);
      // 7 terug zoeken en hotpatchen ;-)
      for (int64_t tmpcount = 0; tmpcount < 7; tmpcount++)
        tmpmarble = tmpmarble->prev;
      player_scores[elf] += tmpmarble->value;
      tmpmarble->next->prev = tmpmarble->prev;
      tmpmarble->prev->next = tmpmarble->next;
      current_marble = tmpmarble->next;

    } else {
      marble * new_marble = new marble;
      new_marble->value = marble_value;
      current_marble->next->next->prev = new_marble;
      new_marble->next = current_marble->next->next;
      current_marble->next->next = new_marble;
      new_marble->prev = current_marble->next;
      current_marble = new_marble;
    }    
  }

  int64_t highscore(0);
  for(auto sc: player_scores) {
    if (sc.second > highscore) highscore = sc.second;
  }
  return highscore;
}


void solve() {
  int64_t max_players;
  int64_t max_marble;
  std::string idontcare;

  std::cin >> max_players >> idontcare >> idontcare >> idontcare >> idontcare >> idontcare >> max_marble >> idontcare;
  std::cout << "Solution part 1: " << solve_int(max_players, max_marble) << std::endl << "Solution part 2: " << solve_int(max_players, max_marble*100)  << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

