#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

struct Node
{
  std::vector<int> metadata;
  std::vector<Node> children;
};

std::istream &operator>>(std::istream &is, Node &node)
{
  int num_children, num_metadata;
  is >> num_children >> num_metadata;
  if(is.good()) {
      node.children.resize(num_children);
      node.metadata.resize(num_metadata);
      for(auto &child : node.children) is >> child;
      for(auto &data : node.metadata) is >> data;
  }
  return is;
}

int total(const Node &node)
{
  int sum(0);
  for(auto &child: node.children)
    sum+=total(child);
  for(auto &data: node.metadata)
    sum+=data;
  return sum;
}


int value(const Node &node)
{
  int val(0);
  if(node.children.empty()) return total(node);
  for(auto &data: node.metadata) 
      if(data > 0 && data <= node.children.size()) val += value(node.children.at(data-1));
  return val;
}

void solve() {
  Node node;
  std::cin >> node;
  std::cout << "Solution part 1: " << total(node) << std::endl << "Solution part 2: " << value(node) << std::endl;
}

int main(void) {
  std::cout << "Starting..." << std::endl;
  auto start_time = std::chrono::high_resolution_clock::now();
  solve();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Ran for " << ms_count << "ms" << std::endl;
}

