#include "process.h"
#include "schedule-main.c"

void testA(){
    struct process *processA = (struct process*)malloc(sizeof(struct process));
    struct process *processB = (struct process*)malloc(sizeof(struct process));
    struct process *processC = (struct process*)malloc(sizeof(struct process));

    processA->remainingTime = 10;
    processB->remainingTime = 3;
    processC->remainingTime = 5;

    processA->arrival = 0;
    processB->arrival = 0;
    processC->arrival = 0;

    processA->priority = 1;
    processB->priority = 3;
    processC->priority = 3;

    struct process *processes[] = {processA, processB, processC};
           
    schedule_main(processes, 10); //The second variable being max time per priority queue

}