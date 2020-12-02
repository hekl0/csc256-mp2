// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/kernel/fork.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/fdtable.h>

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

/*
 * This function will get information related to info->pid
 * and store it in info
 */
SYSCALL_DEFINE1(prinfo, struct prinfo *, info) {
	// printk ("CSC256: Hi %d!\n", 123);
	// printk ("sys_time offset is %lx\n", __builtin_offsetof (struct prinfo, sys_time));

	// Check info NULL
	if (info == NULL) 
		return -EINVAL;
	// Check invalid memory access
	if (!access_ok(info, sizeof(struct prinfo)))
		return -EFAULT;

	struct task_struct *p;
	for_each_process(p) {
		if (info->pid == p->pid) {
			int i;
			// Get state
			info->state = p->state;
			// Get parent
			if (p->real_parent != NULL)
				info->parent_pid = p->real_parent->pid;
			else
				info->parent_pid = -1;
			// Get youngest child
			if (!list_empty(&p->children)) {
				struct task_struct *child = list_first_entry(&p->children, struct task_struct, sibling);
				info->youngest_child_pid = child->pid;
			} else info->youngest_child_pid = -1;
			// Get younger sibling
			if (list_entry(p->sibling.next, struct task_struct, sibling)->pid > p->pid) {
				struct task_struct *sibling = list_entry(p->sibling.next, struct task_struct, sibling);
				info->younger_sibling_pid = sibling->pid;
			} else info->younger_sibling_pid = -1; 
			// Get older sibling
			if (list_entry(p->sibling.prev, struct task_struct, sibling)->pid < p->pid) {
				struct task_struct *sibling = list_entry(p->sibling.prev, struct task_struct, sibling);
				info->older_sibling_pid = sibling->pid;
			} else info->older_sibling_pid = -1;
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
					// printk("child %d\n", s->pid);
				}
			}
			// Get uid
			if (p->cred != NULL)
				info->uid = p->cred->uid.val;
			else
				info->uid = -1;
			// Get comm
			for (i = 0; i < 16; i++)
				info->comm[i] = p->comm[i];
			// Get number of pending signals
			info->signal = 0;
			if (!list_empty(&p->pending.list)) {
				struct list_head *s;
				list_for_each(s, &p->pending.list) {
					info->signal++;
				}
			}
			// Get number of open fds
			info->num_open_fds = 0;
			for (i = 0; i < NR_OPEN_DEFAULT; i++)
				if (p->files->fd_array[i] != NULL)
					info->num_open_fds++;
			return 0;
		}
	}
	
	return -EINVAL;
}
