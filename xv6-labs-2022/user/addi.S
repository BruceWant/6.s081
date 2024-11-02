
.data

.text
.global start

start:
  addi t1, x0, 1

  # illegal operands: 2048
  #addi t2, t1, 2048
  addi t2, t1, 2047

  addi t4, t2, 0

  # illegal operands: -2049
  #addi t3, t2, -2049
  addi t3, t2, -2048

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
