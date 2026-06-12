#include "types.h" // access to data types
#include "user.h" // to use printf(), read(); exit() also and my own getreadcount());
int
main(void)
{
  char string[10];
  int count = 0; //printf affect the write count
  printf(1, "READ COUNT TEST\n");
  printf(1, "Initial count of read(): %d\n", getreadcount(0));
  read(0, string, 1);
  read(0, string, 1);
  printf(1, "after 2 read(): %d\n", getreadcount(0));
  printf(1, "Reset read count: %d\n", getreadcount(1));
  printf(1, "After reset-command: %d\n", getreadcount(0));
  printf(1, "SYSCALL COUNT TEST for READ(5) + WRITE(16))\n");
  printf(1, "Read syscalls: %d\n", getsyscallcount(5, 0));
  count = getsyscallcount(16,0);
  printf(1, "Write syscalls: %d\n", count);
  write(1, "hello", 6);
  write(1, "world\n", 6);
  count = getsyscallcount(16,0);
  printf(1, "Write syscalls after 2 writes: %d\n", count);
  printf(1, "Reset read syscalls: %d\n", getsyscallcount(5, 1));
  printf(1, "Reset write syscalls : %d\n", getsyscallcount(16, 1));
  printf(1, "After read reset-command: %d\n", getsyscallcount(5, 0));
  printf(1, "After write reset-command: %d\n", getsyscallcount(16, 0));
  exit();
}
