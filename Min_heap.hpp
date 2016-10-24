#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

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


    T get_front() {
        if (heap_v.empty()) {
            std::cout << "error: peeking at an empty heap" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return heap_v.front();
    }

    T peek() {
        if (heap_v.empty()) {
            std::cout << "error: peeking at an empty heap" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return get_front();
    } 


    void add(T item, bool(*custom_compare) (T, T)) { 
        heap_v.push_back(item); 
        std::push_heap(heap_v.begin(), heap_v.end(), custom_compare);
    }

    void add(T item) {
        add(item, compare);
    }

    void add(std::vector<T> v) {
        for (T item : v) {
            add(item);
        } 
    }

    void pop(bool(*custom_compare) (T, T)) {
        if (not heap_v.empty()) {
            std::pop_heap(heap_v.begin(), heap_v.end(), custom_compare); 
            heap_v.pop_back();
        } else {
            std::cout << "Min_heap error: popping an empty heap" 
                << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void pop() {
        if (not heap_v.empty()) {
          std::pop_heap(heap_v.begin(), heap_v.end(), compare); 
          heap_v.pop_back();
        } else {
          std::cout << "Min_heap error: popping an empty heap" 
            << std::endl;
          std::exit(EXIT_FAILURE);
        }
    }


    bool empty() {
        return heap_v.empty();
    }

    size_t size() {
        return heap_v.size();
    }

  private:

    /*
    static bool compare(T j1, T j2) {
        if (j1.t_exe_d == j2.t_exe_d) {
            if (j1.t_arrival == j2.t_arrival) {
                return j1.order > j2.order;
            } else {
                return j1.t_arrival > j2.t_arrival;
            }
        } else {
            return j1.t_exe_d > j2.t_exe_d;
        }
    }
    */

    static bool compare(T a, T b) {
        return a < b;
    }

    std::vector<T> heap_v;
};

#endif // MIN_HEAP_HPP
