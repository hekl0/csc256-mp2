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
