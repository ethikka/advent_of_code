#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string str;
  getline( std::cin, str);
  int resulta = 0;
  int resultb = 0;
  for(std::string::size_type i = 0; i < str.size(); ++i) {
    if (str[i] == str[(i+1)%str.size()])
      resulta += (int)(str[i] - '0');
    if (str[i] == str[(i+(str.size()/2))%str.size()])
      resultb += (int)(str[i] - '0');
  }
  std::cout << "Result part 1: " << resulta << std::endl << "Result part 2: " << resultb << std::endl;
}

