#include <sstream>
#include <vector>
#include <set>
#include <variant>
#include <ranges>
#include "../common/lib.h"

struct packet : public std::variant<int64_t, std::vector<packet>> {};

auto operator<=>(const packet &left, const packet &right) {
  if (left.index() == 0) {
      if (right.index() == 0) return std::get<0>(left) <=> std::get<0>(right);
      else                    return packet{std::vector<packet>{left}} <=> right;
  } else {
      if (right.index() == 0) return left <=> packet{std::vector<packet>{right}};
      else {
        const auto &lv = std::get<1>(left);
        const auto &rv = std::get<1>(right);
        for (int i = 0; i < lv.size(); i++) {
            if (i >= rv.size())  return std::strong_ordering::greater;
            if (lv[i] < rv[i]) return std::strong_ordering::less;
            if (rv[i] < lv[i]) return std::strong_ordering::greater;
        }
        if (rv.size() == lv.size()) return std::strong_ordering::equal;
        return std::strong_ordering::less;
      }
  }
}

bool isnum(char a){ return (a >= '0' && a <= '9'); }

bool skipchar(char c) {
  char d;
  if (std::cin.peek() == c) { std::cin >> d; return true; }
  return false;
}

int64_t readint() {
  int64_t res(0);
  char c;
  do {
    if (isnum(std::cin.peek())) { std::cin >> c; res *= 10; res += c-'0'; } 
    else                          break;
  } while (isnum(c));
  return res;
}

std::vector<packet> readList() {
  std::vector<packet> result{};
  while (!skipchar(']') && !std::cin.eof()) {
    if (skipchar('[')) result.push_back({readList()});
    else               result.push_back({readint()});
    skipchar(',');
  }
  return result;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::set<packet> packets{};

  int64_t pair = 0;
  char discard;
  while (!std::cin.eof()) {
    std::cin >> discard; packet left{readList()};
    std::cin >> discard; packet right{readList()};
    ++pair;
    if (left < right) res.first += pair;
    packets.insert(left);
    packets.insert(right);
  }

  packet d0{std::vector<packet>{{std::vector<packet>{{2}}}}};
  packet d1{std::vector<packet>{{std::vector<packet>{{6}}}}};
  packets.insert(d0);
  packets.insert(d1);
  res.second = 1;
  int64_t index = 1;
  for (const auto &value : packets) {
    if (value == d0 or value == d1) res.second *= index;
    ++index;
  }
  return res;
}