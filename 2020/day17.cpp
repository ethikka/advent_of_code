#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "../common/lib.h"

std::vector<glm::ivec4> offsets3{{ -1, -1, -1, 0},  { -1, -1,  0, 0},	{ -1, -1, +1, 0},	{ -1,  0, -1, 0},	{ -1,  0,  0, 0},	{ -1,  0, +1, 0},	{ -1, +1, -1, 0},	{ -1, +1,  0, 0},	{ -1, +1, +1, 0},	
                                 {  0, -1, -1, 0},	{  0, -1,  0, 0},	{  0, -1, +1, 0},	{  0,  0, -1, 0},                  	{  0,  0, +1, 0},	{  0, +1, -1, 0},	{  0, +1,  0, 0},	{  0, +1, +1, 0},	
                                 { +1, -1, -1, 0},	{ +1, -1,  0, 0},	{ +1, -1, +1, 0},	{ +1,  0, -1, 0},	{ +1,  0,  0, 0},	{ +1,  0, +1, 0},	{ +1, +1, -1, 0},	{ +1, +1,  0, 0},	{ +1, +1, +1, 0}};

std::vector<glm::ivec4> offsets4{{-1, -1, -1, -1},	{-1, -1, -1, +0},	{-1, -1, -1, +1},	{-1, -1, +0, -1},	{-1, -1, +0, +0},	{-1, -1, +0, +1},	{-1, -1, +1, -1},	{-1, -1, +1, +0},	{-1, -1, +1, +1},
                                 {-1, +0, -1, -1},	{-1, +0, -1, +0},	{-1, +0, -1, +1},	{-1, +0, +0, -1},	{-1, +0, +0, +0},	{-1, +0, +0, +1},	{-1, +0, +1, -1},	{-1, +0, +1, +0},	{-1, +0, +1, +1},
	                               {-1, +1, -1, -1},	{-1, +1, -1, +0},	{-1, +1, -1, +1},	{-1, +1, +0, -1},	{-1, +1, +0, +0},	{-1, +1, +0, +1},	{-1, +1, +1, -1},	{-1, +1, +1, +0},	{-1, +1, +1, +1},
	                               {+0, -1, -1, -1},	{+0, -1, -1, +0},	{+0, -1, -1, +1},	{+0, -1, +0, -1},	{+0, -1, +0, +0},	{+0, -1, +0, +1},	{+0, -1, +1, -1},	{+0, -1, +1, +0},	{+0, -1, +1, +1},
	                               {+0, +0, -1, -1},	{+0, +0, -1, +0},	{+0, +0, -1, +1},	{+0, +0, +0, -1},	                  {+0, +0, +0, +1},	{+0, +0, +1, -1},	{+0, +0, +1, +0},	{+0, +0, +1, +1},	
	                               {+0, +1, -1, -1},	{+0, +1, -1, +0},	{+0, +1, -1, +1},	{+0, +1, +0, -1},	{+0, +1, +0, +0},	{+0, +1, +0, +1},	{+0, +1, +1, -1},	{+0, +1, +1, +0},	{+0, +1, +1, +1},	
	                               {+1, -1, -1, -1},	{+1, -1, -1, +0},	{+1, -1, -1, +1},	{+1, -1, +0, -1},	{+1, -1, +0, +0},	{+1, -1, +0, +1},	{+1, -1, +1, -1},	{+1, -1, +1, +0},	{+1, -1, +1, +1},
	                               {+1, +0, -1, -1},	{+1, +0, -1, +0},	{+1, +0, -1, +1},	{+1, +0, +0, -1},	{+1, +0, +0, +0},	{+1, +0, +0, +1},	{+1, +0, +1, -1},	{+1, +0, +1, +0},	{+1, +0, +1, +1},
	                               {+1, +1, -1, -1},	{+1, +1, -1, +0},	{+1, +1, -1, +1},	{+1, +1, +0, -1},	{+1, +1, +0, +0},	{+1, +1, +0, +1},	{+1, +1, +1, -1},	{+1, +1, +1, +0},	{+1, +1, +1, +1}};

std::uintmax_t gen(const std::unordered_set<glm::ivec4>& cubes, int generations, std::vector<glm::ivec4> offsets)
{
	std::unordered_set<glm::ivec4> current_gen = cubes;
	for(int cycle = 0; cycle < generations; ++cycle)
	{
		std::unordered_map<glm::ivec4, int> sums;
		for(auto& cc : current_gen)
			for(auto& o : offsets)
				++sums[cc + o];

		std::unordered_set<glm::ivec4> next_gen;
		for(auto& s : sums)
		{
			if(s.second == 2 && current_gen.count(glm::ivec4(s.first)))	next_gen.insert(glm::ivec4(s.first));
			if(s.second == 3)	                                          next_gen.insert(glm::ivec4(s.first));
		}
		current_gen = next_gen;
	}
	return current_gen.size();
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
	std::unordered_set<glm::ivec4> ac;
	std::string line;
	int y(0);
	while(std::getline(std::cin, line))
	{
		for(int x = 0; x < line.size(); ++x)
			if(line[x] == '#') ac.insert({x, y, 0, 0});
		++y;
	}
  res.first = gen(ac, 6, offsets3);
  res.second = gen(ac, 6, offsets4);
  return res;
}
