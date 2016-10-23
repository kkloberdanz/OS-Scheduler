#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Job.hpp"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "error: specify an input file" << std::endl;
        exit(EXIT_FAILURE);
    }

    Job j;
    j.build_from_file(argv[1]);
    
#ifdef DEBUG
    std::cout << "Before sorting:" << std::endl;
    j.print_jobs();
    std::cout << "---------------" << std::endl;

    std::cout << "After sorting:" << std::endl;
    j.fcfs_sort();
    j.print_jobs();
    std::cout << "---------------" << std::endl;
#endif

    j.run_sjf();

    return 0;
}
