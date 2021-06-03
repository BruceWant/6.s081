#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

char *get_line(char *buf, int len)
{
  //printf("%s:%d\n", __FUNCTION__, __LINE__);
  int i = 0;
  do
  {
    if (0 >= read(0, &buf[i], sizeof(char)))
    {
      //printf("%c ", buf[i]);
      return 0;
    }
    //printf("%s\n", buf);
    i++;
  }while('\n' != buf[i-1] && i < len-1);
  buf[i-1] = '\0';
  //printf("buf: %s\n", buf);

  return buf;
}

void mk_argv(char **exeargv, int argc, char **argv, char *buf)
{
  int i = 0;
  for (;i < argc; i++)
  {
    exeargv[i] = argv[i];
    //printf("exeargv: %s ", exeargv[i]);
  }
  exeargv[i++] = buf;
  //printf("exeargv: %s ", exeargv[i-1]);
  exeargv[i++] = 0;
}

void xargs(int argc, char *argv[])
{
  char buf[512] = {0};
  char *exeargv[MAXARG] = {0};
  int pid = 0;

  //printf("%s:%d\n", __FUNCTION__, __LINE__);
  while (get_line(buf, sizeof(buf)))
  {
    mk_argv(exeargv, argc, argv, buf);

    pid = fork();
    if (-1 == pid)
    {
      exit(0);
    }
    else if (0 == pid)
    {
      //printf("%s %s %s\n", exeargv[0], exeargv[1], exeargv[2]);
      exec(argv[0], exeargv);
    }
    else
    {
      wait(0);
    }
  }
}

int main(int argc, char *argv[])
{
  if (3 > argc)
  {
    exit(0);
  }
  //printf("%s %s\n", argv[0], argv[1]);
  xargs(argc-1, argv+1);

  exit(0);
}
