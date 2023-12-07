#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include "../common/lib.h"

enum hand_type { HIGH_CARD = 0, ONE_PAIR = 1, TWO_PAIR = 2, THREE = 3, FULL_HOUSE = 4, FOUR = 5, FIVE = 6};
hand_type m[6] = { FIVE, FIVE, FOUR, THREE, ONE_PAIR, HIGH_CARD };

hand_type get_type(std::string i) {
    std::map<char,int> freq;
    std::set<int> ff;
    for(char c: i) freq[c]++;
    hand_type r = m[freq.size()];
    if (freq.size() == 2 && (freq.begin()->second == 2 || freq.rbegin()->second == 2)) r = FULL_HOUSE;
    if (freq.size() == 3 && (freq.begin()->second == 2 || freq.rbegin()->second == 2)) r = TWO_PAIR;
    return r;
};

class camelcard_hand {
  public:
    std::string cards, sub_cards;
    hand_type type;
    bool wildcard_hand;
    camelcard_hand(std::string input, bool wildcard) { 
        cards = input; 
        wildcard_hand = wildcard;
        type = get_type(cards); 
        if (wildcard) {
            std::map<char,int> freq;
            std::string remaining(cards);
            remaining.erase(std::remove(remaining.begin(), remaining.end(), 'J'), remaining.end());
            if (remaining.size() != 5) {
              for(char c: remaining) freq[c]++;
              type = m[freq.size()];
              if (remaining.size() == 4 && freq.size() == 2 && (freq.begin()->second == 2)) type = FULL_HOUSE;
            }
        };
    };
};

auto operator<=>(const camelcard_hand &left, const camelcard_hand &right) {
    if (left.type == right.type) {
        std::string comp = left.wildcard_hand ? "AKQT98765432J": "AKQJT98765432";
        for (int i = 0; i < 5; i++) {
            if (comp.find(left.cards[i]) > comp.find(right.cards[i])) return std::strong_ordering::less;
            if (comp.find(left.cards[i]) < comp.find(right.cards[i])) return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    } else if (left.type > right.type) return std::strong_ordering::greater;
    else return std::strong_ordering::less;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string cards;
  int64_t bid, idx(0);
  std::map<camelcard_hand, int64_t> hands, wildcard_hands;

  while (std::cin >> cards >> bid) { hands.insert({camelcard_hand(cards, false), bid}); wildcard_hands.insert({camelcard_hand(cards, true), bid}); }

  for(auto cc: hands) res.first += (cc.second * ++idx);
  idx = 0;
  for(auto cc: wildcard_hands) res.second += (cc.second * ++idx);
  return res;
}