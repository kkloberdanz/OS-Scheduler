#include "Job.hpp"

void Job::build_from_file(const char* filename) {
    std::ifstream input_file;
    input_file.open(filename);

    std::string line;
    size_t t_arrival = 0;
    size_t t_execution = 0;


    // first line of input file will be the number of jobs
    getline(input_file, line);
    const size_t number_of_jobs = as_int(line);
    //std::cout << number_of_jobs << std::endl;

    // Read from input file
    size_t order = 0;
    //Job j;
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

    jobs_v.push_back(j);
}

void Job::print_jobs() {
    for (auto j : jobs_v) {
        std::cout << "order    : " << j.order <<  std::endl;
        std::cout << "arrival  : " << j.t_arrival <<  std::endl;
        std::cout << "execution: " << j.t_execution << std::endl;
        std::cout << std::endl;
    }
}

void Job::run() {
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
    printf("%.5f\n", (t_turnaround / jobs_v.size()));
    printf("%.5f\n", (t_total_response / jobs_v.size()));
}

void Job::run_sjf() {
    sjf_sort();


}

void Job::fcfs_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), fcfs_sort_by);
}

void Job::sjf_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), sjf_sort_by);
}

void Job::stfc_sort() {
    std::sort(jobs_v.begin(), jobs_v.end(), stfc_sort_by);
}

bool Job::fcfs_sort_by(struct job j1, struct job j2) {
    if (j1.t_arrival == j2.t_arrival) {
        return j1.order < j2.order;
    } else {
        return j1.t_arrival < j2.t_arrival;
    }
}

bool Job::sjf_sort_by(struct job j1, struct job j2) { 
    if ((j1.t_arrival != j2.t_arrival) && 
        (j1.t_execution == j2.t_execution)) {
        return j1.t_arrival < j2.t_arrival;
    } else {
        return j1.t_execution < j2.t_execution;
    }
}

    /*
bool Job::sjf_sort_by_test(struct job j1, struct job j2) {
    if (j1.t_arrival == j2.t_arrival) {
        return j1.t_execution < j2.t_execution;
    } else {
        return j1.t_arrival < j2.t_arrival;
    }
}
*/

bool Job::stfc_sort_by(struct job j1, struct job j2) {
    // TODO:
    // This is a placeholder, AND IS NOT CORRECT!
    return j1.t_execution < j2.t_execution;
}

