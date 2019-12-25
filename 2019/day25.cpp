#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include "intcode.h"

void solve() {
  int res1(0), res2(0);
  intcode interpreter("./2019/fileinput.day25");

  while (!interpreter.halted()) {
    std::string cmd;
    auto m = interpreter.run();
    while (interpreter.has_output())
      std::cout << (char) interpreter.output();
    if (m == inputMode) {
      bool d(false);
      while (!d) {
        cmd = "";
        std::getline(std::cin, cmd);
        if      (cmd == "stack")  interpreter.print_stack();
        else if (cmd == "snapshot") interpreter.dump();
        else                      d = true;
      }
      interpreter.inputqueue_text({cmd});
    }
    m = interpreter.run();
  }
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

