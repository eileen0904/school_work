#我用了Selection Sort，以下是我用C寫的程式碼
#for(i = 0; i<元素數量-1; i++)
#   index = i
#   min = array[i]
#   for(j = i + 1; j < 元素數量; j++)
#       if(min > array[j])
#           min = array[j]
#           index = j
#   array[index] = array[i]
#   array[i] = min

    .data
array:	.space 200
input_msg:.asciiz "Please input an integer followed with a line: \n"
output_msg:.asciiz "The sorted sequence is: \n "
space: .asciiz " "

    .text
main:
    la $s0, array	            #s0 = array[0]
    la $s1, array               #s1 = array[0]
    la $a0, input_msg
    li $v0, 4
    syscall

	li $t7, 0                   #the count of element
    jal input

input:
    li $v0, 5			        #cin >> element
	syscall
    move $t0, $v0	            #t0 = v0

    beq $t0, $zero, init        #if(input == 0) 

    sw $t0, ($s1)	            #array[index] = t0
    addi $s1, $s1, 4            #next index of array
    
    addi $t7, $t7, 1            #count++

    jal input

init:
    li $t8, -1                  #iterator i for loop 1
    li $t2, 0
    add $t2, $t2, $t7
    addiu $t2, $t2, -1          #t2 = count - 1

    jal sort_loop_1

sort_loop_1:
    addi $t8, $t8, 1            #i++
    move $t1, $t8               #t1 is index = i
    move $a1, $t8               #iterator j for loop 2
    addi $a1, $a1, 1            #j = i + 1

    li $t9, 0
    sll $t9, $t8, 2             #t9 = i * 4
    add $t9, $t9, $s0           #address of array[i]
    lw $t5, 0($t9)              #t5 = array[i]
    move $s2, $t5               #s2 is min

    blt $t8, $t2, sort_loop_2   #if(i < count-1) go to loop 2

    jal print_msg

sort_loop_2:
    beq $a1, $t7, swap          #if(j == count) go to swap

    li $t4, 0
    sll $t4, $a1, 2             #t4 = j * 4
    add $t4, $t4, $s0           #address of array[j]
    lw $t0, 0($t4)              #t0 = array[j]

    bgt $s2, $t0, assign        #if(min > array[j])

    addi $a1, $a1, 1            #j++

    jal sort_loop_2

assign:
    
    move $s2, $t0               #min = array[j]
    move $t1, $a1               #index = j

    addi $a1, $a1, 1            #j++

    jal sort_loop_2             

swap:
    li $t4, 0
    li $t6, 0
    sll $t4, $t8, 2             #t4 = i * 4
    add $t4, $t4, $s0           #address of array[i]
    lw $t0, 0($t4)              #t0 = array[i]

    sll $t6, $t1, 2             #t6 = index * 4
    add $t6, $t6, $s0           #address of array[index]
    lw $t5, 0($t6)              #t5 = array[index]

    move $t9, $t5               #temp = array[index]
    sw $t0, 0($t6)              #array[index] = array[i]
    sw $t9, 0($t4)              #array[i] = temp
    
    jal sort_loop_1

print_msg:
    li $t0, 0
    li $t4, 0                   #k
    la $a0, output_msg
    li $v0, 4
    syscall

    jal print_data

print_data:
    beq $t0, $t7, Exit          #if(temp1 == count) end

    sll $t4, $t0, 2             #k = temp1 * 4
    add $t4, $t4, $s0           #address of array[k]
    lw $a0, 0($t4)              #a0 = array[k]
    
    li $v0, 1                   #print data
    syscall
    la $a0, space
    li $v0, 4
    syscall

    addi $t0, $t0, 1
    
    jal print_data

Exit:
    li $v0, 10