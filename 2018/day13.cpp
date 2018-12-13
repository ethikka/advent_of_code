#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <set>

int ymod(1000);

struct train {
  char direction;
  int intersectioncounter;
};

std::map<int,std::string> trackmap;
std::map<int,train> trains;

train cartdirection(train def, int newpos) {
  train ret(def);
  switch(trackmap[newpos/ymod][newpos%ymod]) {
    case '+': switch(ret.direction) {
                case '^': ret.direction = "<^>"[ret.intersectioncounter%3]; break;
                case '>': ret.direction = "^>v"[ret.intersectioncounter%3]; break;
                case 'v': ret.direction = ">v<"[ret.intersectioncounter%3]; break;
                case '<': ret.direction = "v<^"[ret.intersectioncounter%3]; break;
              };
              ret.intersectioncounter++;
              break;
    case '/': switch(ret.direction) {
                case '^': ret.direction = '>'; break;
                case '>': ret.direction = '^'; break;
                case 'v': ret.direction = '<'; break;
                case '<': ret.direction = 'v'; break;
              };
              break;
    case '\\': switch(ret.direction) {
                 case '^': ret.direction = '<'; break;
                 case '>': ret.direction = 'v'; break;
                 case 'v': ret.direction = '>'; break;
                 case '<': ret.direction = '^'; break;
               };
               break;
  }
  return ret;
}

void solve() {
  std::string line, res1, res2;
  for (int linecount = 0; std::getline(std::cin, line); linecount++)
    trackmap[linecount] = line;

  // find trains
  for(auto s: trackmap) {
    int64_t endpos = trackmap[s.first].find_last_of("<>^v");
    while (endpos != -1) {
      train t;
      t.direction = trackmap[s.first][endpos];
      t.intersectioncounter = 0;
      trains[(s.first*ymod)+endpos] = t;
      switch (trackmap[s.first][endpos]) {
        case '>':
        case '<': trackmap[s.first][endpos] = '-';  break;
        default: trackmap[s.first][endpos] = '|'; break;
      }
      endpos = trackmap[s.first].find_last_of("<>^v");
    }
  }

  while (trains.size() > 1) {
    std::map<int,train> tmp;
    std::set<int> crashspots;

    for (auto t: trains) {
      if (crashspots.count(t.first) == 0) {
        int newpos = t.first;
        switch(t.second.direction) {
          case 'v': newpos += ymod; break;
          case '^': newpos -= ymod; break;
          case '<': newpos -= 1; break;
          case '>': newpos += 1; break;
        }
        if (trains.count(newpos) > 0 || tmp.count(newpos) > 0) {
          if (res1.size() == 0)
            res1 = std::to_string(newpos%ymod) + "," + std::to_string(newpos/ymod);
          crashspots.insert(newpos);
        }
        if (crashspots.count(newpos) == 0)
          tmp[newpos] = cartdirection(trains[t.first],newpos);
      }
    }

    // reinsert moved carts
    trains.clear();
    for(auto t: tmp) {
      if (crashspots.count(t.first) == 0) {
        trains[t.first] = t.second;
      }
    }
    crashspots.clear();
  };
  for(auto t: trains) 
    res2 = std::to_string(t.first % ymod) + "," + std::to_string(t.first / ymod);

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

