# Experiements

Test1: 
+ the state is TASK_INTERRUPTIBLE (value 1) if I start test 1 in bg
+ the state is 260 if I start in fg and then stop it (ctrl + z)

Test2:
+ I only got state 0 which means that task is running 
+ I expected to get state 1 or something similar also (I didn't get it) because maybe the process is putted to sleep to give resource for other processes

Test3:
+ I got 1 signal pending
+ Because the kernel uses only a mask to keep track of pending signal. When there is a pending signal, the kernel will set the bit associate with the pending signal to 1. Therefore, we can't queue signals of the same type.

# Some problem I encountered:

Quit qemu vm:
+ Ctrl + A
+ x

Can't write to stat tmp:
+ manually create file

Unmount:
+ umount not unmount

VM doesn't have gcc:
- Compile code from outside and then send exe file to VM

Set errno:
- Return -Error Code

Check invalid memory
- Use access_ok(add, sz)

# Linux Source Code for CSC 256/456

This repository contains the Linux source code for CSC 256/456.

# Downloading additional files

Students will need the OpenWRT hard disk image.  The getfiles.sh script will
download and unpack these files from the course web page.  Simply execute the command:

o sh getfiles.sh

In case students want to get the files by hand, the information is below:

o The OpenWRT image that we use for our virtual machine is at http://www.cs.rochester.edu/courses/256/fall2015/QDGL/openwrt-15.05-x86-generic-combined-ext4.img

# Compiling the kernel

To compile the kernel, cd into the linux-5.3.2 directory.  Use the following
commands the first time you build the kernel:

o cd linux-5.3.2

o make mrproper

o cp ../csc256.config .config

o make bzImage

Subsequent kernel compiles can be done just by using:

o make bzImage

The first kernel compile will take some time.  Subsequent kernel compiles will
take less time as the kernel build system will only recompile files that have
changed (or that use header files that have changed).

If your system has multiple processors, you can use the -j option to GNU make
to compile files in parallel.  Just remember to be kind to your fellow students;
don't specify too large a number with the -j option.

# Running QEMU

The runqemu.sh script will launch QEMU with the needed command-line options.
With no arguments, it will boot the OpenWRT disk image with the default kernel
residing on the image.  Alternatively, students can provide the pathname to
their Linux kernel, and runqemu.sh will boot their kernel instead.  The kernel
is in the file linux-5.3.2/arch/x86_64/boot/bzImage.

# Importing files into the QEMU virtual machine

Files in the floppy directory will appear as a hard disk within the
virtual machine.  To mount the hard disk, use the command:

o mount -t msdos /dev/sdb1 /mnt

The contents of the directory floppy should appear in /mnt.

Be sure to use the following command to unmount the hard disk device before
shutting down the virtual machine:

o unmount /mnt
