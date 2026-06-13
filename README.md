# CT30A3370-Project-4-Kernel-Hacking
## Introduction
```bash
   * This project create two new system calls that track and return the number of system calls made: **getreadcount(int reset)** and **getsyscallcount(int sys_call_number, int reset)**
   * **getreadcount(int reset)** only track read() system call and getsyscallcount track specified system call identified by sys_call_number parameter. Both system call takes in int reset parameter to check if user want to reset the counter.
 ```
## Installation instruction
```bash
Requirement
   * Best run this in Linux terminal (all commands here only works on Linux subsystems)
   * vscode will not be able to build qemu emulator since it use snap while qemu ...
 ```

```bash
## Preinstallation:
git clone https://github.com/xuanminhcpvn/CT30A3370-Project-4-Kernel-Hacking
sudo apt install qemu-system-x86  //You might need to install qemu-emulator to test system call using a program that test features of new system calls

## To run program (or in fact test created system calls):
git clone https://github.com/xuanminhcpvn/CT30A3370-Project-1-Warmup-to-C-and-Unix-programming
cd xv6-public
make clean #(just to reset the build process and make sure that latest version is being build, can skip this)
make  
make qemu
=> You will see a terminal like this
=> type following command to run the test program if you want to quickly check that counters works:
read_count_test (this will run a custom user program)
```
## Details about the workflow and what I modified
Since we have small code addition in different files. I will document all changes/additions made to enable new system call creation

1.	In usys.S added:
SYSCALL(getreadcount)
2.	In user.h (where those syscall declaration or definition (in C term) are located)), Added new definition
int getreadcount(void)
3.	Next is to go to syscall.h since usys.S include that header file and we need to specify system call number for returning system call number back to syscall() in syscall.c

#define SYS_getreadcount 22


4.	After that we can also add our new routine to the syscall table in syscall.c

extern int sys_getreadcount(void);
[SYS_getreadcount] sys_getreadcount,


 
5.	After that we implement our sys_getreadcount procedure implementation in sysproc.c
As well as modifying sys_read() function to count read() calls in sysfile.c

In sysfile.c added:

uint readcount = 0;

readcount++;//before returning

in sysproc.c

extern int readcount;

 int sys_getreadcount(void) 
{ 
return readcount; 
}
6.	

And so on but repeating step 1-6 for additional features, for example: 
in user.h updated sys call interface
int getreadcount(int reset)
int getsyscallcount(int sys_call_num, int reset)	
in usys.S added new SYSCALL name
SYSCALL(getsyscallcount)
In sysproc.c reset logic is implemented + syscall counter procedure
Extern int syscall_count[]
etc...
There are some minor modifications related to the xv6 set-up suggestion by the course book such as set CPU:=1 and something else related to the qemu emulator not creating a new window in Makefile
Also an important one is to add my own program to Makefile User program build instruction
U_PROGS:= read_count_test\


