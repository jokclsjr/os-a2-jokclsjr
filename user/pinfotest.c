#include "kernel/types.h"
#include "kernel/pinfo.h"
#include "user/user.h"

int
main(void)
{
  struct pinfo info[64];
  volatile unsigned long x = 0;

  for (unsigned long i = 0; i < 50000000UL; i++) {
    x += i;
  }

  if (x == 0)
    printf("%lu\n", x);

  int n = getpinfo(info, 64);

  if (n < 0) {
    printf("getpinfo failed\n");
    exit(1);
  }

  printf("PID STATE LEVEL RUNTICKS NSCHED CTIME NAME\n");

  for (int i = 0; i < n; i++) {
    printf("%d %d %d %d %d %d %s\n", info[i].pid, info[i].state, info[i].level,
           info[i].runticks, info[i].nsched, info[i].ctime, info[i].name);
  }

  exit(0);
}