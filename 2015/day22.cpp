#include <sstream>
#include <algorithm>
#include <queue>
#include "../common/lib.h"

struct w {
  bool boss_turn;
  int hp;
  int mana;
  int boss_hp;
  int shield_timer;
  int poison_timer;
  int recharge_timer;
  int total_mana_spent;
};

bool can_cast(int turns_left, int mana_cost, int current_mana) {
  return (turns_left < 1 && mana_cost < current_mana);
}

int play(int player_hp, int player_mana, int boss_hp, int boss_dmg, bool part_b_mod) {
  int min_mana(9999999);
  std::queue<w> q;
  q.push({false, player_hp, player_mana, boss_hp, 0, 0, 0, 0});
  while(!q.empty()) {
    w c = q.front();
  // do spell effects
    bool had_shield(false);
    if (c.poison_timer > 0)   { c.poison_timer--;   c.boss_hp -= 3; }
    if (c.recharge_timer > 0) { c.recharge_timer--; c.mana += 101; }
    if (c.shield_timer > 0)   { c.shield_timer--;   had_shield = true;}
    if (part_b_mod && !c.boss_turn) c.hp--;

    if (c.total_mana_spent > min_mana); // al betere uitkomst ergens
    else if (c.boss_turn && c.boss_hp > 0) { // boss turn
      q.push({false, c.hp-(boss_dmg - (had_shield ? 7 : 0)), c.mana, c.boss_hp, c.shield_timer, c.poison_timer, c.recharge_timer, c.total_mana_spent});
    } else if (!c.boss_turn && c.hp > 0) { // player turn
/* magic missile */ if (can_cast(0, 53, c.mana))                 q.push({true, c.hp  , c.mana-53,  c.boss_hp-4, c.shield_timer, c.poison_timer, c.recharge_timer, c.total_mana_spent+53 });
/* drain */         if (can_cast(0, 73, c.mana))                 q.push({true, c.hp+2, c.mana-73,  c.boss_hp-2, c.shield_timer, c.poison_timer, c.recharge_timer, c.total_mana_spent+73 });
/* shield */        if (can_cast(c.shield_timer, 113, c.mana))   q.push({true, c.hp  , c.mana-113, c.boss_hp  , 6             , c.poison_timer, c.recharge_timer, c.total_mana_spent+113});
/* poison */        if (can_cast(c.poison_timer, 173, c.mana))   q.push({true, c.hp  , c.mana-173, c.boss_hp  , c.shield_timer, 6             , c.recharge_timer, c.total_mana_spent+173});
/* recharge */      if (can_cast(c.recharge_timer, 229, c.mana)) q.push({true, c.hp  , c.mana-229, c.boss_hp  , c.shield_timer, c.poison_timer, 5               , c.total_mana_spent+229});
    }
    if (c.boss_hp <= 0 && c.hp > 0) if (min_mana > c.total_mana_spent) min_mana = c.total_mana_spent;
    q.pop();
  }
  return min_mana;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::string discard;
  int hp(0), dmg(0);
  std::cin >> discard >> discard >> hp >> discard >> dmg;
  return { play(50, 500, hp, dmg, false), play(50, 500, hp, dmg, true)};
}