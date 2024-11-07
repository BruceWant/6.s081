.data
.text
.global start
start:
  auipc t1, 0
  auipc t2, 0
  auipc t3, 0
  addi t1, x0, 0

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
