.data
.text
.global start
start:
  addi t1, x0, 1
  lui t1, 1048575

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
