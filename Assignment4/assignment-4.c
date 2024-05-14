#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char name[4]; //proccess name
    int arrivalTime; //arrival time
    int burstTime; //burst time
    int waitTime; //wait time
    int turnTime; //turnarround time 
} Process;


//function for FCFS
void FCFS(Process processes[], int numProcesses) {
    printf("First Come First Served\n");
    float totalWaitTime = 0;
    float totalTurnTime = 0;

    // loop for proccesses
    int currentTime = 0;
    for (int i = 0; i < numProcesses; i++) {
        //trunaround and wait time
        processes[i].waitTime = currentTime - processes[i].arrivalTime;
        processes[i].turnTime = processes[i].waitTime; 

        int burstLeft = processes[i].burstTime;
        while (burstLeft > 0) {
            //print stats
            printf("T%d : %s - Burst left %2d, Wait time %2d, Turnaround time %2d\n",
                   currentTime, processes[i].name, burstLeft,
                   processes[i].waitTime, processes[i].waitTime + processes[i].burstTime - burstLeft);

            //decrement burst left and increment time and turnaround
            burstLeft--;
            currentTime++;
            processes[i].turnTime++; 
        }

        //update total wait and turnaround time
        totalWaitTime += processes[i].waitTime;
        totalTurnTime += processes[i].turnTime;

        
    }
     for (int i = 0; i < numProcesses; i++) {
        //print individual process stats
        printf("\n%s\n", processes[i].name);
        printf("\tAverage waiting time:         %d\n", processes[i].waitTime);
        printf("\tAverage turnaround time:      %d\n", processes[i].turnTime);

     }

    //calculate averages
    float avgWaitTime = totalWaitTime / numProcesses;
    float avgTurnTime = totalTurnTime / numProcesses;

    //total averages
    printf("\nTotal average waiting time:     %.1f\n", avgWaitTime);
    printf("Total average turnaround time:  %.1f\n", avgTurnTime);
}


void SJF(Process processes[], int numProcesses) {
   
}
void RR(Process processes[], int numProcesses, int timeQuantum) {
  
}

int main(int argc, char *argv[]) {
    //list to hold processes
    Process processes[20]; 
    //number of proccessses index
    int numProcesses = 0;

    FILE* file = fopen(argv[argc - 1], "r");
    //read in file
    while (fscanf(file, "P%d,%d\n", &processes[numProcesses].arrivalTime, &processes[numProcesses].burstTime) == 2) {
        //formatting
        snprintf(processes[numProcesses].name, sizeof(processes[numProcesses].name), "P%d", numProcesses);
        //initilize wait time and turnaround time
        processes[numProcesses].waitTime = 0;
        processes[numProcesses].turnTime = 0;
        //increment number of processes
        numProcesses++;
    }
    fclose(file);

    //call function based on command line

    //FCFC
    if (strcmp(argv[1], "-f") == 0) {
        FCFS(processes, numProcesses);
    // SJF
    } else if (strcmp(argv[1], "-s") == 0) {
        SJF(processes, numProcesses);
        //didnt do :(
    //RR 
    } else if (strcmp(argv[1], "-r") == 0) {
        int timeQuantum = atoi(argv[2]);
        RR(processes, numProcesses, timeQuantum);
        //didnt do :(
    
    //error
    } else {
        fprintf(stderr, "ERROR\n");
        exit(1);
    }

    return 0;
}
