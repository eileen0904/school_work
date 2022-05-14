    .data
welcom_msg:.asciiz "This calculator only accept integer: \n"
example1_msg:.asciiz "Example formula: 100+2*10=\n"
example2_msg:.asciiz "Example formula: 4+5%2*3+2*4-3+5=\n"
input_msg:.asciiz "Please input a formula in one line: \n"
output_msg:.asciiz "The result is: \n "
dotdotdot:.asciiz "..."
nextline: .asciiz "\n"
exp: .space 401
	.align 4
exp_1: .space 400

    .text
main:
    la $a0, welcom_msg
    li $v0, 4
    syscall
    
    la $a0, example1_msg
    li $v0, 4
    syscall

    la $a0, example2_msg
    li $v0, 4
    syscall
    
    la $a0, input_msg
    li $v0, 4
    syscall
    
    li $v0, 8               # cin >> exp (string)
    la $a0, exp             # a0 = address of input string
    li $a1, 401             # a1 =  maximum number of characters to read
    syscall
    move $s0, $a0           # s0 = address of exp

    la $s1, exp_1           # s1 = address of exp_1          

    li $s2, 0               # head
    li $s3, 0               # tail
    li $s4, 0               # index of exp_1
    li $a2, 10

    jal seperate

seperate:
    beq $t2, 24, cal

    #sll $t0, $s3, 2        # t0 = tail * 4 
    add $t0, $s3, $s0       # t0 = address of exp[tail]
    lb $t1, 0($t0)          # t1 = exp[tail]

    blt $t1, 48, op         # if(exp[tail] < 48) op
    bgt $t1, 57, op         # if(exp[tail] > 57) op

    addi $s3, $s3, 1        # tail = tail + 1

    jal seperate

op:
    addiu $t2, $t1, -37     # op = t1 - '%'
    li $t1, 0
    li $t3, 0

    jal num

num:
    add $t3, $t3, $t1       # num = num + temp_num
    add $t0, $s2, $s0       # t0 = address of exp[head]
    lb $t1, 0($t0)          # t1 = exp[head]
    addiu $t1, $t1, -48     # t1 = t1 - 48 (get number)

    addi $s2, $s2, 1        # head = head + 1
    sub $t4, $s3, $s2       # counter = tail - head

    bgtz $t4, loop_1        # if(counter > 0) loop_1

    jal store

loop_1:
    beqz $t4, num           # if(counter == 0) num

    mul $t1, $t1, $a2       # t1 = t1 * 10
    addiu $t4, $t4, -1      # counter = counter - 1

    jal loop_1

store:
    add $t3, $t3, $t1       # num = num + temp_num
    
    sll $t5, $s4, 2         # t5 = index * 4
    add $t5, $t5, $s1       # t5 = address of exp_1[index]
    sw $t3, 0($t5)          # exp_1[index] = num
    addi $s4, $s4, 1        # index = index + 1

    sll $t5, $s4, 2         # t5 = index * 4
    add $t5, $t5, $s1       # t5 = address of exp_1[index]
    sw $t2, 0($t5)          # exp_1[index] = op
    addi $s4, $s4, 1        # index = index + 1

    addi $s3, $s3, 1        # tail = tail + 1
    addi $s2, $s2, 1        # head = head + 1

    jal seperate

cal:
    li $t1, 0               # int_1
    li $a1, 6               # op_1 = '+'
    li $t2, 0               # int_2
    li $a2, 0               # op_2
    li $t3, 0               # int_3
    li $a3, 0               # op_3
    li $s2, 0               # cur

    jal cal_1

cal_1:
    beq $a1, 24, output     # if(op_1 == '=') output

    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $t2, 0($t0)          # int_2 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $a2, 0($t0)          # op_2 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')
    beq $a2, 6, plus        # if(op_2 == '+')
    beq $a2, 8, sub         # if(op_2 == '-')

mul:
    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $t3, 0($t0)          # int_3 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $a3, 0($t0)          # op_3 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    mul $t2, $t2, $t3       # int_2 = int_2 * int_3

    move $a2, $a3           # op_2 = op_3

    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')

div:
    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $t3, 0($t0)          # int_3 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    sll $t0, $s2, 2         # t0 = cur * 4
    add $t0, $t0, $s1       # t0 = address of exp_1[cur]
    lw $a3, 0($t0)          # op_3 = exp_1[cur]
    addi $s2, $s2, 1        # cur = cur + 1

    div $t2, $t3            # int_2 = int_2 % int_3
    mflo $t2                # quotient to t2
    mfhi $t4                # remainder to t4

    move $a2, $a3           # op_2 = op_3

    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')

plus:
    add $t1, $t1, $t2       # int_1 = int_1 + int_2

    move $a1, $a2           # op_1 = op_2

    jal cal_1

sub:
    sub $t1, $t1, $t2       # int_1 = int_1 - int_2

    move $a1, $a2           # op_1 = op_2

    jal cal_1

output:
    la $a0, output_msg
    li $v0, 4
    syscall

    move $a0, $t1           # t1 is the result
    li $v0, 1               # print the result
    syscall

    la $a0, dotdotdot
    li $v0, 4
    syscall

    move $a0, $t4           
    li $v0, 1               # print the remainder
    syscall

    li $v0, 10
    syscall