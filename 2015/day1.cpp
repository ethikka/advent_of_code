#include <iostream>
#include <string>
#include <vector>
#include <iterator>

int main() {
  std::vector<char> input { std::istream_iterator<char>{ std::cin }, {}};
  int currentfloor = 0;
  int steps = 0, basement = 0;
  for(auto& i: input) {
    if      (i == '(') currentfloor++;
    else if (i == ')') currentfloor--;
    steps++;
    if (currentfloor == -1 && basement == 0)
      basement = steps;
  }
  std::cout << "Santa ends up on floor " << currentfloor << " and stepped foot in the basement at " << basement << std::endl;
}
