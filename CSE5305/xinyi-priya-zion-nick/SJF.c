#include "thread.h"

// Implement sorting alg (buble sort)
void swap(struct thread* a, struct thread* b) {
    struct thread* temp = a;
    a = b;
    b = temp;
}

void bubble(struct thread* jobs, int num_jobs) {
    for (int i = 0; i < num_jobs - 1; i++) {
        for (int j = 0; j < num_jobs - 1; j++) {
            // sort the jobs by their burst time
            if (jobs[i].burst > jobs[j].burst) {swap(&jobs[i], &jobs[j]);}
        }
    }
}

// sort shortest jobs (burst time) using BubbleSort
void sjf_scheduler(struct thread *jobs) {
    int num_jobs = sizeof(jobs) / sizeof(jobs[0]);
    int current_time = 0;

    bubble(jobs, num_jobs);
    for (int i = 0; i < num_jobs; i++) {current_time += jobs[i].burst;}
}