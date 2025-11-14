#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

void sjf_scheduler(struct thread* jobs, int num_jobs);

int findNextJob(struct thread* jobs, int numjobs) {
    int minIndex = -1;
    int minTime = 10000000;

    for (int i = 0; i < numjobs; i++) {
        if (!jobs[i].completion_time && jobs[i].arrival < minTime) {
            minTime = jobs[i].arrival;
            minIndex = i;
        }
    }
    return minIndex;
}


void fifo(struct thread* jobs, int numjobs) {
    int time = 0;
    int doneCount = 0;
    int QUANTUM = 10; 

    while (doneCount < numjobs) {
        
        int next = findNextJob(jobs, numjobs);
        if (next == -1) break; 
        //include a clause to check if renaming quantum time is greater than or equal to turnaround_length of next and if not then call sjf on remaining jobs
        if (time < jobs[next].arrival)
            time = jobs[next].arrival;

        jobs[next].first_run = time;
        jobs[next].response = jobs[next].first_run - jobs[next].arrival;


        //QUANTUM 


        //if finishing this jobs exceeds quantum, stop and switch to SJF
        if (time + jobs[next].burst > QUANTUM){
        //update burst
            int executed = QUANTUM - time;
            jobs[next].burst -= executed;
            time = QUANTUM;

            //allocate array for remaining jobs
            struct thread* remaining = malloc(numjobs * sizeof(struct thread));
            if (!remaining) {
                fprintf(stderr, "Memory allocation failed!\n");
                return;
            }
            int rcount = 0; 
            
            for (int i = 0; i < numjobs; i++){
                if (!jobs[i].completion_time){
                    remaining[rcount] = jobs[i];
                    rcount++;
                }
            }

            sjf_scheduler(remaining, rcount);

            //copy results into main job list
            int idx = 0;
            for (int i = 0; i < numjobs; i++){
                if (!jobs[i].completion_time){
                    jobs[i] = remaining[idx];
                    idx++;
                }
            }
            free(remaining);
              

        }

        //Resume
        time += jobs[next].burst;

        jobs[next].completion_time = time;
        jobs[next].turnaround = time - jobs[next].arrival;

        doneCount++;
    }

}
