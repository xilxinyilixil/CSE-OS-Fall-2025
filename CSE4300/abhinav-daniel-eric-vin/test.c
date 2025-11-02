#include "process.h"

void testA(){
    struct process processA;
    struct process processB;
    struct process processC;

    processA.remainingTime = 10;
    processB.remainingTime = 3;
    processC.remainingTime = 5;

    processA.arrival = 0;
    processB.arrival = 0;
    processC.arrival = 0;

    struct process processes[] = {processA, processB, processC};
    
    fifo(processes,3); //Third
    sjf(processes,3); ///Fourth
    srtcf(processes,3); //Second highest priority queue
    rr(processes,3,1); //First priority queue

}