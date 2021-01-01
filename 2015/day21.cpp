#include <sstream>
#include <vector>
#include "../common/lib.h"

struct gear {
  std::string name;
  int cost;
  int damage;
  int armor;
};

std::vector<gear> weapons{{"Dagger", 8, 4, 0}, {"Shortsword", 10, 5, 0}, {"Warhammer", 25, 6, 0}, {"Longsword", 40, 7, 0}, {"Greataxe", 74, 8, 0}};
std::vector<gear> armor{{"None", 0, 0, 0}, {"Leather", 13, 0, 1}, {"Chainmail", 31, 0, 2}, {"Splintmail", 53, 0, 3}, {"Bandedmail", 75, 0, 4}, {"Platemail", 102, 0, 5}};
std::vector<gear> rings{{"None", 0, 0, 0}, {"Damage +1", 25, 1, 0}, {"Damage +2", 50, 2, 0}, {"Damage +3", 100, 3, 0}, {"Defense +1", 20, 0, 1}, {"Defense +2", 40, 0, 2}, {"Defense +3", 80, 0, 3}};

bool simulate(int player_hp, int player_dmg, int player_ac, int boss_hp, int boss_dmg, int boss_ac) {
  if ((player_dmg-boss_ac) <= 0) return false;
  if ((boss_dmg-player_ac) <= 0) return true;
  return (boss_hp / (player_dmg-boss_ac)) <= (player_hp / (boss_dmg-player_ac));
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{9999,0};
  std::string discard;
  int hp(0), dmg(0), ac(0);
  std::cin >> discard >> discard >> hp >> discard >> dmg >> discard >> ac;

  for(auto w: weapons) 
    for (auto a: armor) 
      for (auto r1: rings) 
        for (auto r2: rings) 
          if (r1.name != r2.name || r1.cost == 0) {
            int pcost(w.cost+a.cost+r1.cost+r2.cost);
            if (simulate(100, w.damage+a.damage+r1.damage+r2.damage, w.armor+a.armor+r1.armor+r2.armor, hp, dmg, ac)) {
              if (res.first > pcost) res.first = pcost;
            } else {
              if (res.second < pcost) res.second = pcost;
            }
          }
  return res;
}