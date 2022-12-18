#include <vector>

namespace tbb {
  template <class T> class circularlist {
    private:
      std::vector<T> buffer; 
      int head = 0;
    public:
      void enqueue(T item) { buffer.push_back(item);}
      void enqueue(std::vector<T> items) { for (auto i: items) buffer.push_back(i);}
      void next() { head = (head + 1) % buffer.size(); }
      T front() { return buffer[head]; }
      T front_and_next() { int oh(head); head = (head + 1) % buffer.size(); return buffer[oh]; }
      size_t size() { return buffer.size(); }  
  };
}