




sub $0, $0, $0					#ensure $0 contains zero  address: Ox400'000

#---------------------------
#Store array variables

addi $t0, $0,  Ox10000000
addi $t1, $0,  11
sw $t1, 0($t0)

addi $t0, $0,  Ox10000004       #0x 400'010
addi $t1, $0,  22
sw $t1, 0($t0)

addi $t0, $0,  Ox10000008
addi $t1, $0,  33            #0x 400'020
sw $t1, 0($t0)

addi $t0, $0,  Ox1000000c
addi $t1, $0,  44
sw $t1, 0($t0)                 #0x 400'030

addi $t0, $0,  Ox10000010
addi $t1, $0,  55
sw $t1, 0($t0)



addi $t0, $0,  Ox100000014		#store length variable, address 0x400'040
addi $t1, $0,  5
sw $t1, 0($t0)

#-----------------------
# Function to Sum array


addi $t0, $0, 0					#loop counter
addi $t2, $0, 0					#total             #0x 400'050
addi $t3, $0, Ox10000000		#starting address
lw $t5, 0($t1)					#store length in $t5
#sumLoop:
	beq $t0, $t5, 0x14    # branch to done
		lw $t4, 0($t3)				#load array value    #0x 400'060
		add $t2, $t2, $t4			#add to total
		addi $t3, $t3, 4			#increment address
		addi $t0, $t0, 1			#increment loop counter
		beq $0, $0, 0xffe8          #back to sumLoop                    # 0x 400'070

#done





