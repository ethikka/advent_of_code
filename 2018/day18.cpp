#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdlib>

/* size of board to check         */ const int  BOARDSIZE(50);
/* make a printout of the board   */ const bool OUTPUTBOARD(false);
/* check for {generations} cycles */ const int  GENERATIONS(1000000000);

int generation(1);
int res1(0), res2(0);

char board[BOARDSIZE][BOARDSIZE];
char snapshot[BOARDSIZE][BOARDSIZE];
int snapshotgen;

void print_board() {
  if (OUTPUTBOARD) {
    std::system("clear");
    std::cout << "Generation: " << generation << std::endl;
  }
  int wood(0), lumberyard(0);
  for (int y = 0; y < BOARDSIZE; y++) {
    for(int x = 0; x < BOARDSIZE; x++) {
      if (OUTPUTBOARD) std::cout << board[y][x];
      if (board[y][x] == '|') wood++;
      if (board[y][x] == '#') lumberyard++;
    }
    if (OUTPUTBOARD) std::cout << std::endl;    
  }
  if (generation == 10) res1 = wood*lumberyard;
  if (generation == GENERATIONS) res2 = wood*lumberyard;
}

int count_adjecant(int x, int y, char type) {
  int res(0);
  for(auto xo: {-1, 0, 1})
    for(auto yo: {-1, 0, 1}) 
      if ((x+xo >= 0) && (x+xo < BOARDSIZE)) 
        if ((y+yo >= 0) && (y+yo < BOARDSIZE)) 
          if (!((xo == 0) && (yo == 0)))
            if (board[y+yo][x+xo] == type)
              res++;
  return res;
}

void create_snapshot() {
  for (int y = 0; y < BOARDSIZE; y++) 
    for(int x = 0; x < BOARDSIZE; x++) 
      snapshot[y][x] = board[y][x];
  snapshotgen = generation;
}

int check_snapshot() {
  for (int y = 0; y < BOARDSIZE; y++) 
    for(int x = 0; x < BOARDSIZE; x++) 
      if (board[y][x] != snapshot[y][x]) return -1;
  return snapshotgen;
}

void advance_board() {
  char tmpboard[BOARDSIZE][BOARDSIZE];
  for (int y = 0; y < BOARDSIZE; y++) 
    for(int x = 0; x < BOARDSIZE; x++) 
      switch(board[y][x]) {
        case '.': tmpboard[y][x] = (count_adjecant(x, y, '|') >= 3) ? '|' : '.'; break;
        case '|': tmpboard[y][x] = (count_adjecant(x, y, '#') >= 3) ? '#' : '|'; break;
        case '#': tmpboard[y][x] = (count_adjecant(x, y, '#') >= 1) && (count_adjecant(x, y, '|') >= 1) ? '#' : '.'; break;
      }
    
  for (int y = 0; y < BOARDSIZE; y++) 
    for(int x = 0; x < BOARDSIZE; x++) 
      board[y][x] = tmpboard[y][x];
  print_board();
}

void solve() {
  std::string line;
  int yy(0);
  while (std::getline(std::cin, line)) {
    int xx(0);
    for(char c: line)
      board[yy][xx++] = c;
    yy++;
  }

  print_board();
  bool fastforwarded(false);
  for (generation; generation <= GENERATIONS; generation++) {
    // after a 1000 GENERATIONS the board has probably stabilized to a repeating pattern
    if ((generation % 1000) == 0) create_snapshot(); 
    if (generation > 1000 && !fastforwarded) {
      int cycled_since = check_snapshot();
      if (cycled_since > 0) {
        int stride = generation - cycled_since;
        generation += ((((GENERATIONS-generation)/stride)-1)*stride);
        fastforwarded = true;
      }
    }
    advance_board();
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

