	.data
array:	.space 161

    .text
main:
    li $v0, 5			
	syscall			    #cin >> n
	move $t0, $v0	    #t0 = v0
    la $s0, array	    #s0 = array[0]
	sw $t0, ($s0)	    #array[0] = t0

    li $t1, 1
	li $t2, 2
    beq $t0, $t1, One   #if t0 == 1 One()
    beq $t0, $t2, Two   #if t0 == 2 Two()

    li $t3, 0			
	li $t4, 1			
	li $t5, 0

    #if the input is larger than 2
    addi $s0, $s0, 4    #s0 = array[1]
	sw $t3, ($s0)       #array[1] = t3 = 0
	addi $s0, $s0, 4    #s0 = array[2]
	sw $t1, ($s0)       #array[2] = t1 = 1
	addi $t0, $t0, -3   #t0 = t0 - 3 (location)
	move $a0, $t0       #a0 = to
	jal fibo	        #fibo(a0)

One:
    addi $s0, $s0, 4
	sw $t3, ($s0)
	jal exit

Two:
    addi $s0, $s0, 4
	sw $t3, ($s0)
	addi $s0, $s0, 4
	sw $t1, ($s0)
	jal exit

fibo:
	add $t5, $t4, $t3	#f(n) = f(n-1) + f(n-2)
	addi $s0, $s0, 4    #s0 = array[3]
	sw $t5, ($s0)       #array[3] = t5
	move $t3, $t4		#prev = curr
	move $t4, $t5		#curr = next
	slt $t7, $t6, $t0   #if(t6 < t0) t7 = 1 else t7 = 0
	beq $t7, $0, exit   #if t7 == 0 (t6 == t0) exit
	addi $t6, $t6, 1    #count

	jal fibo

exit:
	li $v0, 10
	syscall