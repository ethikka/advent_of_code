#include <sstream>
#include <vector>
#include <map>
#include "../common/lib.h"
#include "../common/vector2.h"
#include "../common/vector3.h"

struct vec3 { int x, y, z; };
struct block { vec3 mn, mx; };

bool operator==(const vec3& a, const vec3& b){ return a.x == b.x && a.y == b.y; }
struct pos_hash { size_t operator()(const vec3& pos) const { return (pos.x + pos.y + 1) * (pos.x + pos.y) / 2 + pos.y; }};

using height_map_t = std::unordered_map<vec3, int, pos_hash>;

void move_block(block& block, height_map_t& height_map) {
  int max_height_seen = 0;
  for(int y=block.mn.y; y<=block.mx.y; ++y) for(int x=block.mn.x; x<=block.mx.x; ++x) max_height_seen = std::max(height_map[{x,y}], max_height_seen);
  int move = std::max(block.mn.z - max_height_seen - 1, 0);
  block.mn.z -= move;
  block.mx.z -= move;
}

std::vector<block> move_blocks(std::vector<block> blocks, int exclude_box = -1) {
  height_map_t height_map;
  for(int i = 0; i < blocks.size(); ++i)
    if(i != exclude_box) {
      auto& box = blocks[i];
      move_block(box, height_map);
      for(int y=box.mn.y; y<=box.mx.y; ++y) for(int x=box.mn.x; x<=box.mx.x; ++x) height_map[{x,y}] = box.mx.z;
    }
  return blocks;
};

int64_t part1(const std::vector<block>& blocks) {
  auto settled_blocks = move_blocks(blocks);
  int64_t stable = blocks.size();
  for(int i = 0; i<blocks.size(); ++i) {
    auto new_settled_blocks = move_blocks(settled_blocks, i);
    for(int j = 0; j<settled_blocks.size(); ++j){
      if(j != i && new_settled_blocks[j].mn.z != settled_blocks[j].mn.z){
        stable--; // we have a diff therefore not stable
        break;
      }
    }
  }
  return stable;
}

int64_t part2(const std::vector<block>& blocks) {
  auto settled_blocks = move_blocks(blocks);
  int64_t fall_sum = 0;
  for(int i=0; i<blocks.size(); ++i) {
    auto new_settled_blocks = move_blocks(settled_blocks, i);

    for(int j=0; j<settled_blocks.size(); ++j)
      if(j != i && new_settled_blocks[j].mn.z != settled_blocks[j].mn.z) fall_sum++;
  }
  return fall_sum;
}

std::pair<std::uintmax_t,std::uintmax_t> solve() {
  std::pair<std::uintmax_t,std::uintmax_t> res;
  vec3 a,b;
  std::vector<block> blocks;
  char discard;
  while (std::cin >> a.x >> discard >> a.y >> discard >> a.z >> discard >> b.x >> discard >> b.y >> discard >> b.z) blocks.push_back(block{a, b});
  std::sort(blocks.begin(), blocks.end(), [](auto& a, auto& b){ return a.mn.z < b.mn.z; });

  return {part1(blocks), part2(blocks)};
}