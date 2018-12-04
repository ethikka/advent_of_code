#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

struct guardfreq {
	int guardNo;
	int totalSleep;
	std::map<int,int> snoozeTimes;
};

void solve() {
  std::string line;
  int res1(0), res2(0);
  std::map<int,guardfreq> stats;
  int _guardNo, _startTime, _endTime;
  while (std::getline(std::cin, line)) {
    switch (line[19]) {
      case 'G': {
		  std::string guard = line.substr(line.find('#')+1, 255);
                  guard.replace(guard.end()-13, guard.end(), "");
		  _guardNo = stoi(guard); 
		  break;
		}
      case 'f': _startTime = stoi(line.substr(15,2));
		break;
      case 'w': {
		  _endTime = stoi(line.substr(15,2));
  		  if (stats.count(_guardNo) == 0) {
	            guardfreq fr;
 		    stats.emplace(_guardNo, fr);
		    stats[_guardNo].guardNo = _guardNo;
		  }

		  for (int j = _startTime; j < _endTime; j++) {
	            if (stats[_guardNo].snoozeTimes.count(j) == 0) stats[_guardNo].snoozeTimes[j] = 0;
		    stats[_guardNo].snoozeTimes[j]++;
		  }
		  stats[_guardNo].totalSleep += (_endTime - _startTime);
		  break;
		}
    }
  }

  // Part 1
  int g = 0, s = 0;
  for(auto f: stats) {
    if (s < f.second.totalSleep) {
      g = f.second.guardNo;
      s = f.second.totalSleep;
    }
  }
  int d = 0, dt = 0;
  for(auto f: stats[g].snoozeTimes) {
	  if (f.second > dt) {
		  dt = f.second;
		  d = f.first;
	  }
  }
  res1 = g * d;
  
  // Part 2
  int ms = 0, m = 0, g2 = 0;
  for (auto f: stats) {
    for (auto s: stats[f.first].snoozeTimes) {
      //
      if (s.second > ms) {
        ms = s.second;
	m = s.first;
	g2 = f.first;
      }
    }
  }
  res2 = g2 * m;


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

