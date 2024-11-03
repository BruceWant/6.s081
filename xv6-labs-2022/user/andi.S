.data
.text
.global start

start:
  addi t1, x0, 3
  andi t3, t1, 0

  addi t1, x0, 2
  andi t3, t1, 1

  addi t1, x0, 3
  andi t3, t1, 2

  addi t1, x0, 3
  andi t3, t1, 1

  addi t1, x0, 0
  andi t3, t1, 0

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
