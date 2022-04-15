	.data
space:		.asciiz " "
one:        .asciiz "1"

    .text
main:
    li $v0, 5			
	syscall             #cin >> n;
	move $t0, $v0		#t0 = v0;

    li $t1, 1
	li $t2, 2
    beq $t0, $0, exit   #if t0 == 0 Zero()
    beq $t0, $t1, One   #if t0 == 1 One()
    beq $t0, $t2, Two   #if t0 == 2 Two()

    li $t1, 40
	beq $t0, $t1, exit

    li $t3, 0
	li $t4, 1			
	li $t5, 0

    #if the input is larger than 2
	move $v0, $0
	li $v0, 1           #print v0(0)
	syscall
	la $a0, space
	li $v0, 4           #print space
	syscall
    la $a0, one  
	li $v0, 4           #print 1
	syscall

    addi $t0, $t0, -3
	move $a0, $t0

    jal fibo            #fibo(a0)

One:
    move $v0, $0
	li $v0, 1           #print v0(0)
	syscall
	jal exit

Two:
    move $v0, $0
	li $v0, 1           #print v0(0)
	syscall
	la $a0, space
	li $v0, 4           #print space
	syscall
	la $a0, one  
	li $v0, 4           #print 1
	syscall
	jal exit

fibo:
    add $t5, $t4, $t3	#f(n) = f(n-1) + f(n-2)
    la $a0, space
    li $v0, 4           #print space
    syscall
    move $a0, $t5
    li $v0, 1           #print f(n)
    syscall
    move $t3, $t4		#prev = curr
	move $t4, $t5		#curr = next
    slt $t7, $t6, $t0   #if(t6 < t0) t7 = 1 else t7 = 0
	beq $t7, $0, exit   #if t7 == 0 (t6 == t0) exit
    addi $t6, $t6, 1    #count

    jal fibo

exit:
	li $v0, 10
	syscall
