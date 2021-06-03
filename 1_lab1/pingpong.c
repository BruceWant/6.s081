#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int ptc[2] = {0};
  int ctp[2] = {0};
  int pid = -1;
  //char ch = 'a';
  char buf[10] = {0};

  pipe(ptc);
  pipe(ctp);

  if (-1 == (pid = fork()))
  {
    printf("fork error\n");
    exit(1);
  }
  else if (0 == pid)
  {
    close(ptc[1]);
    close(ctp[0]);

    sleep(50);
    read(ptc[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(ctp[1], "pong", 4);

    close(ptc[0]);
    close(ctp[1]);
  }
  else
  {
    close(ptc[0]);
    close(ctp[1]);

    write(ptc[1], "ping", 4);
    close(ptc[1]);
    read(ctp[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);

    close(ctp[0]);
  }
  exit(0);
}
