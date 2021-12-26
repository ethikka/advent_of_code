#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <chrono>
#include <algorithm>

typedef std::pair<int,int> point;
typedef std::map<point,char> posimap;

std::vector<point> offsets= { {-1,0}, {1,0}, {0,-1}, {0,1}};
int res1 = 0;
int res2 = 0;

int number_of_keys = 0;

int best = 9999999;
std::vector<std::string> m;

struct keyset {
    int keys;
    int cnt;
    keyset() : keys(0), cnt(0) {}

    void set(int i) {
        if((keys&(1<<i))==0) cnt++;
        keys|=(1<<i);
    }

    void unset(int i) {
        if((keys&(1<<i))) cnt--;
        keys&=~(1<<i);
    }

    bool isset(int i) {
        if(i<0) return false;
        return (keys&(1<<i));
    }
};

bool operator<(const keyset &k1, const keyset k2) {
    return k1.keys<k2.keys;
}

std::map<std::pair<keyset,std::vector<point>>, int> memory2;

void search2(keyset &found_keys, std::vector<point> position, int steps) {
  if(found_keys.cnt == 26) {
    std::cout << best << "," << steps << std::endl;
    if (steps < best)
      best = std::min(best, steps);
    return;
  }
  if(steps >= best) return;

  auto k=make_pair(found_keys, position);
  auto it=memory2.find(k);
  if (it!=memory2.end() && it->second <= steps) 
    return;
  memory2[k]=steps;

  for(int r=0; r < position.size(); r++) {
    std::vector<std::vector<int>> dp(m.size(), std::vector<int>(m[0].size(), 99999999));
    dp[position[r].first][position[r].second]=0;

    std::queue<point> q;
    q.push(position[r]);
    while(q.size()) {
      point pos=q.front();
      q.pop();
      for(point p : offsets) {
        point newpos = { pos.first+p.first, pos.second+p.second };

        if(newpos.first<0 || newpos.first>=m.size() || newpos.second<0 || newpos.second>=m[newpos.first].size()) continue;
        if(m[newpos.first][newpos.second]=='#') continue;

        int ndp = dp[pos.first][pos.second]+1;
        bool canMove=false;
        char mat = m[newpos.first][newpos.second];

        if (mat == '.' || found_keys.isset(mat-'a')) {
          canMove=true;
        } else if (mat >= 'a' && mat <= 'z') {
          found_keys.set(mat-'a');
          point oldPos=position[r];
          position[r] = newpos;
          search2(found_keys, position, steps+ndp);  
          position[r] = oldPos;
          found_keys.unset(mat-'a');
        } else if (mat>='A' && mat<='Z') {
          if(found_keys.isset(mat-'A'))
            canMove=true;
        }
        if (canMove && dp[newpos.first][newpos.second] > ndp) {
          dp[newpos.first][newpos.second] = ndp;
          q.push(newpos);
        }
      }
    }
  }
}

void solve() {
  int res1(0);

  point playerpos;
  std::string s;
  while (std::cin >> s) {
    if(s.size() > 0)
      m.push_back(s);
    else
      break;

    for(size_t i=0; i<s.size(); i++) {
      if(s[i]=='@') {
        playerpos = std::make_pair( (int)m.size()-1, (int)i );
        m.back()[i]='.';
      }
    }
  }

  std::vector<point> startingpos = { playerpos };
  keyset keys;
  search2(keys, startingpos, 0);
  res1 = best;
  best = 999999;
  startingpos.clear();
  // doolhof dichtplamuren
  m[playerpos.first][playerpos.second]='#';
  m[playerpos.first+1][playerpos.second]='#';
  m[playerpos.first-1][playerpos.second]='#';
  m[playerpos.first][playerpos.second+1]='#';
  m[playerpos.first][playerpos.second-1]='#';
  m[playerpos.first+1][playerpos.second+1]='.';
  m[playerpos.first-1][playerpos.second-1]='.';
  m[playerpos.first-1][playerpos.second+1]='.';
  m[playerpos.first+1][playerpos.second-1]='.';

  startingpos= { { playerpos.first+1, playerpos.second+1 }, { playerpos.first-1, playerpos.second-1 }, { playerpos.first-1, playerpos.second+1 }, { playerpos.first+1, playerpos.second-1 }};
  keyset keys2;
  search2(keys, startingpos, 0);
  std::cout << "Solution part 1: " << res1 << std::endl << "Solution part 2: " << best << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}
