#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>



int main(int argc, char *argv[]) {
    pid_t pid;

    // check if correct ammount of arguments
    if (argc != 3) {
        printf("error: Invalid number of arguments");
        return 1; 
    }

   
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    //print the values from args
    printf("\nYour integers are %d %d\n", a,b);

    //partition the two numbers
    int a1 = a/100;
    int a2 = a%100;
    int b1 = b/100;
    int b2 = b%100;

    int pTc[2]; //parent writes, child reads
    int cTp[2]; //child writes, parent reads

    // Create pipes
    if (pipe(pTc) == -1 || pipe(cTp) == -1) {
        perror("pipe error");
        exit(0);
    }

    //forking
    pid = fork();
    if (pid < 0){
        perror("fork error");
        exit(0);
    }
    //parent process
    if(pid > 0) {

        
        printf("Parent (PID %d): created child (PID %d)\n\n", getpid(), pid);

        /* 
            CALCULATING X
        */

        printf("###\n# Calculating X\n###\n");

        //send a1 and b1 to child
        write(pTc[1], &a1, sizeof(a1));
        write(pTc[1], &b1, sizeof(b1));

        //display the values sent to child
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        
        //read value from child
        int A;
        read(cTp[0], &A, sizeof(A));

        //display the value received from child
        printf("Parent (PID %d): Received %d from child\n", getpid(), A);

        //calculate X 
        int X = A * pow(10,4);

        /* 
            CALCULATING Y
        */

        printf("\n###\n# Calculating Y\n###\n");

        //send a2 and b1 to child
        write(pTc[1], &a1, sizeof(a2));
        write(pTc[1], &b1, sizeof(b1));

        //display the values sent to child
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);

        
        //read value from child
        int B;
        read(cTp[0], &B, sizeof(B));

        //display the value received from child
        printf("Parent (PID %d): Received %d from child\n", getpid(), B);

        //send a1 and b2 to child
        write(pTc[1], &a1, sizeof(a1));
        write(pTc[1], &b1, sizeof(b2));

        //display the values sent to child
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        
        //read value from child
        int C;
        read(cTp[0], &C, sizeof(C));

        //display the value received from child
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), C);

        //calculate y
        int Y = (B+C)*pow(10,2);

        /* 
            CALCULATING Z
        */

        printf("###\n# Calculating Z\n###\n");

        //send a2 and b2 to child
        write(pTc[1], &a2, sizeof(a2));
        write(pTc[1], &b2, sizeof(b2));

        //display the values sent to child
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);

        
        //read value from child
        int D;
        read(cTp[0], &D, sizeof(D));

        //display the value received from child
        printf("Parent (PID %d): Received %d from child\n", getpid(), D);

        //calculate Z
        int Z = D * pow(10,0);

        int sum = X + Y + Z;
        //print sum
        printf("\n%d*%d == %d + %d + %d == %d\n", a, b, X, Y, Z, sum);
    } 

    //child process
    else if(pid==0){ 
        //read a1 and b1 from parent 
        read(pTc[0], &a1, sizeof(a1));
        read(pTc[0], &b1, sizeof(b1));

        //display the values received from the parent
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), a1);
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), b1);

        //calculate A
        int A = a1*b1;

        //send A to parent
        write(cTp[1], &A, sizeof(A));

        //display the value sent to the parent
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), A);

        //read a2 and b1 from parent 
        read(pTc[0], &a1, sizeof(a2));
        read(pTc[0], &b1, sizeof(b1));

        //display the values received from the parent
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), a2);
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), b1);

        //calculate B
        int B = a2*b1;

        //send B to parent
        write(cTp[1], &B, sizeof(B));

        //display the value sent to the parent
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), B);

        //read a1 and b2 from parent 
        read(pTc[0], &a1, sizeof(a1));
        read(pTc[0], &b1, sizeof(b2));

        //display the values received from the parent
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), a1);
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), b2);

        //calculate C
        int C = a1*b2;

        //send C to parent
        write(cTp[1], &C, sizeof(C));

        //display the value sent to the parent
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), C);

        //read a2 and b2 from parent 
        read(pTc[0], &a2, sizeof(a2));
        read(pTc[0], &b2, sizeof(b2));

        //display the values received from the parent
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), a2);
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), b2);

        //calculate D
        int D = a2*b2;

        //send D to parent
        write(cTp[1], &D, sizeof(D));

        //display the value sent to the parent
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), D);

        //child exits
        exit(0);
    }

    //exit
    return 0; 
}
