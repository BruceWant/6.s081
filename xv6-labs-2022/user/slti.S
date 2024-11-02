.data
.text
.global start
start:
  addi t1, x0, 3
  slti t2, t1, 4 # t2 == 1
  slti t3, t1, 2 # t3 == 0

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
