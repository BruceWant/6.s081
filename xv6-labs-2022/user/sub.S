.data
.text
.global start
start:
  addi t1, x0, 3
  addi t2, x0, 2
  sub t3, t1, t2

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
