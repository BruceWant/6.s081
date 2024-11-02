# riscv64-linux-gnu-as -o hello.o hello.S
# riscv64-linux-gnu-ld -o hello hello.o


#riscv64-linux-gnu-as -march=rv64imac -o hello.o hello.S
#riscv64-linux-gnu-ld -o hello hello.o

.data
helloworld:      .asciz "hello world!\n"

.text
.global start

start:
        #addi  a0, x0, 1 # stdout
        li    a0, 1 # stdout
        la    a1, helloworld # address of string
        li    a2, 13 # length of string
        #addi  a7, x0, 16 # SYS_write
        li    a7, 16 # SYS_write
        ecall


        addi  a0, x0, 0 # exit value
        #addi    a7, x0, 2 # SYS_exit
        li    a7, 2 # SYS_exit
        ecall

