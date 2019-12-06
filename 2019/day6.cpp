#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <locale>
#include <map>

struct orbitseperator : std::ctype<char> {
    static const mask* make_table()
    {
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[')'] |=  space;  // ) toevoegen aan whitespace lijst
        return &v[0];
    }
    orbitseperator(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};


struct orbitnode {
  orbitnode(std::string n, std::string o) {
    name = n;
    orbits = o;
    stepcount = 0;
  };
  orbitnode() {};

  std::string name;
  std::string orbits;
  int stepcount;
};

void solve() {
  int res1(0), res2(0), cc(0);
  std::map<std::string, orbitnode> planets;
  std::string body, orbits;

  std::cin.imbue(std::locale(std::cin.getloc(), new orbitseperator));

  // search&replaced ) in the input with a space for easier parsing
  while (std::cin >> orbits >> body) {
    if (planets.count(body) == 0) 
      planets[body] = orbitnode(body, orbits);
    //else
      planets[body].orbits = orbits;
    if (planets.count(orbits) == 0) planets[orbits] = orbitnode(orbits, ""); 
  }

  for (auto p: planets) {
    orbitnode on = p.second;
    while (on.orbits != "") {
      on = planets[on.orbits];
      res1++;
    }
  }

  orbitnode on = planets[planets["YOU"].orbits];
  while (on.orbits != "") {
    planets[on.name].stepcount = cc++;
    on = planets[on.orbits];
  }

  on = planets[planets["SAN"].orbits];
  while (on.orbits != "") {
    if (on.stepcount > 0) {
      res2 += on.stepcount;
      break;
    }
    res2++;
    on = planets[on.orbits];
  }

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