#include <stdio.h>
#include <stdlib.h>

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
/*
 * Function: main()
 *
 * Description:
 *   Entry point for this program. 
 *   Expect 1 or 2 args:
 *      + 1 args: call prinfo for itself
 *      + 2 args: call prinfo for the process argv[1] 
 *
 * Inputs:
 *   argc - The number of argument with which this program was executed.
 *   argv - Array of pointers to strings containing the command-line arguments. 
 *
 * Return value:
 *   0 - This program terminated normally.
 */

int main (int argc, char ** argv) {
	/* Print a friendly message */
	printf ("Hello from User Space!\n");
	printf ("sys_time offset is %lx\n", __builtin_offsetof (struct prinfo, sys_time));

	struct prinfo *info = malloc(sizeof(struct prinfo));
    if (argc == 1) {
        info->pid = getpid();
        printf("pid %d\n\n", getpid());
    } else 
        info->pid = atoi(argv[1]);
	/* Call our new system call */
	int ret = syscall (181, info);

    printf("-- syscall return status %d\n", ret);
    printf("state\t\t\t\t%ld\n", info->state);
    printf("parent_pid\t\t\t%d\n", info->parent_pid);
    printf("youngest_child_pid\t\t%d\n", info->youngest_child_pid);
    printf("younger_sibling_pid\t\t%d\n", info->younger_sibling_pid);
    printf("older_sibling_pid\t\t%d\n", info->older_sibling_pid);
    printf("start_time\t\t\t%ld\n", info->start_time);
    printf("user_time\t\t\t%ld\n", info->user_time);
    printf("sys_time\t\t\t%ld\n", info->sys_time);
    printf("cutime\t\t\t\t%ld\n", info->cutime);
    printf("cstime\t\t\t\t%ld\n", info->cstime);
    printf("uid\t\t\t\t%ld\n", info->uid);
    printf("comm\t\t\t\t%s\n", info->comm);
    printf("signal\t\t\t\t%ld\n", info->signal);
    printf("num_open_fds\t\t\t%ld\n", info->num_open_fds);

	/* Exit the program */
	return 0;
}
