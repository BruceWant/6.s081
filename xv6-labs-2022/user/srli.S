.data
.text
.global start

start:
  addi t1, x0, 1
  slli t2, t1, 31
  srli t3, t2, 31

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
