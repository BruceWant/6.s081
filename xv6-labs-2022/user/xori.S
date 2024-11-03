.data
.text
.global start

start:
  addi t1, x0, 3
  xori t2, t1, 2
  xori t2, t1, 1
  xori t2, t1, 0

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
