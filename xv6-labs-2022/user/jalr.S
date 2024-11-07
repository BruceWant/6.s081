.data
.text
.global start
start:
  addi x1, x0, 4
loop:
  addi x5, x0, 1
  addi t1, t1, 0
  #jalr t1, 0(x1)
  jalr t1, x1, 0

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
