#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int sec = 0;

  if(argc <= 1){
    printf("usage: %s <numbers>\n", argv[0]);
    exit(0);
  }

  sec = atoi(argv[1]);
  sleep(sec);

  exit(0);
}
