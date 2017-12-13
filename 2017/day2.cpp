#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

int main() {
  std::string str;
  int resa = 0;
  int resb = 0;
  while (std::getline( std::cin, str))
  {
    std::istringstream ss(str);
    std::istream_iterator<std::string> begin(ss), end;
    std::vector<std::string> arrayTokens(begin, end);
    int min = -1;
    int max = -1;
    for ( int i = 0; i < arrayTokens.size(); i++)
    {
      if (max == -1 || max < std::stoi(arrayTokens[i])) max = std::stoi(arrayTokens[i]);
      if (min == -1 || min > std::stoi(arrayTokens[i])) min = std::stoi(arrayTokens[i]);

      for ( int j = i+1; j < arrayTokens.size(); j++)
      {
        int ii = std::stoi(arrayTokens[i]);
        int jj = std::stoi(arrayTokens[j]);
        if ((ii % jj) == 0)
        {
          resb += (ii / jj);
          break;
        }
        if ((jj % ii) == 0)
        {
          resb += (jj / ii);
          break;
        }
      }
    }
    resa += std::abs(max - min);
  }
  std::cout << "Result part 1: " << resa << std::endl << "Result part 2: " << resb << std::endl;
}
