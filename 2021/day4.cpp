#include <sstream>
#include <vector>
#include <algorithm>
#include "../common/lib.h"

class board {
    std::vector<int> numbers;
    std::vector<int> drawn;
  public:
    bool stop;

    board ()  {
      int n(0);
      for (int i = 0; i < 25; i++) {
        std::cin >> n;
        numbers.push_back(n);
      }
    }

    int64_t bingo_crc(int last) {
      int res(0);
      for (auto n: numbers) res += n;
      return res*last;
    }

    bool bingo() {
      for (int s: {0,5,10,15,20}) {
        bool has_bingo(true);
        for (int c = 0; c < 5; c++)
          has_bingo &= numbers[s+c] == 0;
        if (has_bingo) return true;
      }

      for (int s: {0,1,2,3,4}) {
        bool has_bingo(true);
        for (int c = 0; c < 5; c++)
          has_bingo &= numbers[s+(c*5)] == 0;
        if (has_bingo) return true;
      }

      return false;
    }

    bool draw (int num) {
      if (stop) return stop;
      for (int i = 0; i < 25; i++) 
        if (num == numbers[i])
          numbers[i] = 0;
      stop = bingo();

      return stop;
    }
  
    void print() {
      for(int i = 0; i < 25; i++) {
        if (i % 5 == 0) std::cout << std::endl;
        std::cout << std::setw(3) << numbers[i];
      }
      std::cout << std::endl;
    }
  };

bool bb(board b) {
  return b.stop;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  
  std::string line;
  std::cin >> line; // read drawn numbers
  std::replace(line.begin(), line.end(), ',', ' '); 

  int num;
  std::vector<board> boards;
  while (!std::cin.eof()) {
    board t;
    boards.push_back(t);
  }

  std::istringstream ssl(line);
  int draw(0);
  while (ssl >> draw) {
    for(auto &b: boards) {
        if (!b.stop) {
          if (b.draw(draw)) {
            if (res.first == 0) res.first = b.bingo_crc(draw); else res.second = b.bingo_crc(draw);
          }
          // Uncomment to show bingocards    
          //b.print();
        }
    }
  }

  return res;
}