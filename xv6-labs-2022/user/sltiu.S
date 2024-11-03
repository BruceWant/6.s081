.data

.text

.global start

start:
  addi t1, x0, 2047
  addi t2, t1, 1
  addi t3, x0, -1
  sltiu t4, t2, 2047
  sltiu t5, t3, 2045
  sltiu t6, t1, -1
  sltiu t1, t3, -1

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
