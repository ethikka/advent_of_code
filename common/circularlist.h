#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <vector>

namespace tbb {
  template <class T> class circularlist {
    private:
      int head = 0;
    public:
      std::vector<T> buffer; 
      void enqueue(T item) { buffer.push_back(item);}
      void enqueue(std::vector<T> items) { for (auto i: items) buffer.push_back(i);}
      void next() { head = (head + 1) % buffer.size(); }
      T front() { return buffer[head]; }
      T front_and_next() { int oh(head); head = (head + 1) % buffer.size(); return buffer[oh]; }
      size_t size() { return buffer.size(); }  
      std::vector<T> get_raw_vector() { return buffer; }
      int internal_index() { return head; }
  };
}

#endif
