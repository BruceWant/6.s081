#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid = 0;
  int ptc[2] = {0};
  int ctp[2] = {0};
  int arr[35] = {0};

  //printf("init\n");
  for (int i = 2; i <= 35; i++)
  {
    arr[i-2] = i;
    //printf("%d ", arr[i-2]);
  }
  //printf("init end\n");
  //for (int i = 0; i < 35; i++)
  //{
  //  printf("arr[%d]: %d", i, arr[i]);
  //}
  pipe(ptc);
  pipe(ctp);


  while (-1 != (pid = fork()))
  {
    if (0 == pid)
    {
      close(ptc[1]);
      int i = 0;
      while (read(ptc[0], &arr[i], sizeof(int)))
      {
        i++;
        //printf("child: arr[%d]: %d\n", i, arr[i]);
      }
      close(ptc[0]);
      printf("prime %d\n", arr[0]);

      close(ctp[0]);
      int j = 0;
      for (j = 0; j < i; j++)
      {
        if (0 != arr[j] % arr[0])
        {
          //printf("arr: %d\n", arr[j]);
          write(ctp[1], &arr[j], sizeof(int));
        }
      }
      close(ctp[1]);
      break;
      //exit(0);
    }
    else
    {
      //printf("arr: %d\n", arr[0]);
      close(ptc[0]);
      for (int i = 0; 0 != arr[i]; i++)
      {
        write(ptc[1], &arr[i], sizeof(int));
      }
      close(ptc[1]);

      close(ctp[1]);
      int i = 0;
      for(i = 0; read(ctp[0], &arr[i], sizeof(int)); i++)
      {
      }
      arr[i] = 0;
      close(ctp[0]);

      if (0 == i)
      {
        break;
      }
      pipe(ptc);
      pipe(ctp);
    }
  }
  exit(0);
}
