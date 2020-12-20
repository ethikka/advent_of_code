#include <sstream>
#include <vector>
#include <map>
#include <bitset>
#include <queue>
#include "../common/lib.h"

std::map<int, std::vector<int>> border_id_mappings;
std::map<int, std::vector<int>> border_ids;

bool map[96][96];

struct tile {
  int id;

  bool isCorner = false;
  bool placed = false;

  bool bits[10][10];

  void fill_possible_border_ids() {
    std::bitset<10> bs;
    // ugly as sin and hard to maintain
    for (int i = 0; i < 10; i++) bs[i] = bits[0][i]; border_ids[id].push_back(bs.to_ulong());   
    for (int i = 0; i < 10; i++) bs[i] = bits[i][9]; border_ids[id].push_back(bs.to_ulong());   
    for (int i = 0; i < 10; i++) bs[i] = bits[9][i]; border_ids[id].push_back(bs.to_ulong());   
    for (int i = 0; i < 10; i++) bs[i] = bits[i][0]; border_ids[id].push_back(bs.to_ulong());   
    for (int i = 0; i < 10; i++) bs[i] = bits[0][9-i]; border_ids[id].push_back(bs.to_ulong()); 
    for (int i = 0; i < 10; i++) bs[i] = bits[9-i][9]; border_ids[id].push_back(bs.to_ulong()); 
    for (int i = 0; i < 10; i++) bs[i] = bits[9][9-i]; border_ids[id].push_back(bs.to_ulong()); 
    for (int i = 0; i < 10; i++) bs[i] = bits[9-i][0]; border_ids[id].push_back(bs.to_ulong()); 
    for(auto idx: border_ids[id]) border_id_mappings[idx].push_back(id);
  };

  void examine() {
    bool isEdge[4];
    for (int i = 0; i < 4; i++) isEdge[i] = (border_id_mappings[border_ids[id][i]].size() == 1 || border_id_mappings[border_ids[id][i+4]].size() == 1);
    for (int i = 0; i < 4; i++) isCorner |= (isEdge[i] && isEdge[(i+1)%4]);
  }

  int N() { std::bitset<10> bs; for (int i = 0; i < 10; i++) bs[i] = bits[i][0]; return bs.to_ulong(); }
  int E() { std::bitset<10> bs; for (int i = 0; i < 10; i++) bs[i] = bits[9][i]; return bs.to_ulong(); }
  int S() { std::bitset<10> bs; for (int i = 0; i < 10; i++) bs[i] = bits[i][9]; return bs.to_ulong(); }
  int W() { std::bitset<10> bs; for (int i = 0; i < 10; i++) bs[i] = bits[0][i]; return bs.to_ulong(); }

  void join(int x, int y) {   
    int cnt(0);
    placed = true;
    if (x == -1 && y == -1) { 
      while (!((border_id_mappings[N()].size() == 1) && (border_id_mappings[W()].size()) == 1)) {
        if (cnt == 4) flip();
        cw();
        cnt++;
      }
    } else if (y == -1) { 
      while (!(border_id_mappings[N()].size() == 1 && W() == x)) {
        if (cnt == 4) flip();
        cw();
        cnt++;
      }
    } else if (x == -1) { 
      while (!(border_id_mappings[W()].size() == 1 && N() == y)) {
        if (cnt == 4) flip();
        cw();
        cnt++;
      }
    } else { 
      while (!(N() == y && W() == x) && cnt < 19) {
        if (cnt == 4) flip();
        cw();
        cnt++;
      }
    }
  }
  
  void cw() {
    bool newbits[10][10];
    for (int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
        newbits[9-y][x] = bits[x][y];
    for (int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
        bits[x][y] = newbits[x][y];
  }

  void flip() {
    bool newbits[10][10];
    for (int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
        newbits[x][9-y] = bits[x][y];
    for (int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
        bits[x][y] = newbits[x][y];
  }

  void place_in_grid(int x, int y) {
    for (int xx = 0; xx < 8; xx++) {
      for (int yy = 0; yy < 8; yy++) {
          map[(x*8)+xx][(y*8)+yy] = bits[xx+1][yy+1];
      }
    }
  }
};

void cw_map() {
  bool newmap[96][96];
  for (int x = 0; x < 96; x++) for (int y = 0; y < 96; y++) newmap[95-y][x] = map[x][y];
  for (int x = 0; x < 96; x++) for (int y = 0; y < 96; y++) map[x][y] = newmap[x][y];
}

void flip_map() {
  bool newmap[96][96];
  for (int x = 0; x < 96; x++) for (int y = 0; y < 96; y++) newmap[x][95-y] = map[x][y];
  for (int x = 0; x < 96; x++) for (int y = 0; y < 96; y++) map[x][y] = newmap[x][y];  
}

int count_map() {
  int res(0);
  for (int x = 0; x < 96; x++) for (int y = 0; y < 96; y++) if (map[x][y]) res++;
  return res;
}

bool monster_hunter() {
  bool res(false);
  std::vector<std::tuple<int,int>> monster_pixels({{18,0},{0,1},{5,1},{6,1},{11,1},{12,1},{17,1},{18,1},{19,1},{1,2},{4,2},{7,2},{10,2},{13,2},{16,2}});
  for (int xx = 0; xx < 76; xx++) {
    for (int yy = 0; yy < 93; yy++) {
      bool monster(true);
      for (auto t: monster_pixels) monster &= (map[xx+std::get<0>(t)][yy+std::get<1>(t)]);
      res |= monster;
      if (monster) for (auto t: monster_pixels) map[xx+std::get<0>(t)][yy+std::get<1>(t)] = false;
    }
  }
  return res;
}

std::map<int,tile> tiles;

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;

  while (!std::cin.eof()) {
    tile t;
    std::getline(std::cin, line);    // header
    t.id = std::stoi(line.substr(5, 4));
    int y(0);
    while(std::getline(std::cin, line) && line.size()) {
      for (int x = 0; x < line.size(); x++) 
        t.bits[x][y] = (line[x] == '#');
      y++;
    }
    t.fill_possible_border_ids();
    tiles[t.id] = t;
  }

  int grid[12][12];
  for(int y = 0; y < 12; y++) 
    for(int x = 0; x < 12; x++) 
      grid[x][y] = 0;

  res.first = 1;
  int startId;
  for(auto& t: tiles) {
    t.second.examine();
    if (t.second.isCorner) {
      res.first *= t.second.id;
      grid[0][0] = t.second.id;
    }
  }
  
  for(int y = 0; y < 12; y++) {
    for(int x = 0; x < 12; x++) {
      int newsq(-1);
      int x_id(-1), y_id(-1);
      if (grid[x][y] == 0) {
        if (x > 0) x_id = tiles[grid[x-1][y]].E();
        if (y > 0) y_id = tiles[grid[x][y-1]].S();
        for(auto idx: {x_id, y_id}) if (idx > -1) for(auto i: border_id_mappings[idx]) if (!tiles[i].placed) newsq = i;
        if (newsq >= 0) grid[x][y] = newsq;
      }
      tiles[grid[x][y]].join(x_id, y_id);
      tiles[grid[x][y]].place_in_grid(x, y);
    }
  }

  int cnt(0);
  while (!monster_hunter()) {
    cw_map(); 
    if (cnt++ == 4)
      flip_map();
  }
  res.second = count_map();
  return res;
}