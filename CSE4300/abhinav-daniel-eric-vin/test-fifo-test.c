#include"process.h"
#include <stdio.h>
#include <stdlib.h>
#include "fifo-schedulemain.h"

int main(void) {

    //create array of processes

    struct process *processA = (struct process*)malloc(sizeof(struct process));
    struct process *processB = (struct process*)malloc(sizeof(struct process));
    int procArraySize = 2;

    processA->remainingTime = 6;
    processB->remainingTime = 2;

    processA->arrivalTime = 0;
    processB->arrivalTime = 0;

    processA->priority = 3;
    processB->priority = 3;

    struct process *processArray[] = {processA, processB};

    //run scheduler

    scheduleMain(processArray, procArraySize, 10);


    //print out finish times
    printf("Finish times:\n");
    for(int i=0; i<procArraySize; i++) {
        printf("process %d: %d\n", i, processArray[i]->finishTime);
    }

    free(processA);
    free(processB);


    return 0;
}