#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//function to count and sum primes
void countSumPrime(int minNum, int maxNum, long *count, long *sum) {
    (*sum) = 0;
    (*count) = 0;

    for (int i = minNum; i <= maxNum; ++i) {
        //set isPrime to true
        int isPrime = 1; 
        if (i <= 1) {
            //i isnt a prime
            isPrime = 0; 
        } else {
            for (int j = 2; j * j <= i; ++j) {
                if (i % j == 0) {
                    isPrime = 0; 
                    break;
                }
            }
        }
        //if prime increment sum and count
        if (isPrime) {
            (*count)++;
            (*sum) +=i;
        }  
    }
}

int main(int argc, char *argv[]) {
    // check if correct ammount of arguments
    if (argc != 4) {
        printf("error: Invalid number of arguments");
        return 1; 
    }
    //sum and count variables
    long count = 0;
    long sum = 0;

    //pid
    pid_t pid =getpid();

    //ppid
    pid_t ppid = getppid();

    printf("Proccess id: %d\n",pid);

    //binary flag for series or paralell
    int bFlag = atoi(argv[1]);
    int minNum = atoi(argv[2]);
    int maxNum = atoi(argv[3]);

    //increment variable when splitting into 4 child proccesses
    int increment = (maxNum - minNum) / 4;


    if (bFlag != 0) {
        //parralel
        int childpids[4]; //array to store child pids
        int currPid; //current child pid

        //4 child proccess
        for (int i=0; i<4; i++){
            currPid = fork();
            //error check
            if (currPid == -1){
                printf("Error");
                break;
            }else if (currPid == 0){
                //call child proccess
                countSumPrime(minNum + i * increment, minNum + (i + 1) * increment, &count, &sum);
                //print info
                printf("pid: %d, ppid %d - Count and sum of prime numbers between %d and %d are %ld and %ld\n", getpid(), getppid(), minNum + i * increment, minNum + (i + 1) * increment, count, sum);
                return 0;
            }else {
                childpids[i] = currPid; //store child pid
            }
        }

        //wait for all child proccesses
        for (int i = 0; i < 4; i++) {
            waitpid(childpids[i], NULL, 0);
        }


    }else{
        //series
        for (int i=0; i<4; i++){
            //call child procces
            countSumPrime(minNum + i * increment, minNum + (i + 1) * increment, &count, &sum);
            //print info
            printf("pid: %d, ppid %d - Count and sum of prime numbers between %d and %d are %ld and %ld\n", getpid(), getppid(), minNum + i * increment, minNum + (i + 1) * increment, count, sum);
        }
       
    }
    //exit
    return 0; 
}
