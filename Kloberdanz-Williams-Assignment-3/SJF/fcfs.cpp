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
    j.run_fcfs();

    return 0;
}
