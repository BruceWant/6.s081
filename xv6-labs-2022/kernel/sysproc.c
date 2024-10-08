#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


#ifdef LAB_PGTBL
int
sys_pgaccess(void)
{
  pte_t *pte;
  struct proc* p = myproc();
  uint64 addr;
  int len;
  int bitmask = 0;
  uint64 bitmask_addr;

  argaddr(0, &addr);
  argint(1, &len);
  argaddr(2, &bitmask_addr);

  //vmprint(p->pagetable);
  //printf("addr: %p\n", addr);
  for (int i = 0; i < len; i++) {
    pte = walk(p->pagetable, addr+(i*PGSIZE), 0);
    //printf("%d:pte: %p\n", i, *pte);
    //uint64 pa = PTE2PA(*pte);
    //printf("%d:pa: %p\n", i, pa);
    if (*pte & PTE_A) {
      bitmask |= (1 << i);
      //printf("i: %d, bitmask: %d\n", i, bitmask);
    }
    *pte = *pte & (~PTE_A);
  }
  //printf("bitmask: %d\n", bitmask);
  copyout(p->pagetable, bitmask_addr, (char *)&bitmask, sizeof(bitmask));
  // lab pgtbl: your code here.
  return 0;
}
#endif

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
