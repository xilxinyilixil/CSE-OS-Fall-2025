#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

//helper: find next FIFO job that has arrived and is unfinished
static int find_next_fifo(struct thread *work, int *remaining, int numjobs, int current_time) {
    int idx = -1;
    int min_arrival = 1<<30;
    for (int i = 0; i < numjobs; i++) {
        if (remaining[i] > 0 && work[i].arrival <= current_time) {
            if (work[i].arrival < min_arrival) {
                min_arrival = work[i].arrival;
                idx = i;
            }
        }
    }
    return idx;
}

//helper: find earliest future arrival among unfinished jobs
static int earliest_future_arrival(struct thread *work, int *remaining, int numjobs, int current_time) {
    int idx = -1;
    int min_arrival = 1<<30;
    for (int i = 0; i < numjobs; i++) {
        if (remaining[i] > 0 && work[i].arrival > current_time) {
            if (work[i].arrival < min_arrival) {
                min_arrival = work[i].arrival;
                idx = i;
            }
        }
    }
    return idx;
}

void hybrid_quantum(struct thread *jobs, int numjobs, int quantum) {
    if (numjobs <= 0) return;

    struct thread *work = malloc(numjobs * sizeof(struct thread));
    int *remaining = malloc(numjobs * sizeof(int));
    if (!work || !remaining) {
        fprintf(stderr, "Memory allocation failed\n");
        free(work);
        free(remaining);
        return;
    }

    for (int i = 0; i < numjobs; i++) {
        work[i] = jobs[i];
        remaining[i] = jobs[i].burst;
        work[i].completion_time = 0;
        work[i].turnaround = 0;
        work[i].wait = 0;
        work[i].first_run = -1;
        work[i].response = 0;
    }

    int time = 0;
    int doneCount = 0;

    //FIFO phase
    while (time < quantum && doneCount < numjobs) {
        int next = find_next_fifo(work, remaining, numjobs, time);
        if (next == -1) {
            int fut = earliest_future_arrival(work, remaining, numjobs, time);
            if (fut == -1) break;
            time = (work[fut].arrival >= quantum) ? quantum : work[fut].arrival;
            continue;
        }

        if (work[next].first_run == -1) {
            work[next].first_run = time;
            work[next].response = work[next].first_run - work[next].arrival;
        }

        int time_available = quantum - time;
        if (remaining[next] <= time_available) {
            time += remaining[next];
            remaining[next] = 0;
            work[next].completion_time = time;
            work[next].turnaround = time - work[next].arrival;
            work[next].wait = work[next].turnaround - work[next].burst;
            doneCount++;
        } else {
            remaining[next] -= time_available;
            time += time_available;
            break;
        }
    }

    if (doneCount < numjobs) {
        //SJF phase
        while (doneCount < numjobs) {
            int chosen = -1;
            int min_rem = 1<<30;
            for (int i = 0; i < numjobs; i++) {
                if (remaining[i] > 0 && work[i].arrival <= time) {
                    if (remaining[i] < min_rem) {
                        min_rem = remaining[i];
                        chosen = i;
                    }
                }
            }

            if (chosen == -1) {
                int fut = earliest_future_arrival(work, remaining, numjobs, time);
                if (fut == -1) break;
                time = work[fut].arrival;
                continue;
            }

            if (work[chosen].first_run == -1) {
                work[chosen].first_run = time;
                work[chosen].response = time - work[chosen].arrival;
            }

            time += remaining[chosen];
            remaining[chosen] = 0;
            work[chosen].completion_time = time;
            work[chosen].turnaround = time - work[chosen].arrival;
            work[chosen].wait = work[chosen].turnaround - work[chosen].burst;
            doneCount++;
        }
    }

    //copy back results
    for (int i = 0; i < numjobs; i++) {
        jobs[i].completion_time = work[i].completion_time;
        jobs[i].turnaround = work[i].turnaround;
        jobs[i].wait = work[i].wait;
        jobs[i].first_run = work[i].first_run;
        jobs[i].response = work[i].response;
    }

    free(work);
    free(remaining);
}
