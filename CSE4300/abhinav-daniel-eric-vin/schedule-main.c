#include "process.h"
#include <stdio.h>
#include <stdlib.h>

void scheduleMain(struct process **procArray, int procArraySize, int maxTimesteps) {

    //create arrays for each queue level
    struct process **RRQueue = malloc(procArraySize * sizeof(int*)); //set all to nullptr
    struct process **STCFQueue = malloc(procArraySize * sizeof(int*));
    struct process **FIFOQueue = malloc(procArraySize * sizeof(int*));
    struct process **SJFQueue = malloc(procArraySize * sizeof(int*));

    for(int i=0; i<procArraySize; i++) {
        RRQueue[i] = NULL;
        STCFQueue[i] = NULL;
        FIFOQueue[i] = NULL;
        SJFQueue[i] = NULL;
    }

    //array to keep track of empty/non-empty queues - empty by default
    int emptyQueues[] = {
        1, //RoundRobin
        1, //STCF
        1, //FIFO
        1  //SJF
    };

    int t = 0; //central time counter - represents ms
    while (t < maxTimesteps) {

        //simulate some queueing & scheduling VV

        //iterate through procArray to find newly arriving processes
        for(int i=0; i<procArraySize; i++) {
            if (procArray[i]->arrivalTime == t) {
                if (procArray[i]->priority == 1) {
                    //round robin
                }
            }
        }

        //add new processes to appropriate queue & update emptyQueues array

        //execute processes based on the highest non-empty queue

        t++; //increment time (based on type of algorithm)

    }


}
