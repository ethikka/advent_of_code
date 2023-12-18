#include <sstream>
#include <vector>
#include "../common/lib.h"

class sequencer {
  private:
    std::vector<std::vector<int64_t>> subsequences;
  public:
    sequencer(std::istringstream inp) {
      int64_t i, d, t; std::vector<int64_t> ss; bool all_zero;

      subsequences.push_back({});
      while (inp >> i) subsequences.back().push_back(i);
      do
      {
        d = 0; all_zero = true; ss.clear();
        for (int i = 1; i < subsequences.back().size(); i++) {
          ss.push_back(t = subsequences.back().at(i)-subsequences.back().at(i-1));
          d += ss.back();
          all_zero &= (d == 0);
        }
        subsequences.push_back(ss);
      } while (!all_zero);
    };
    int64_t predict_next() { int64_t pred(0); for(int i = subsequences.size()-1; i >= 0; --i) pred = subsequences.at(i).back() +pred; return pred; };
    int64_t predict_prev() { int64_t pred(0); for(int i = subsequences.size()-1; i >= 0; --i) pred = subsequences.at(i).front()-pred; return pred; };
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<int64_t, int64_t> res;
  std::string line;
  std::vector<sequencer> seqs;
  while (std::getline(std::cin, line)) seqs.push_back(sequencer(std::istringstream(line)));

  for(auto s: seqs) {
    res.first += s.predict_next();
    res.second += s.predict_prev();
  }
  return res;
}