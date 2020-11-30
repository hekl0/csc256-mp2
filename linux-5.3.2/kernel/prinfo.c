// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/kernel/fork.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>

struct prinfo {
	/* current state of process */
	long state;

	/* process id (input) */
	pid_t pid;

	/* process id of parent */
	pid_t parent_pid;

	/* process id of youngest child */
	pid_t youngest_child_pid;

	/* pid of the oldest among younger siblings */
	pid_t younger_sibling_pid;

	/* pid of the youngest among older siblings */
	pid_t older_sibling_pid;

	/* process start time */
	unsigned long start_time;

	/* CPU time spent in user mode */
	unsigned long user_time;

	/* CPU time spent in system mode */
	unsigned long sys_time;

	/* total user time of children */
	unsigned long cutime;

	/* total system time of children */
	unsigned long cstime;

	/* user id of process owner */
	long uid;

	/* name of program executed */
	char comm[16];

	/* The set of pending signals */
	unsigned long signal;

    /* Number of open file descriptors */
	unsigned long num_open_fds;
};


SYSCALL_DEFINE1(prinfo, struct prinfo *, p) {
	printk ("CSC256: Hi %d!\n", 123);

	struct task_struct *p = current;
	
	return 0;
}
