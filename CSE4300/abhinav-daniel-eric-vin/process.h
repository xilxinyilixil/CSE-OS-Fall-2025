#ifndef PROCESS_H
#define PROCESS_H


struct process{
    int remainingTime;
    int arrival;
    int finishTime;
    int priority; //1 is highest priority
};


#endif

// [1, 1, 1, 0, 0, 1, 1, 1, 1]