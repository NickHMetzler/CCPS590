#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) 
{
   int pid, fpid, ppid;
   
   fpid = fork ();      // Spawn child process. 
   
   // Both parent and child continue executing from this point.
   // However, they both have their own fpid variable whose 
   // value will be different for parent and child.
   
   pid  = getpid();     // Get PID
   ppid = getppid();    // Get PID of parent
   
   // This will print twice!
   printf ("fpid is is %d\n", fpid);
   
   sleep(5);
   
   if (fpid > 0) // For parent, fpid == PID of child
   {
       printf("\nIn parent process: ");
       printf("FPID = %d, PID = %d, PPID = %d\n", fpid, pid, ppid);
   }
   else if (fpid == 0) // For child, fpid == 0
   {
       sleep(1);
       printf("\nIn child process: ");
       printf("FPID = %d, PID = %d, PPID = %d\n", fpid, pid, ppid);
   }
   else 
   {
	   printf ("fork failed\n");
   }
   
   return (0);
}
