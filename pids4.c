#define _GNU_SOURCE  //for Ubuntu
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) 
{
   int pid, fpid, ppid, status;
   
   fpid = fork ();
   
   printf ("fpid is is %d\n", fpid);
     
   if (fpid > 0) 
   {
       pid  = getpid();
       ppid = getppid();
       printf("\nIn parent process: ");
       printf("FPID = %d, PID = %d, PPID = %d\n", fpid, pid, ppid);
       
       if (wait(&status) >= 0)
       {
          printf("\nChild has finished and Parent is now exiting...\n");
       }
   }
   else if (fpid == 0) 
   {
       pid  = getpid();
       ppid = getppid();
       printf("\nIn child process: ");
       printf("FPID = %d, PID = %d, PPID = %d\n", fpid, pid, ppid);
       exit(0);
   }
   else 
   {
       printf ("fork failed\n");
   }
   
   return (0);
}
