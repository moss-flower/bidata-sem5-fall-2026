#include <stdio.h>

int main (void) {
  char buf[128];
  int flag = 0;

  printf("addr of flag: %llx\n", &flag);
  gets(buf);
  printf (buf);

  if (flag)
    printf("You reached me!\n");

  return 0;
}
