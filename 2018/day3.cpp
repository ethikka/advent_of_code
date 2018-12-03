#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <set>

void solve() {
  std::string line;
  int res1(0);
  std::string res2;
  std::unordered_map<std::string,std::string> claims;
  while (std::getline(std::cin, line)) {
    std::string claimId, lefttop, claimSize, throwaway;

    std::stringstream ss(line);
    ss >> claimId >> throwaway >> lefttop >> claimSize;

    int startX = stoi(lefttop.substr(0, lefttop.find(",")));
    int startY = stoi(lefttop.substr(lefttop.find(",")+1, 255));
    int widthX = stoi(claimSize.substr(0, claimSize.find("x")));;
    int widthY = stoi(claimSize.substr(claimSize.find("x")+1, 255));;

    for (int x = 0; x < widthX; x++) {
      for (int y = 0; y < widthY; y++) {
        std::string key = std::to_string(startX + x)+"#"+std::to_string(startY + y);
        if (claims.count(key) > 0)
          claims[key] += ","+claimId;
        else
          claims.emplace(key, claimId);
      }
    }
  }

  std::set<std::string> possible_uncontested;

  for (auto f: claims) {
    if (f.second.find(",") != std::string::npos) {
      res1++;
    }
    else {
      possible_uncontested.insert(f.second);
    }
  }
  
  for (auto f: possible_uncontested) {
    bool lonely(true);
    for (auto fi: claims) {
      if (!lonely) break;
      if (fi.second.find(f) != std::string::npos) {
        lonely &= fi.second.find(",") == std::string::npos;
      }
    }
    if (lonely) res2 = f;
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

