// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html

// Please take a look at the included PDF document for more comprehensive answers with screenshots

// Question 1
// Spock ends since it the message queue identifier (msqid) is removed, msgrcv() then returns -1 which activates the line of code that exits.
// Spock exits this way since there is no queue to connect to, thus returning -1.

// Question 3
// Since spock doesn’t contain a condition to end when there is an input passed that is NULL, nothing will happen when ^D is passed. Meanwhile in kirk.c, the loop is based on that the value passed is not NULL. Even if you pass nothing in, it pases in an empty string (“”) which is not NULL.

// Question 6
// The order of which the Spocks receive the message seems to be in increasing order of PID. Which makes sense since most systems dedicate the most important PID’s as the lowest number identifiers.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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

    // Create a key from the inputted integer
    key = keyNum;

    // Create message queue using key, set appropriate flags.
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    printf("Enter lines of text, ^D to quit:\n");
    buf.mtype = 1; // We don't really care in this case

    // Loop to send messages to queue until CTRL-D is typed
    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) 
	{
        int len = strlen(buf.mtext);

        // Ditch newline at end, if it exists
        if (buf.mtext[len-1] == '\n') 
			buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) // len+1 for '\0'
            perror("msgsnd");
    }

    // Remove message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}

