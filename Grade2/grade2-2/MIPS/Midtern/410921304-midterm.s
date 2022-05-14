    .data
welcom_msg:.asciiz "This calculator only accept integer: \n"
example1_msg:.asciiz "Example formula: 100+2*10= (記得換行) \n"
example2_msg:.asciiz "Example formula: 4+5%2*3+2*4-3+5= (記得換行) \n"
notice1_msg:.asciiz "Notice that you don't need to input enter when you input the operator: \n"
notice2_msg:.asciiz "It will word wrap \n"
input_msg:.asciiz "Please input a formula followed with a line: \n"
output_msg:.asciiz "The result is: \n "
dotdotdot:.asciiz "..."
nextline: .asciiz "\n"

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

    la $a0, notice1_msg
    li $v0, 4
    syscall

    la $a0, notice2_msg
    li $v0, 4
    syscall

    la $a0, input_msg
    li $v0, 4
    syscall

    li $s1, 0               # int_1
    li $a1, 6               # op_1 = '+'
    
    jal input

input:
    beq $a1, 24, output     # if(op_1 == '=') output

    li $v0, 5               # cin >> int_2
    syscall
    move $s2, $v0           # s2 = int_2

    li $v0, 12              # cin >> op_2 (char)
    syscall
    move $t2, $v0           # t2 = op_2

    la $a0, nextline
    li $v0, 4
    syscall

    addiu $a2, $t2, -37     # a2 = t2 - '%' (ascii) 

    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')
    beq $a2, 6, plus        # if(op_2 == '+')
    beq $a2, 8, sub         # if(op_2 == '-')

mul:
    li $v0, 5               # cin >> int_3
    syscall
    move $s3, $v0           # s3 = int_3

    li $v0, 12              # cin >> op_3 (char)
    syscall
    move $a3, $v0           # a3 = op_3

    la $a0, nextline
    li $v0, 4
    syscall
	
    mul $s2, $s2, $s3       # int_2 = int_2 * int_3

    addiu $a3, $a3, -37     # a3 = a3 - '%' (ascii)
    move $a2, $a3           # op_2 = op_3

    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')

div:
    li $v0, 5               # cin >> int_3
    syscall
    move $s3, $v0           # s3 = int_3

    li $v0, 12              # cin >> op_3 (char)
    syscall
    move $a3, $v0           # a3 = op_3

    la $a0, nextline
    li $v0, 4
    syscall

    div $s2, $s3            # int_2 = int_2 % int_3
	mflo $s2                # quotient to s2
    mfhi $t0                # remainder to t0

	addiu $a3, $a3, -37     # a3 = a3 - '%' (ascii)
    move $a2, $a3           # op_2 = op_3

    beq $a2, $zero, div     # if(op_2 == '%')
    beq $a2, 5, mul         # if(op_2 == '*')
    beq $a1, 6, plus        # if(op_1 == '+')
    beq $a1, 8, sub         # if(op_1 == '-')

plus:
    add $s1, $s1, $s2       # int_1 = int_1 + int_2

    move $a1, $a2           # op_1 = op_2

    jal input

sub:
    sub $s1, $s1, $s2       # int_1 = int_1 - int_2

    move $a1, $a2           # op_1 = op_2

    jal input

output:
    la $a0, output_msg
    li $v0, 4
    syscall

    move $a0, $s1           # s1 is the result
    li $v0, 1               # print the result
    syscall

    la $a0, dotdotdot
    li $v0, 4
    syscall

    move $a0, $t0           
    li $v0, 1               # print the remainder
    syscall

    li $v0, 10
    syscall
