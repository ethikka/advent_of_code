#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include <queue>
#include <algorithm>

struct fp {
  int x;
  int y;
  int z;
  int w;
  bool operator ==(const fp &comp) const { return (x == comp.x) && (y == comp.y) &&(z == comp.z) && (w == comp.w ); };
};

std::ostream& operator<<(std::ostream& o, fp p)
{
  o << "[" << p.x << ", " << p.y << ", " << p.z << "," << p.w << "]";
  return o;
};

bool operator <(const fp &lhs, const fp &rhs) {
  return (lhs.x < rhs.x) && 
         (lhs.y < rhs.y) &&
         (lhs.z < rhs.z) &&
         (lhs.w < rhs.w);
};

int mhd(fp a, fp b) {
  return std::abs(a.x-b.x)+std::abs(a.y-b.y)+std::abs(a.z-b.z)+std::abs(a.w-b.w);
};

std::list<fp> fpa;

void solve() {
  std::string line;
  while (std::getline(std::cin, line)) {
    fp p;
    sscanf(line.c_str(), "%d,%d,%d,%d", &p.x, &p.y, &p.z, &p.w);
    fpa.push_back(p);
  }

  int constellations(0);
  std::queue<fp> work;
  while (fpa.size() > 0) {
    work.push(fpa.back());
    while (!work.empty()) {
      fp check = work.front();
      work.pop();
      if (std::find(fpa.begin(), fpa.end(), check) != fpa.end()) {
        fpa.erase(std::find(fpa.begin(), fpa.end(), check));
        for(auto a: fpa) {
          if (mhd(a, check) <= 3) {
            work.push(a);
          };
        };
      };
    };
    constellations++;
  };
  std::cout << "Solution part 1: " << constellations << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

