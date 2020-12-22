#include <sstream>
#include <vector>
#include <unordered_set>
#include <tuple>
#include "../common/lib.h"

std::string state(std::vector<int> deck) {
  std::string res1("");
  for(auto c: deck) res1 += std::to_string(c)+",";
  return res1;
}

int64_t fingerprint(std::vector<int> deck) {
  int64_t res1(0), cnt(deck.size());
  for(auto c: deck) res1 += (c * cnt--);
  return res1;
}

std::tuple<std::vector<int>,std::vector<int>,int> play_recursive_decks(std::vector<int> player[2], bool recursive, int game) {
  std::unordered_set<std::string> previous_states;
  int round(0);
  while (player[0].size() > 0 && player[1].size() > 0) {
    if (recursive) {
      std::string key = state(player[0])+"|"+state(player[1]);
      if (previous_states.count(key)) 
        return std::make_tuple(player[0], player[1], 0);
      previous_states.insert(key);
    }

    int p[2];
    for(auto i: {0,1}) {
      p[i] = player[i].front(); 
      player[i].erase(player[i].begin());
    }

    int winner = (p[0] > p[1] ? 0 : 1);
    if ((p[0] <= player[0].size()) && (p[1] <= player[1].size()) && recursive) {
      std::vector<int> p1, p2, subgame[2]{{player[0].begin(), player[0].begin()+p[0]}, {player[1].begin(), player[1].begin()+p[1]}};
      std::tie(p1, p2, winner) = play_recursive_decks(subgame, recursive, game+1);
    }
    player[winner].push_back(p[winner]);
    player[winner].push_back(p[(winner+1)%2]);
  }
  return std::make_tuple(player[0], player[1], ((player[1].size() == 0) ? 0 : 1 ));
};

int64_t play(std::vector<int> player[2], bool recursive) {
  std::vector<int> p1, p2;
  int winner;
  std::tie(p1, p2, winner) = play_recursive_decks(player, recursive, 1);
  return (winner == 0 ? fingerprint(p1) : fingerprint(p2));
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  std::vector<int> player_a[2];
  for(auto i: {0,1}) {
    std::getline(std::cin, line); // skip player header
    while(std::getline(std::cin, line) && line.size())
      player_a[i].push_back(std::stoi(line));
  }
  std::vector<int> player_b[2]{player_a[0], player_a[1]};

  res.first = play(player_a, false);
  res.second = play(player_b, true);
  return res;
}