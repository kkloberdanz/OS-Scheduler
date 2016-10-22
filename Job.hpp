#ifndef JOB_HPP
#define JOB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include <stdio.h>

#include "helpers.hpp"

class Job {
  public:

    void build_from_file(const char*);

    void push_job(size_t order, size_t t_arrival, size_t t_execution);

    void print_jobs();

    void run();

    void run_fcfs();

    void run_sjf();

    void fcfs_sort();

    void sjf_sort();

    void stfc_sort();
    
  private: 
    struct job {
        size_t t_arrival;
        size_t t_execution; 
        size_t order;
    };

    static bool fcfs_sort_by(struct job j1, struct job j2);

    static bool sjf_sort_by(struct job j1, struct job j2);

    //static bool sjf_sort_by_test(struct job j1, struct job j2);

    static bool stfc_sort_by(struct job j1, struct job j2);

    std::vector<struct job> jobs_v;
};

#endif
