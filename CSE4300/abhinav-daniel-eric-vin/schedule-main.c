#include "process.h"
#include <stdio.h>

void scheduleMain(struct process **procArray, int procArraySize, int maxTimesteps) {

    //array to keep track of empty/non-empty queues
    int emptyQueues[] = {
        0, //RoundRobin
        0, //STCF
        0, //FIFO
        0  //SJF
    };


    int t = 0; //central time counter
    while (t < maxTimesteps) {

        //simulate some queueing & scheduling VV

        //iterate through procArray to find newly arriving processes

        //add new processes to appropriate queue & update emptyQueues array

        //execute processes based on the highest non-empty queue

        t++; //increment time (based on type of algorithm)

    }


}