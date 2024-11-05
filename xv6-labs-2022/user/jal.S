.data
.text
.global start

start:
  addi t1, x0, 0
loop: 
  addi t1, t1, 1
  jal x1, loop

  addi a0, x0, 0
  addi a7, x0, 2
  ecall
