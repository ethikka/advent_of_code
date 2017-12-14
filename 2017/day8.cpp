#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <chrono>

void solve(void) {
  std::map<std::string,int> registers;
  std::string line;
  int highest = 0, alltimehighest = 0;
  while (getline(std::cin, line)) {
    std::string targetregister, targetoperation, noop, testregister, testoperation;
    int targetnumber, testnumber;
    std::istringstream ssl(line);

    ssl >> targetregister >> targetoperation >> targetnumber >> noop >> testregister >> testoperation >> testnumber;

    if (registers.find(testregister  ) == registers.end()) registers[testregister]   = 0;
    if (registers.find(targetregister) == registers.end()) registers[targetregister] = 0;

    bool validinstruction = false;
    if        (testoperation == "==") { validinstruction = (registers[testregister] == testnumber);
    } else if (testoperation == "!=") { validinstruction = (registers[testregister] != testnumber);
    } else if (testoperation == ">=") { validinstruction = (registers[testregister] >= testnumber);
    } else if (testoperation == "<=") { validinstruction = (registers[testregister] <= testnumber);
    } else if (testoperation == ">" ) { validinstruction = (registers[testregister] >  testnumber);
    } else if (testoperation == "<" ) { validinstruction = (registers[testregister] <  testnumber);
    };
    if (validinstruction)
      registers[targetregister] += (targetnumber * ((targetoperation == "dec") ? -1 : 1));

    for (auto& i: registers) if (i.second > alltimehighest) alltimehighest = i.second;
  }
  for (auto& i: registers) if (i.second > highest) highest = i.second;
  std::cout << "Solution a: " << highest << std::endl << "Solution b: " << alltimehighest << std::endl;
}

int main(void) {
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

