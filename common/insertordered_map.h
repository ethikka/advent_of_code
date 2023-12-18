#ifndef INSERTORDEREMAP_H
#define INSERTORDEREMAP_H

#include <map>
#include <vector>

namespace tbb {
  template <class K, class V> class insertordered_map {
    private:
      std::map<K,V> elements;
      std::vector<K> order;
    public:
      void push_back(K key, V value) { 
        elements.emplace(key, value); 
        order.push_back(key); 
      };
      
      void erase(K key) {
        elements.erase(key);
        order.erase(std::remove(order.begin(), order.end(), key), order.end()); 
      };

      V& operator[] (K key) {
        if (elements.find(key) == elements.end()) order.push_back(key);
        return elements[key];
      };

      std::vector<std::pair<K,V>> get_map() {
        std::vector<std::pair<K,V>> res;
        for(auto k: order) res.push_back({k, elements[k]});
        return res;
      }
  };
}

#endif