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
	info->pid = getpid();
	printf("pid %d\n\n", getpid());
	info->pid = 321;
	/* Call our new system call */
	int ret = syscall (181, info);

	printf("return %d\n", ret);
	printf("parent_pid %d\n", info->parent_pid);
	printf("youngest_child_pid %d\n", info->youngest_child_pid);
	printf("younger_sibling_pid %d\n", info->younger_sibling_pid);
	printf("older_sibling_pid %d\n", info->older_sibling_pid);
	printf("start_time %ld\n", info->start_time);
	printf("user_time %ld\n", info->user_time);
	printf("sys_time %ld\n", info->sys_time);
	printf("cutime %ld\n", info->cutime);
	printf("cstime %ld\n", info->cstime);
	printf("uid %ld\n", info->uid);
	printf("comm %s\n", info->comm);
	printf("signal %ld\n", info->signal);
	printf("num_open_fds %ld\n", info->num_open_fds);

	/* Exit the program */
	return 0;
}
