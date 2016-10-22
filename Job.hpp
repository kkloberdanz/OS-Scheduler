#ifndef JOB_HPP
#define JOB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include <stdio.h>

#include "helpers.hpp"
#include "Min_heap.hpp"

class Job {
  private: 
    struct job {
        size_t t_arrival;
        size_t t_execution; 

        size_t t_first_run;
        size_t t_total_runtime;
        size_t order;
    };

    static bool fcfs_sort_by(struct job j1, struct job j2);

    static bool sjf_sort_by(struct job j1, struct job j2);

    static bool stfc_sort_by(struct job j1, struct job j2);

    std::vector<struct job> jobs_v;

    Min_heap<job> min_h;

    void print_job_heap();
  public:

    Job();

    void build_from_file(const char*);

    void push_job(size_t order, size_t t_arrival, size_t t_execution);

    void print_jobs();

    void run();

    void run_fcfs();

    void run_sjf();

    void fcfs_sort();

    void sjf_sort();

    void stfc_sort();

    void print_job(struct job);

    void get_jobs(size_t);
    
    void print_avg_time(size_t, size_t);
};

#endif
