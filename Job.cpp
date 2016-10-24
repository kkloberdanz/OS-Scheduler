#include "Job.hpp"
#include "helpers.hpp"

Job::Job() {
    ;
}

void Job::build_from_file(const char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");

    std::string line;
    size_t t_arrival = 0; size_t t_execution = 0; 

    // Read from input file
    size_t order = 0;
    char c;
    std::string num_str = "";
    std::vector<std::string> num_v;
    while ( (c = fgetc(fp)) != EOF) {
        if (isdigit(c)) {
            num_str += c;
        } else if (num_str != "") {
            num_v.push_back(num_str);
            num_str = "";
        } else {
            num_str = ""; 
        }
    } 

    if (num_v.size() > 0) { 
        std::reverse(num_v.begin(), num_v.end());

        total_jobs = atoi(num_v.back().c_str());
        num_v.pop_back(); 

        while (not num_v.empty()) { 
            order++;
            t_arrival = atoi(num_v.back().c_str());
            num_v.pop_back(); 
            t_execution = atoi(num_v.back().c_str());
            num_v.pop_back(); 

            push_job(order, t_arrival, t_execution);
        }
    } else {
        push_job(0, 0, 0);
    }

    fclose(fp);
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
    if (total_jobs != 0) {
        printf("%.5f\n", ((double)t_turnaround /     (double)total_jobs));
        printf("%.5f\n", ((double)t_total_response / (double)total_jobs));
    } else { 
        printf("%.5f\n", 0.0);
        printf("%.5f\n", 0.0);
    }
}

void Job::run_fcfs() {

    fcfs_sort();

    size_t t_current = 0;
    size_t t_total_response = 0;
    size_t t_turnaround = 0;
    for (auto j: jobs_v) { 
        if (j.t_arrival > t_current) {
            t_current = j.t_arrival;
        }
        t_total_response += t_current - j.t_arrival;
        t_current        += j.t_execution;
        t_turnaround     += t_current - j.t_arrival;

    } 
    print_avg_time(t_turnaround, t_total_response);
}

void Job::print_job_heap() {
    struct job j;
    while (!min_h.empty()) {
        j = min_h.peek();
        std::cout << "t_arrival  : " << j.t_arrival << std::endl;
        std::cout << "t_execution: " << j.t_execution << std::endl;
        min_h.pop(my_heap_compare);
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
                t_current = jobs_v.back().t_arrival;
            }
            get_jobs(t_current);
        }

        current_job = min_h.peek();
        min_h.pop(my_heap_compare);

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
    while ((not jobs_v.empty()) && 
            jobs_v.back().t_arrival <= t_current) { 
        min_h.add(jobs_v.back(), my_heap_compare);
        jobs_v.pop_back();
    }
}

void Job::run_stcf() {

    struct job current_job;
    size_t t_current = 0;
    size_t t_turnaround = 0;
    size_t t_total_response = 0;

    stcf_sort(); 

    while ((not min_h.empty()) || (not jobs_v.empty()) ) { 

        if (not jobs_v.empty()) {
            get_jobs(t_current);
        }

        if (not min_h.empty()) {

            if (not min_h.peek().started) {
                t_total_response += t_current - min_h.peek().t_arrival;

                struct job tmp_job = min_h.peek();
                min_h.pop(my_heap_compare);
                tmp_job.started = true;
                min_h.add(tmp_job, my_heap_compare);
            }

            current_job = min_h.peek();
            min_h.pop(my_heap_compare);

            if (current_job.t_exe_d == 0) { 
                t_turnaround += t_current - current_job.t_arrival; 

            } else {
                current_job.t_exe_d--;
                t_current++;
                min_h.add(current_job, my_heap_compare);
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
    std::stable_sort(jobs_v.begin(), jobs_v.end(), stcf_sort_by);
}

bool Job::fcfs_sort_by(struct job j1, struct job j2) {
    if (j1.t_arrival == j2.t_arrival) {
        return j1.order < j2.order;
    } else {
        return j1.t_arrival < j2.t_arrival;
    }
}

bool Job::sjf_sort_by(struct job j1, struct job j2) { 
    if (j1.t_arrival == j2.t_arrival) {
        if (j1.t_execution == j2.t_execution) {
            return j1.order > j2.order;
        } else {
            return j1.t_execution > j2.t_execution;
        }
    } else {
        return j1.t_arrival > j2.t_arrival;
    }
}

bool Job::stcf_sort_by(struct job j1, struct job j2) {
    return sjf_sort_by(j1, j2);
}

bool Job::my_heap_compare(struct job j1, struct job j2) {
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
