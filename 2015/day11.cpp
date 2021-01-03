#include <sstream>
#include "../common/lib.h"

std::string next_pass(std::string pass) {
  std::string res(pass);
  bool upped(false);
  for (int i = 7; i >= 0 && !upped; i--) {
    if (res[i] == 'z') {
      res[i] = 'a';
      continue;
    } 
    res[i] = (char)((int)res[i]+1);
    upped = true;
  }
  return res;
};

bool checkpass(std::string password) {
    bool valid(false);
    int dbls(0);
    char dd;
    for (int i=0; i < 6; i++) valid |= (((int)password[i+1]-(int)password[i]) == 1) && (((int)password[i+2]-(int)password[i+1]) == 1);
    if (valid) for (int i=0; i < 8; i++) valid &= ((password[i] != 'i') && (password[i] != 'o') && (password[i] != 'l'));
    if (valid) {
      for (int i=0; i < 7; i++) {
        if (password[i] == password[i+1] && password[i] != dd) {
          dd = password[i];
          dbls++; i += 2;
        }
      }
      valid &= (dbls == 2);
    }
  return valid;
};

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res{0,0};
  std::string currentpass("hxbxwxba");
  while (res.first < 2) {
    currentpass = next_pass(currentpass);
    if (checkpass(currentpass)) {
      if (!output_for_timing)
        std::cout << currentpass << std::endl;
      res.first++;
    }
  }
  return res;
}