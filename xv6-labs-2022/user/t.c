#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  char buf[] = "hello world!\n";
  if (write(1, buf, 13) != 13) {
    fprintf(2, "cat: write error\n");
    exit(1);
  }
  exit(0);
}
