#include <stdio.h>
#include "thread.h"

//compile with gcc -o test test.c FIFO.c SJF.c

//functions
void fifo(struct thread* jobs, int numjobs);
void sjf_scheduler(struct thread* jobs, int num_jobs);

int main() {
    // Test Case 1: Basic
    printf("TEST CASE 1: Basic 3 Jobs\n");
    struct thread jobs1[] = {
        { .thread_ID = 1, .arrival = 0, .burst = 10, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 2, .arrival = 2, .burst = 4, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 3, .arrival = 4, .burst = 6, .turnaround = 0, .response = 0, .wait = 0 }
    };

    int num_jobs1 = sizeof(jobs1) / sizeof(jobs1[0]);
    struct thread jobs1_fifo[3];
    struct thread jobs1_sjf[3];
    
    for (int i = 0; i < num_jobs1; i++) {
        jobs1_fifo[i] = jobs1[i];
        jobs1_sjf[i] = jobs1[i];
    }

    printf("SJF Scheduler:\n");
    sjf_scheduler(jobs1_sjf, num_jobs1);
    for (int i = 0; i < num_jobs1; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs1_sjf[i].thread_ID, jobs1_sjf[i].arrival, jobs1_sjf[i].burst, 
            jobs1_sjf[i].turnaround, jobs1_sjf[i].response, jobs1_sjf[i].wait);
    }

    printf("\nFIFO Scheduler:\n");
    fifo(jobs1_fifo, num_jobs1);
    for (int i = 0; i < num_jobs1; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs1_fifo[i].thread_ID, jobs1_fifo[i].arrival, jobs1_fifo[i].burst,
            jobs1_fifo[i].turnaround, jobs1_fifo[i].response, jobs1_fifo[i].wait);
    }

    // Test Case 2: Same arrival time
    printf("\nTEST CASE 2: Same Arrival Time\n");
    struct thread jobs2[] = {
        { .thread_ID = 1, .arrival = 0, .burst = 8, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 2, .arrival = 0, .burst = 4, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 3, .arrival = 0, .burst = 9, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 4, .arrival = 0, .burst = 5, .turnaround = 0, .response = 0, .wait = 0 }
    };

    int num_jobs2 = sizeof(jobs2) / sizeof(jobs2[0]);
    struct thread jobs2_fifo[4];
    struct thread jobs2_sjf[4];
    
    for (int i = 0; i < num_jobs2; i++) {
        jobs2_fifo[i] = jobs2[i];
        jobs2_sjf[i] = jobs2[i];
    }

    printf("SJF Scheduler:\n");
    sjf_scheduler(jobs2_sjf, num_jobs2);
    for (int i = 0; i < num_jobs2; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs2_sjf[i].thread_ID, jobs2_sjf[i].arrival, jobs2_sjf[i].burst, 
            jobs2_sjf[i].turnaround, jobs2_sjf[i].response, jobs2_sjf[i].wait);
    }

    printf("\nFIFO Scheduler:\n");
    fifo(jobs2_fifo, num_jobs2);
    for (int i = 0; i < num_jobs2; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs2_fifo[i].thread_ID, jobs2_fifo[i].arrival, jobs2_fifo[i].burst,
            jobs2_fifo[i].turnaround, jobs2_fifo[i].response, jobs2_fifo[i].wait);
    }

    // Test Case 3: Short job arrives later
    printf("\nTEST CASE 3: Short Job Arrives Later\n");
    struct thread jobs3[] = {
        { .thread_ID = 1, .arrival = 0, .burst = 10, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 2, .arrival = 1, .burst = 1, .turnaround = 0, .response = 0, .wait = 0 },
        { .thread_ID = 3, .arrival = 2, .burst = 8, .turnaround = 0, .response = 0, .wait = 0 }
    };

    int num_jobs3 = sizeof(jobs3) / sizeof(jobs3[0]);
    struct thread jobs3_fifo[3];
    struct thread jobs3_sjf[3];
    
    for (int i = 0; i < num_jobs3; i++) {
        jobs3_fifo[i] = jobs3[i];
        jobs3_sjf[i] = jobs3[i];
    }

    printf("SJF Scheduler:\n");
    sjf_scheduler(jobs3_sjf, num_jobs3);
    for (int i = 0; i < num_jobs3; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs3_sjf[i].thread_ID, jobs3_sjf[i].arrival, jobs3_sjf[i].burst, 
            jobs3_sjf[i].turnaround, jobs3_sjf[i].response, jobs3_sjf[i].wait);
    }

    printf("\nFIFO Scheduler:\n");
    fifo(jobs3_fifo, num_jobs3);
    for (int i = 0; i < num_jobs3; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs3_fifo[i].thread_ID, jobs3_fifo[i].arrival, jobs3_fifo[i].burst,
            jobs3_fifo[i].turnaround, jobs3_fifo[i].response, jobs3_fifo[i].wait);
    }

    // Test Case 4: Single job
    printf("\nTEST CASE 4: Single Job\n");
    struct thread jobs4[] = {
        { .thread_ID = 1, .arrival = 0, .burst = 5, .turnaround = 0, .response = 0, .wait = 0 }
    };

    int num_jobs4 = sizeof(jobs4) / sizeof(jobs4[0]);
    struct thread jobs4_fifo[1];
    struct thread jobs4_sjf[1];
    
    for (int i = 0; i < num_jobs4; i++) {
        jobs4_fifo[i] = jobs4[i];
        jobs4_sjf[i] = jobs4[i];
    }

    printf("SJF Scheduler:\n");
    sjf_scheduler(jobs4_sjf, num_jobs4);
    for (int i = 0; i < num_jobs4; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs4_sjf[i].thread_ID, jobs4_sjf[i].arrival, jobs4_sjf[i].burst, 
            jobs4_sjf[i].turnaround, jobs4_sjf[i].response, jobs4_sjf[i].wait);
    }

    printf("\nFIFO Scheduler:\n");
    fifo(jobs4_fifo, num_jobs4);
    for (int i = 0; i < num_jobs4; i++) {
        printf("Job ID %d: arrival=%d, burst=%d, turnaround=%d, response=%d, wait=%d\n",
            jobs4_fifo[i].thread_ID, jobs4_fifo[i].arrival, jobs4_fifo[i].burst,
            jobs4_fifo[i].turnaround, jobs4_fifo[i].response, jobs4_fifo[i].wait);
    }

    return 0;
}
