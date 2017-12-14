#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>

std::ostream& operator<<(std::ostream& os, const __int128 i) noexcept
{
	  std::ostream::sentry s(os);
		  if (s) {
				    unsigned __int128 tmp = i < 0 ? -i : i;
						    char buffer[128];
								    char *d = std::end(buffer);
										    do {
													      --d;
																      *d = "0123456789"[tmp % 10];
																			      tmp /= 10;
																						    } while (tmp != 0);
												    if (i < 0) {
															      --d;
																		      *d = '-';
																					    }
												    int len = std::end(buffer) - d;
														    if (os.rdbuf()->sputn(d, len) != len) {
																	      os.setstate(std::ios_base::badbit);
																				    }
																  }
			  return os;
}

__int128 redist(std::vector<int>& memcubes) {
	// find first highest number
	
	return 0;

}

int main() {
	std::vector<int> memcubes {std::istream_iterator<int>{std::cin}, {}};
	__int128 currentstate = 0, initialstate = 0;
	for(int i = 0; i < memcubes.size(); i++) {
		initialstate += (__int128)memcubes[i] << (i * 16);
	}
  currentstate = initialstate;
	std::map<__int128,int> states;
	std::cout << initialstate << std::endl;
	for(auto& i: memcubes) {
		std::cout << i << std::endl;
	}
}
