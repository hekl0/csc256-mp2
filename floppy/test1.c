/*
Write a program that prints out its process ID and then calls the sleep()
system call to put itself to sleep for 100 seconds. Use your test program
to find the state of the process. Report this state in your README file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/unistd.h>
#include <sys/syscall.h>

struct prinfo {
    long state; /* current state of process */
    pid_t pid; /* process id (input) */
    pid_t parent_pid; /* process id of parent */
    pid_t youngest_child_pid; /* process id of youngest child */
    pid_t younger_sibling_pid; /* pid of the oldest among younger siblings */
    pid_t older_sibling_pid; /* pid of the youngest among older siblings */
    unsigned long start_time; /* process start time */
    unsigned long user_time; /* CPU time spent in user mode */
    unsigned long sys_time; /* CPU time spent in system mode */
    unsigned long cutime; /* total user time of children */
    unsigned long cstime; /* total system time of children */
    long uid; /* user id of process owner */
    char comm[16]; /* name of program executed */
    unsigned long signal; /* The set of pending signals */
    unsigned long num_open_fds; /* Number of open file descriptors */
};

int main (int argc, char ** argv) {
	printf ("sys_time offset is %lx\n", __builtin_offsetof (struct prinfo, sys_time));
    
    printf("pid %d\n\n", getpid());
    sleep(100);

	return 0;
}
