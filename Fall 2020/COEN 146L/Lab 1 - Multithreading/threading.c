// Name: Ruchir Mehta
// Date: 9/28/2020
// Title: Lab1 - Threading Program
// Description: Rewrite the forking program with the threading program

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h> 

void *start_routine(void *arg)
{
    int i;
    for (i = 0; i < 100; i++)
    {
        printf("\t \t \t Parent Process %d \n", i);
        usleep(*(int*) arg);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n = atoi(argv[1]);

    pthread_t tid;
    pthread_create(tid, NULL, start_routine, &n); // used instead of fork()

    // Child Process
    for (i = 0; i < 100; i++)
    {
        printf("Child Process %d\n", i);
        usleep(n);
    }
    pthread_join(tid, NULL);
    return 0;
}
