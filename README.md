### Declaration of AI (AI was used to turn my notes during development phase) to .md format. Tool used: ChatGPT
# CT30A3370-Project-4-Kernel-Hacking
## Introduction

This project implements two new system calls in the xv6 operating system that track and return the number of system calls:
* **getreadcount(int reset)**
* **getsyscallcount(int syscall_number, int reset)**

The **getreadcount()** system call tracks only `read()` system calls. The **getsyscallcount()** system call tracks any system call specified by the `syscall_number` parameter.

Both system calls support a reset flag. When `reset = 1`, the current counter value is returned and the corresponding counter is reset to zero. When `reset = 0`, the current value is returned without modifying the counter.

## Point proposal 
-Everything submitted compiles and works at least on some level. (Required, 2 points)


-The documentation is appropriate, correct and the repository is available (Required, 0 points)

-The documentation is detailed, and the provided source code is reasonably well commented. (1 point)


-You can reset the counter with an argument (1 point)

-You can select between the number of different system call which to follow (1 point)

**TOTAL: = 5**
## Installation Instructions

### Requirements

* Ubuntu 22.04 or similar Linux environment.
* Must use a Linux terminal instead of VS Code Snap Terminal because Snap may cause QEMU library conflicts.
* Required packages (to be fair only qemu-system-x86 is the critical one to enable qemu-emulator):

```bash
sudo apt install build-essential
sudo apt install qemu-system-x86
sudo apt install gcc-multilib
sudo apt install libc6-dev-i386
```
```bash
git clone https://github.com/xuanminhcpvn/CT30A3370-Project-4-Kernel-Hacking.git
cd CT30A3370-Project-4-Kernel-Hacking/xv6-public
make clean
make
make qemu
```
### Run Test Program when qemu terminal is available (otherwise check if qemu-package is installed or you are not using vscode terminal ):

```bash
read_count_test
```
This program test:
* getreadcount()
* getreadcount() reset functionality
* getsyscallcount() for read()
* getsyscallcount() for write()
* reset functionality for selected system call counters (write which is not really easy to track since there is a lot of write() call by other kernel routine

---

## Details About The Workflow And Modifications (Example of getreadcount() system call creation , getsyscallcount() and reset feature in similar way)
## Mostly following the course video material

### 1. Added user-level system call interface
File modified:

```text
user.h
```
```c
int getreadcount(int reset);
int getsyscallcount(int syscall_number, int reset);
```

### 2. Added user stub

File modified:
```text
usys.S
```

Added:

```c
SYSCALL(getreadcount)
SYSCALL(getsyscallcount)
```

### 3. new sys call number

File modified:

```text
syscall.h
```
```c
#define SYS_getreadcount 22

```
### 4. Registered system call in syscall.c
File modified:
```text
syscall.c
```
Added:
```c
extern int sys_getreadcount(void);
extern int sys_getsyscallcount(void);
```
and registered them in the syscall table:
```c
[SYS_getreadcount] sys_getreadcount,
[SYS_getsyscallcount] sys_getsyscallcount,
```
### 5. Global counter variable
File modified:

```text
sysfile.c
```
Added:
```c
int readcount = 0;
```
The counter is incremented whenever `sys_read()` successfully executes.
### 6. Implemented getreadcount()
File modified:
```text
sysproc.c
```
Added:
```c
extern int readcount;
```
and implemented:
```c
int
sys_getreadcount(void)
{
    ...
}
```
This system call returns the current read counter and optionally resets it depending on the reset flag.
### Additional Modifications
Created a custom user program:

```text
read_count_test.c
```
* Added the test program to `UPROGS` in Makefile
```make
UPROGS += _read_count_test
```

* Some Makefile instruction suggested by the background material such as set CPU:=1 and something related to qemu not opening new window when created + shorter make qemu command


