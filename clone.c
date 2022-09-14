/*
In this program we use the clone() function to spawn a 
child process in two different ways: 

A child spawned as a HEAVYWEIGHT process gets a copy of
parents memory, file descriptors, etc, but any changes in 
child would be only for the child.

A child spawned as a LIGHTWEIGHT process (thread) shares
memory and files with its parent by using flags CLONE_VM 
and CLONE_FILES.
  
The difference is only in a single line, seen below. 
Comment out the appropriate line depending on which type
of child you wish to spawn  
*/

#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

// Globals in scope for both main() and do_something()
int var = 0;
FILE *fd;

int do_something() 
{
    printf("\nChild in do_something():\n");
    printf("  My PID is: %d\n", getpid()); 
    printf("  My parent's PID is %d\n\n", getppid());
    var = 42;   // Change global variable
    fclose(fd); // Close file
    exit(0);    // Exit (terminate child) 
}

int main(int argc, char *argv[]) 
{
    char *stack, *stackTop;         // Pointers for child stack
    const int STACK_SIZE = 65536;   // Note stack grows down
    stack = malloc(STACK_SIZE);     // Allocate stack for child
    if (stack == NULL) {
        perror("malloc"); 
        exit(1);
    }
    stackTop = stack + STACK_SIZE;  // Note stack grows down

    var = 9;
    fd = fopen("test.txt", "r");

    // Ensure file has been opened successfully
    if (fd == NULL) {
        fprintf(stderr, "Missing test.txt file in this directory!\n");
        exit(2);
    }

    printf("VAR in parent before clone: %d\n", var);

    // Calling clone() this way spawns a HEAVYWEIGHT process 
    int cret = clone(do_something, stackTop, 0, NULL);

    // Calling clone() this way spawns a LIGHTWEIGHT process
    //int cret = clone(do_something, stackTop, CLONE_VM|CLONE_FILES, NULL);

    if (cret == -1)	{
        perror("clone() failed"); 
        exit(0); 
    }
	
    // Parent keeps going here, child continues execution in do_something()
    printf("Parent PID after clone() %d\n", getpid());
    sleep(1);

    printf("VAR in parent after clone/sleep: %d\n", var);
	
    // Attempt to read character from file test.txt
    char tempch;
    if (fscanf(fd, "%c", &tempch) < 1) {
        perror("File Read Error");
        exit(1);
    }
	
    printf("Read from the file: %c\n", tempch);
    return 0;
}

