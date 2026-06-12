#include "types.h" // access to data types
#include "user.h" // to use printf(), read(); exit() also and my own getreadcount());

int main()
{
  char string[10];

  printf(1, "read() syscalls done until now: %d\n", getreadcount());
  read(0, string, 1);
  read(0, string, 1);
  printf(1, "Total counter after 2 read() calls%d\n", getreadcount());

  exit();
}
