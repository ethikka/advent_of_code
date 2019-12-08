#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <chrono>

void solve() {
  std::cout << "\033[0;0H";
  for (int i = 0; i < 29; i++)
    std::cout << "                                                                                                                                                " << std::endl;
  int width(25), height(6);
  int num[3]{99,99,99};

  char ch[3]{' ','X','.'};
  int framecnt(0), cnt(0), fewest(99999999);
  int image[width*height];
  for (int filler = 0; filler < (width*height); filler++)
    image[filler] = 2;

  int res1(0), res2(0), p(0);
  char c;
  while (std::cin >> c) {
    int p = (int)c-48;

    if (image[framecnt] == 2)
      image[framecnt] = p;

    if ((cnt % (width*height)) == ((width*height)-1)) {
      if (fewest > num[0]) {
        res1 = num[1]*num[2];
        fewest = num[0];
      }
      num[0] = 0; num[1] = 0; num[2] = 0;

      framecnt = -1;
    }
    /* uncomment for visuals! =)
    std::cout << "\033[0;0H";
    for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
        std::cout << ch[image[(row*width)+col]];
      }
      std::cout << std::endl;
    }*/

    num[p]++;
    framecnt++;
    cnt++;
  }

  std::cout << "\033[0;0H";
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      std::cout << ch[image[(row*width)+col]];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

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

