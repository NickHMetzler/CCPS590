// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

// This function to check whether a variable is an integer was taken from
// https://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}
// Function end

int main(int argc, char *argv[])
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // Get the inputted character
    char *a = argv[1];

    // Check if input is an integer
    if (isNumber(a) != true){
      printf("Error, please enter an integer\n");
      exit(1);
    }
    int keyNum = atoi(a);
    
    // Grab key from the inputted integer
    key = keyNum;

    // Connect to the queue
    if ((msqid = msgget(key, 0644)) == -1) { 
        perror("msgget");
        exit(1);
    }
    
    printf("Spock: ready to receive messages, captain!\n");

    // Spock never quits...
    for(;;) 
    { 
        // ... Until queue is destroyed by Kirk
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Spock: \"%s\"\nPID of Spock: %d\n", buf.mtext, getpid());
    }

    return 0;
}

