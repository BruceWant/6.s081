#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    //printf("<%s> ", fmtname(path));
    if (0 == strcmp(fmtname(path), name))
    {
      printf("%s\n", path);
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      if (strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0)
      {
        continue;
      }
      //printf("%s ", de.name);
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      //printf("%s ", p);
      find(buf, name);
      //printf("%s ", buf);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  //int i;

  //if(argc < 2){
  //  ls(".");
  //  exit(0);
  //}
  //for(i=1; i<argc; i++)
  if (argc != 3)
  {
    printf("usage: %s <path> <name>\n", argv[0]);
    exit(0);
  }
  find(argv[1], argv[2]);
  exit(0);
}
