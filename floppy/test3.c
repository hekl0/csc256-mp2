/*
Write a program that prints out its process ID, uses sigblock() to block
SIGUSR2, sends SIGUSR2 to itself two times, and then calls prinfo()
to look up its pending signal set. Use your test program to print out the
value of the list of pending signals. Report this value in the README
and explain why signals cannot be queued.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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
    // block SIGUSR2
    sigblock(1 << (SIGUSR2-1));
    // Try to send SIGUSR2
    raise(SIGUSR2);
    raise(SIGUSR2);

	printf ("sys_time offset is %lx\n", __builtin_offsetof (struct prinfo, sys_time));
	printf("pid %d\n\n", getpid());

	struct prinfo *info = malloc(sizeof(struct prinfo));
	info->pid = getpid();
    int ret = syscall (181, info);

    printf("-- syscall return status %d\n", ret);
    // printf("state\t\t\t\t%ld\n", info->state);
    // printf("parent_pid\t\t\t%d\n", info->parent_pid);
    // printf("youngest_child_pid\t\t%d\n", info->youngest_child_pid);
    // printf("younger_sibling_pid\t\t%d\n", info->younger_sibling_pid);
    // printf("older_sibling_pid\t\t%d\n", info->older_sibling_pid);
    // printf("start_time\t\t\t%ld\n", info->start_time);
    // printf("user_time\t\t\t%ld\n", info->user_time);
    // printf("sys_time\t\t\t%ld\n", info->sys_time);
    // printf("cutime\t\t\t\t%ld\n", info->cutime);
    // printf("cstime\t\t\t\t%ld\n", info->cstime);
    // printf("uid\t\t\t\t%ld\n", info->uid);
    // printf("comm\t\t\t\t%s\n", info->comm);
    printf("signal\t\t\t\t%ld\n", info->signal);
    // printf("num_open_fds\t\t\t%ld\n", info->num_open_fds);

	return 0;
}
