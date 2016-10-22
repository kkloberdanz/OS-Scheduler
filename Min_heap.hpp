#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

template <typename T>
class Min_heap {
  public:
    Min_heap() {
        ;
    }

    Min_heap(std::vector<T> v) {
        for (T item: v) {
            heap_v.push_back(item);
        }
        make_heap(heap_v.begin(), heap_v.end(), compare);
    }

    T get_front() {
        return heap_v.front();
    }

    void add(T item) { 
        heap_v.push_back(item); 
        std::push_heap(heap_v.begin(), heap_v.end(), compare);
    }

    void add(std::vector<T> v) {
        for (T item : v) {
            add_to_heap(item);
        } 
    }

    void pop() {
        std::pop_heap(heap_v.begin(), heap_v.end(), compare); 
        heap_v.pop_back();
    }

    bool is_empty() {
        return heap_v.empty();
    }

  private:

    static bool compare(T a, T b) {
        return a.t_execution > b.t_execution;
    }
    std::vector<T> heap_v;
};

#endif // MIN_HEAP_HPP