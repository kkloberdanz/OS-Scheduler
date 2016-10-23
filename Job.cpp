#include "Job.hpp"
#include "helpers.hpp"

Job::Job() {
    ;
}

void Job::build_from_file(const char* filename) {
    std::ifstream input_file;
    input_file.open(filename);

    std::string line;
    size_t t_arrival = 0;
    size_t t_execution = 0;


    // first line of input file will be the number of jobs
    getline(input_file, line);
    //const size_t number_of_jobs = as_int(line);
    total_jobs = as_int(line);

    // Read from input file
    size_t order = 0;
    while (getline(input_file, line)) { 
        if (is_num(line)) { 
            t_arrival = as_int(line);
            getline(input_file, line);
            t_execution = as_int(line);

            push_job(order, t_arrival, t_execution);
            order++;
        }
    }
}

void Job::push_job(size_t order, size_t t_arrival, size_t t_execution) {
    struct job j;
    j.t_arrival = t_arrival;
    j.t_execution = t_execution;
    j.order = order;
    j.t_exe_d = t_execution;
    j.started = false;

    jobs_v.push_back(j);
}

void Job::print_jobs() {
    for (auto j : jobs_v) {
        std::cout << "order    : " << j.order <<  std::endl;
        std::cout << "arrival  : " << j.t_arrival <<  std::endl;
        std::cout << "execution: " << j.t_execution << std::endl;
        std::cout << "exe_d    : " << j.t_exe_d << std::endl;
        std::cout << "started  : " << j.started << std::endl;
        std::cout << std::endl;
    }
}

void Job::print_avg_time(size_t t_turnaround, size_t t_total_response) {
    printf("%.5f\n", ((double)t_turnaround / (double)total_jobs));
    printf("%.5f\n", ((double)t_total_response / (double)total_jobs));
}

void Job::run_fcfs() {
    fcfs_sort();

    double t_current = 0;
    double t_total_response = 0;
    double t_turnaround = 0;
    for (auto j: jobs_v) { 
        if (j.t_arrival > t_current) {
            t_current = j.t_arrival;
        }
        t_total_response += t_current - j.t_arrival;
        t_current        += j.t_execution;
        t_turnaround     += t_current - j.t_arrival;

#ifdef DEBUG
        std::cout << "current   : " << t_current << std::endl;
        std::cout << "response  : " << t_total_response << std::endl;
        std::cout << "turnaround: " << t_turnaround << std::endl;
        std::cout  << std::endl;
#endif
    } 
    print_avg_time(t_turnaround, t_total_response);
}

void Job::print_job_heap() {
    struct job j;
    while (!min_h.empty()) {
        j = min_h.get_front();
        std::cout << "t_arrival  : " << j.t_arrival << std::endl;
        std::cout << "t_execution: " << j.t_execution << std::endl;
        min_h.pop();
    }
}

void Job::run_sjf() {
    sjf_sort(); 
    struct job current_job;
    size_t t_current = 0;
    size_t t_turnaround = 0;
    size_t t_total_response = 0;

    while ((not min_h.empty()) || (not jobs_v.empty()) ) {

        if (not min_h.empty() && not jobs_v.empty()) {
            get_jobs(t_current);

        } else if ((not jobs_v.empty()) && (min_h.empty())) {
            if (jobs_v.back().t_arrival > t_current) {
                t_current = jobs_v.at(jobs_v.size() - 1).t_arrival;
            }
            get_jobs(t_current);
        }

        current_job = min_h.get_front();
        min_h.pop();

        if (current_job.t_arrival > t_current) {
            t_current = current_job.t_arrival;
        }

        t_total_response += t_current - current_job.t_arrival;
        t_current        += current_job.t_execution;
        t_turnaround     += t_current - current_job.t_arrival; 

    } 

    print_avg_time(t_turnaround, t_total_response);
}

void Job::get_jobs(size_t t_current) {
    //std::cout << "current time: " << t_current << std::endl;
    //std::cout << "job arrival time: " << jobs_v.back().t_arrival << std::endl;
    while ((not jobs_v.empty()) && 
            jobs_v.back().t_arrival <= t_current) {

            //std::cout << "here" << std::endl;
        min_h.add(jobs_v.at(jobs_v.size()-1));
        jobs_v.pop_back();
    }
}

void Job::run_stcf() {
    stcf_sort(); 
    struct job current_job;
    size_t t_current = 0;
    size_t t_turnaround = 0;
    size_t t_total_response = 0;

    while ((not min_h.empty()) || (not jobs_v.empty()) ) {

        if (not jobs_v.empty()) {
            get_jobs(t_current);
        }

        if (not min_h.empty()) {

            if (not min_h.peek().started) {
                t_total_response += t_current - min_h.peek().t_arrival;

                struct job tmp_job = min_h.peek();
                min_h.pop();
                tmp_job.started = true;
                min_h.add(tmp_job);
            }

            current_job = min_h.peek();
            min_h.pop();

            if (current_job.t_exe_d == 0) { 
                t_turnaround += t_current - current_job.t_arrival; 

            } else {
                current_job.t_exe_d--;
                t_current++;
                min_h.add(current_job);
            }
        } else {
            t_current++;
        }
    }
    print_avg_time(t_turnaround, t_total_response);
}

void Job::print_job(struct job j) {
    std::cout << "order      : " << j.order << std::endl;
    std::cout << "t_arrival  : " << j.t_arrival << std::endl;
    std::cout << "t_execution: " << j.t_execution << std::endl;
    std::cout << "t_exe_d    : " << j.t_exe_d << std::endl;
    std::cout << "started    : " << j.started << std::endl;
    std::cout << std::endl;
}

void Job::fcfs_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), fcfs_sort_by);
}

void Job::sjf_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), sjf_sort_by);
}

void Job::stcf_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), stcf_sort_by);
}

bool Job::fcfs_sort_by(struct job j1, struct job j2) {
    if (j1.t_arrival == j2.t_arrival) {
        return j1.order < j2.order;
    } else {
        return j1.t_arrival < j2.t_arrival;
    }
}

bool Job::sjf_sort_by(struct job j1, struct job j2) { 
    /*
    if ((j1.t_arrival != j2.t_arrival) && 
        (j1.t_execution == j2.t_execution)) {
        return j1.t_arrival < j2.t_arrival;
    } else {
        return j1.t_execution < j2.t_execution;
    }
    */
    /*
    if ((j1.t_arrival != j2.t_arrival) && 
        (j1.t_execution == j2.t_execution)) {
        return j1.t_arrival > j2.t_arrival;
    } else {
        return j1.t_execution > j2.t_execution;
    }
    */
    //return j1.t_arrival > j2.t_arrival;
    if (j1.t_arrival == j2.t_arrival) {
        return j1.t_execution > j2.t_execution;
    } else {
        return j1.t_arrival > j2.t_arrival;
    }
}

bool Job::stcf_sort_by(struct job j1, struct job j2) {
    return sjf_sort_by(j1, j2);
}


