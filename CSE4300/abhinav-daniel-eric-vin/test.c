struct process{
    int remainingTime;
    int arrival;
}

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
    
    fifo(processes,3);
    sjf(processes,3);
    srtcf(processes,3);
    rr(processes,3,1);

}