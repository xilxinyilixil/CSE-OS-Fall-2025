#include "process.h"
#include "rr.h"

static time = 0;
int tq = 1; //time quantum

void rr(struct process **procArray, int procArraySize, int globalTime){
    int turn = time%procArraySize;
    procArray[turn] -> remainingTime -= 1;
    if(procArray[turn] -> remainingTime <= 0){
        procArray[turn] -> finishTime = time;
    }

}