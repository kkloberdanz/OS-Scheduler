#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

namespace kgk {
template <typename T>
class Min_heap {
  public:
    Min_heap() {
        ;
    }

    Min_heap(std::vector<T> v) {
        Min_heap(v, compare);
    }


    Min_heap(std::vector<T> v, bool(*custom_compare) (T, T)) {
        for (T item: v) {
            heap_v.push_back(item);
        }
        make_heap(heap_v.begin(), heap_v.end(), custom_compare);
    }


    T peek() {
        if (heap_v.empty()) {
            std::cout << "error: peeking at an empty heap" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return heap_v.front();
    } 


    void add(T item, bool(*custom_compare) (T, T)) { 
        heap_v.push_back(item); 
        std::push_heap(heap_v.begin(), heap_v.end(), custom_compare);
    }

    void add(T item) {
        add(item, compare);
    }

    void add(std::vector<T> v) {
        add(v, compare);
    }

    void add(std::vector<T> v, bool(*custom_compare) (T, T)) {
        for (T item : v) {
            add(item);
        } 
    }

    T pop(bool(*custom_compare) (T, T)) {
        if (not heap_v.empty()) {
            T tmp = heap_v.back();
            std::pop_heap(heap_v.begin(), heap_v.end(), custom_compare); 
            heap_v.pop_back();
            return tmp;
        } else {
            std::cout << "Min_heap error: popping an empty heap" 
                << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    T pop() {
        return pop(compare);
    }


    bool empty() {
        return heap_v.empty();
    }

    size_t size() {
        return heap_v.size();
    }

  private:

    static bool compare(T a, T b) {
        return a < b;
    }

    std::vector<T> heap_v;
};
} // namespace kgk

#endif // MIN_HEAP_HPP
