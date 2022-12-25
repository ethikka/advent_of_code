#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <array>
#include <memory>
#include <algorithm>
#include "../common/lib.h"
#include "../common/vector2.h"

int width(0), heigth(0);
typedef std::array<std::vector<std::vector<std::vector<bool>>>,4> block_timemap;

struct work {
  work(int64_t min, vector2 pos, std::shared_ptr<work> prev):current_time(min),position(pos),prev_pos(prev){};
  int current_time;
  vector2 position;
  std::shared_ptr<work> prev_pos;
};

std::vector<std::pair<vector2,int64_t>> blizzards;

int64_t find_work(vector2 &start, vector2 &target, const block_timemap &blocked, int64_t time_start) {
  int64_t maxY = blocked[0][0].size();
  int64_t maxX = blocked[0][0][0].size();
  int64_t maxR = (maxX-2)*(maxY-2);

  std::vector<std::vector<std::vector<int64_t>>> dist(maxR,std::vector<std::vector<int64_t>>(maxX,std::vector<int64_t>(maxY, std::numeric_limits<int64_t>::max())));
  std::priority_queue<std::tuple<int64_t,int64_t,vector2,std::shared_ptr<work>>,std::vector<std::tuple<int64_t,int64_t,vector2,std::shared_ptr<work>>>, std::greater<>> q;
  q.emplace(target.manhattanlength(),0,start,std::make_shared<work>(0,start,nullptr));

  std::shared_ptr<work> p;

  while(!q.empty()) {
    auto w = q.top();
    int64_t cost = std::get<1>(w);
    vector2 pos = std::get<2>(w);
    std::shared_ptr<work> node = std::get<3>(w);
    q.pop();

    if(pos==target) return cost;
    cost++;
    int64_t round = (time_start+cost) % maxR;
    if(dist[round][pos.x][pos.y]<=cost) continue;
    dist[round][pos.x][pos.y] = cost;

    int64_t h = (target-pos).manhattanlength();

    // wait?
    if(none_of(blocked.begin(),blocked.end(),[&round,&pos](auto& current){ return current[round % current.size()][pos.y][pos.x]; })) q.emplace(cost+h,cost,pos,std::make_shared<work>(cost,pos,node));
    // v
    if(pos.y<maxY-2 || (pos.y==maxY-2 && pos.x == maxX-2)){
      vector2 c = pos + vector2{0,1};
      if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){ return current[round % current.size()][c.y][c.x]; })) q.emplace(cost+h,cost,c,std::make_shared<work>(cost,c,node));
    }
    // >
    if(pos.x<maxX-2 && pos.y!=0){
      vector2 c = pos + vector2{1,0};
      if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){ return current[round % current.size()][c.y][c.x]; })) q.emplace(cost+h,cost,c,std::make_shared<work>(cost,c,node));
    }
    // ^
    if(pos.y>1 || (pos.y==1&&pos.x==1)){
      vector2 c = pos + vector2{0,-1};
      if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){ return current[round % current.size()][c.y][c.x]; })) q.emplace(cost+h,cost,c,std::make_shared<work>(cost,c,node));
    }
    // <
    if(pos.x>1 && pos.y != maxY-1 ){
      vector2 c = pos + vector2{-1,0};
      if(none_of(blocked.begin(),blocked.end(),[&round,&c](auto& current){ return current[round % current.size()][c.y][c.x]; })) q.emplace(cost+h,cost,c,std::make_shared<work>(cost,c,node));
    }
  }
  return -999;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  std::string line;
  
  int x(0), y(0);
  while (std::getline(std::cin, line)) {
    x = 0;
    for(char c : line) {
      switch (c) {
          case '>': blizzards.push_back(std::make_pair(vector2{x,y},0)); break;
          case 'v': blizzards.push_back(std::make_pair(vector2{x,y},1)); break;
          case '<': blizzards.push_back(std::make_pair(vector2{x,y},2)); break;
          case '^': blizzards.push_back(std::make_pair(vector2{x,y},3)); break;
      }
      ++x;
    }
    ++y;
  }
  width = x; heigth = y;

  vector2 start{1,0};
  vector2 target{width-2,heigth-1};

  // generate block timemap
  block_timemap blocked;
  blocked[0] = blocked[2] = std::vector<std::vector<std::vector<bool>>>(width-2,std::vector<std::vector<bool>>(heigth,std::vector<bool>(width,false)));
  blocked[1] = blocked[3] = std::vector<std::vector<std::vector<bool>>>(heigth-2,std::vector<std::vector<bool>>(heigth,std::vector<bool>(width,false)));
  for (auto &b : blizzards) {
    switch (b.second) {
      case 0: { 
        for (int i = 0; i < width - 2; ++i) {
          auto newX = b.first.x + (i % (width - 2));
          if (newX >= width-1) newX -= (width - 2);
            blocked[0][i][b.first.y][newX] = true;
        }
      } break;
      case 1: {
        for (int i = 0; i < heigth-2; ++i) {
          auto newY = b.first.y + (i%(heigth-2));
          if(newY >= heigth-1) newY-=(heigth-2);
          blocked[1][i][newY][b.first.x] = true;
        }
      } break;
      case 2: {
        for (int i = 0; i < width - 2; ++i) {
          auto newX = b.first.x - (i%(width-2));
          if(newX <= 0 ) newX += (width-2);
          blocked[2][i][b.first.y][newX] = true;
        }
      } break;
      case 3: {
        for (int i = 0; i < heigth - 2; ++i) {
          auto newY = b.first.y - (i%(heigth-2));
          if(newY <= 0 ) newY+=(heigth-2);
          blocked[3][i][newY][b.first.x] = true;
        }
      } break;
    }
  }

  res.first = find_work(start, target, blocked, 0);
  res.second = res.first;
  res.second += find_work(target, start, blocked, res.second);
  res.second += find_work(start, target, blocked, res.second);
  return res;
}