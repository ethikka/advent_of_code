#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <queue>

struct pawn {
  pawn(int x, int y, char type) : x(x), y(y), type(type) { }

  int x;
  int y;
  char type;
  bool alive = true;
  int HP = 200;
  int AP = 3;
};

char board[32][33];
std::vector<pawn> pawns;

void drawboard() {
  std::map<int,char> pawn_pos;
  for(auto p: pawns)
    pawn_pos[((p.x*100)+p.y)] = p.type;

  std::cout << std::endl;
  for(int y = 0; y < 32; y++) {
    for(int x = 0; x < 33; x++) {
      if (pawn_pos.count((x*100)+y) > 0)
        std::cout << pawn_pos[(x*100)+y];
      else
        std::cout << board[y][x];
    }
    std::cout << std::endl;
  }
}

void solve() {
  // read board
  std::string line;
  int y(0);
  while (std::getline(std::cin, line)) {
    int x(0);
    for(char c: line) {
      switch (c) {
        case '\r': x--; break;
        case 'G':
        case 'E': {
          pawns.push_back({x, y, c}); 
          board[y][x] = '.';
          break;
        }
        case '.': board[y][x] = '.'; break;
        case '#': board[y][x] = '#'; break;
        default: std::cout << "Whut?" << c;
      }
      x++;
    }
    y++;
  }

  for(auto p: pawns)
    std::cout << p.x << "," << p.y << ":" << p.type << std::endl;


  bool incombat = true;
  // combat rounds
  int combatround(1);
  while (incombat) {
    // map is ordered, so by generating a key from the position we get a reading-order worklist
    std::map<int,pawn*> pawn_order;
    for(auto p: pawns)
      if (p.alive)
        pawn_order[((p.y*100)+p.x)] = &p;

    // cycle through all pawns
    for(auto p: pawn_order) {
      std::cout << p.second->x << "," << p.second->y << ":" << p.second->type << std::endl;
      switch(p.second->type)
      {
        case 'G': p.second->x = p.second->x - 1; break;
        case 'E': p.second->x = p.second->x + 1; break;
      }
      // find closest target using a queue, always exhaust all possibilities 


    }
    std::cout << std::endl;
    combatround++;
    incombat = (combatround < 3);
  }




  int res1(0), res2(0);
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << res2 << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}