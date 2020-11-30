// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/kernel/fork.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

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


SYSCALL_DEFINE1(prinfo, struct prinfo *, info) {
	printk ("CSC256: Hi %d!\n", 123);
	printk ("sys_time offset is %lx\n", __builtin_offsetof (struct prinfo, sys_time));

	if (info == NULL) {
		// errno = EINVAL;
		return EINVAL;
	}

	struct task_struct *p;
	for_each_process(p) {
		if (info->pid == p->pid) {
			// Get state
			info->state = p->state;
			// Get parent
			if (p->real_parent != NULL)
				info->parent_pid = p->real_parent->pid;
			// Get youngest child
			if (!list_empty(&p->children)) {
				struct task_struct *child = list_first_entry(&p->children, struct task_struct, sibling);
				info->youngest_child_pid = child->pid;
			}
			// Get younger sibling
			if (list_entry(p->sibling.prev, struct task_struct, sibling)->pid < p->pid) {
				struct task_struct *sibling = list_entry(p->sibling.prev, struct task_struct, sibling);
				info->younger_sibling_pid = sibling->pid;
			}
			// Get older sibling
			if (list_entry(p->sibling.next, struct task_struct, sibling)->pid > p->pid) {
				struct task_struct *sibling = list_entry(p->sibling.next, struct task_struct, sibling);
				info->older_sibling_pid = sibling->pid;
			}
			// Get start time
			info->start_time = p->start_time;
			// Get user mode time
			info->user_time = p->utime;
			// Get system mode time
			info->sys_time = p->stime;
			// Get time spent by children
			info->cutime = 0;
			info->cstime = 0;
			if (!list_empty(&p->children)) {
				struct list_head *c;
				list_for_each(c, &p->children) {
					struct task_struct *s;
					s = list_entry(c, struct task_struct, sibling);
					info->cutime += s->utime;
					info->cstime += s->stime;
					printk("child %d\n", s->pid);
				}
			}
			return 0;
		}
	}
	
	// errno = EINVAL;
	return EINVAL;
}
