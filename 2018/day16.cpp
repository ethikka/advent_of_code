#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <vector>
#include <array>
#include <set>

using registers = std::array<int, 4>;

struct instruction {
  int opcode;
  int a;
  int b;
  int c;
};

struct sample {
  sample(const registers& b4, int op, int a, int b, int c, const registers& aft) : before(b4), opcode(op), a(a), b(b), c(c), after(aft) { }

  registers before;
  int opcode;
  int a;
  int b;
  int c;
  registers after;
};

std::vector<sample> samples;
std::vector<instruction> instructions;

registers simulate(const registers& before, int real_opcode, int a, int b, int c)
{
  registers out = before;
  /* addr */      if(real_opcode == 0)        out[c] = out[a] + out[b];
  /* addi */      else if(real_opcode == 1)   out[c] = out[a] + b;
  /* mulr */      else if(real_opcode == 2)   out[c] = out[a] * out[b];
  /* muli */      else if(real_opcode == 3)   out[c] = out[a] * b;
  /* andr */      else if(real_opcode == 4)   out[c] = out[a] & out[b];
  /* andi */      else if(real_opcode == 5)   out[c] = out[a] & b;
  /* orr */       else if(real_opcode == 6)   out[c] = out[a] | out[b];
  /* ori */       else if(real_opcode == 7)   out[c] = out[a] | b;
  /* setr */      else if(real_opcode == 8)   out[c] = out[a];
  /* seti */      else if(real_opcode == 9)   out[c] = a;
  /* ge (i/r) */  else if(real_opcode == 10)  (a > out[b]) ? out[c] = 1 : out[c] = 0;
  /* ge (r/i) */  else if(real_opcode == 11)  (out[a] > b) ? out[c] = 1 : out[c] = 0;
  /* ge (r/r) */  else if(real_opcode == 12)  (out[a] > out[b]) ? out[c] = 1 : out[c] = 0;
  /* eq (i/r) */  else if(real_opcode == 13)  (a == out[b]) ? out[c] = 1 : out[c] = 0;
  /* eq (r/i) */  else if(real_opcode == 14)  (out[a] == b) ? out[c] = 1 : out[c] = 0;
  /* eq (r/r) */  else if(real_opcode == 15)  (out[a] == out[b]) ? out[c] = 1 : out[c] = 0;
  return out;
}

void solve() {
  std::string line;
  int res1(0), res2(0);
  int samplecount(0);
  bool sampleloader(true);
  while (std::getline(std::cin, line)) {
    if (line[1] == 'e' && sampleloader) {
        int br0, br1, br2, br3;
        sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &br0, &br1, &br2, &br3);
        std::getline(std::cin, line);
        int op, a, b, c;
        sscanf(line.c_str(), "%d %d %d %d", &op, &a, &b, &c);
        std::getline(std::cin, line);
        int ar0, ar1, ar2, ar3;
        sscanf(line.c_str(), "After:  [%d, %d, %d, %d]", &ar0, &ar1, &ar2, &ar3);
        samples.push_back(sample({ br0, br1, br2, br3 }, op, a, b, c, { ar0, ar1, ar2, ar3 }));
        std::getline(std::cin, line);
    } else { 
      sampleloader = false;
      if (line != "\n") {
        instruction i;
        i.opcode = -1;
        sscanf(line.c_str(), "%d %d %d %d", &i.opcode, &i.a, &i.b, &i.c);
        if (i.opcode > -1)
        instructions.push_back(i);
      }
    }
  }
  std::array<std::set<int>,16> opcode_match = {};
  std::vector<int> matches;

  for(auto s: samples) {
    matches.push_back(0);
    for (int op = 0; op < 16; op++) {
      auto out = simulate(s.before, op, s.a, s.b, s.c);
      if (out == s.after) {
        matches.back()++;
        opcode_match[op].insert(s.opcode);
      }
    }
  }
  for(auto m: matches)
    if (m >= 3) res1++;

  // maps from fake to real!
  std::map<int, int> real_opcode_map;

  while(real_opcode_map.size() < 16)
  {
    for(int k = 0; k < 16; k++)
    {
      const auto& fake_matches = opcode_match[k];
      if(fake_matches.size() == 1)
      {
        int fake = *fake_matches.begin();
        real_opcode_map[fake] = k;

        // erase it from the rest.
        for(int m = 0; m < 16; m++)
        {
          if(m == k) continue;
          opcode_match[m].erase(fake);
        }
      }
    }
  }

  registers state = { 0, 0, 0, 0 };
  for(auto i: instructions) {
    state = simulate(state, real_opcode_map[i.opcode], i.a, i.b, i.c);
  }
  res2 = state[0];
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

