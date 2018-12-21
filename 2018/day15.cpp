#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <queue>
#include <set>

int round_number(0);
bool end_combat(false);

struct pawn {
  pawn(): AP(3) {}
  pawn(int x, int y, char type) : x(x), y(y), type(type), AP(3) { }
  pawn(int x, int y, char type, int ap) : x(x), y(y), type(type), AP(ap) { }
  int x;
  int y;
  char type;
  bool alive = true;
  int HP = 200;
  int AP = 3;
};

char board[32*32];
std::map<int,pawn> pawns;

struct search_work {
  search_work() {}
  search_work(int key, std::string path, int d): key(key), path(path), distance(d) {}
  int key;
  std::string path;
  int distance;
};

std::string offset_to_string(int x) {
  switch(x) {
    case  32: return "S";
    case -32: return "N";
    case   1: return "E";
    case  -1: return "W";
  };
  return "";
};

void apply_round(int unit) {
  std::map<int,int> pawn_pos;
  for(auto p: pawns)
    if (p.first != unit && p.second.type != pawns[unit].type) {
      pawn_pos[((p.second.y*32)+p.second.x)] = p.first;
    }

  std::queue<search_work> bfs;

  int closest_target(99999);
  std::set<int> visited;
  // //char move;
  bfs.push(search_work{(pawns[unit].y*32)+pawns[unit].x, "", 0});
  while(!bfs.empty()) {
    search_work p = bfs.front();
    if ((visited.count(p.key) == 0) && p.distance <= closest_target) {
      for (auto o: {+32, -32, +1, -1}) {
        if (pawn_pos.count(p.key+o) != 0) {
          std::cout << "Found a target! " << pawns[unit].y << "," << pawns[unit].x << "=>" << pawns[pawn_pos[p.key+o]].y << "," << pawns[pawn_pos[p.key+o]].x << " Distance " << p.distance << " /" << p.path << std::endl;
          closest_target = p.distance;
        }
        else
          bfs.push(search_work{p.key+o, p.path+offset_to_string(o), p.distance+1});

      };
      visited.insert(p.key);
    }


    // look at surrounding spots
    // if (OTHER_UNIT) 


    //bfs.push({low, -1*walls[0]});
    bfs.pop();
  };

  // switch(move) {
  //   case 'N': break;
  //   case 'E': break;
  //   case 'S': break;
  //   case 'W': break;
  // }


  end_combat = round_number > 0;
};


void drawboard() {
//  std::system("clear");  
  std::cout << "Round " << round_number << std::endl;
  std::map<int,char> pawn_pos;
  for(auto p: pawns)
    pawn_pos[((p.second.y*32)+p.second.x)] = p.second.type;

  std::cout << std::endl;
  for(int key = 0; key < 32*32; key++) {
    if ((key % 32) == 0) std::cout << std::endl;
    if (pawn_pos.count(key) > 0)
      std::cout << pawn_pos[key];
    else
      std::cout << board[key];
  }
  std::cout << std::endl;
}

void solve() {
  std::string line;
  int y(0);
  while (std::getline(std::cin, line)) {
    int x(0);
    for(char c: line) {
      switch (c) {
        case '\r': x--; break;
        case 'G':
        case 'E': {
          pawns[pawns.size()] = pawn(x, y, c);
          board[(y*32)+x] = '.';
          break;
        }
        default: board[(y*32)+x] = c;
      }
      x++;
    }
    y++;
  }

  // combat rounds
  while (!end_combat) {
    drawboard();
    // map is ordered, so by generating a key from the position we get a reading-order worklist
    std::map<int,int> pawn_order;
    for(auto p: pawns)
      if (p.second.alive)
        pawn_order[((p.second.y*32)+p.second.x)] = p.first;

    for(auto p: pawn_order) apply_round(p.second);

    round_number++;
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