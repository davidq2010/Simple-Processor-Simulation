




sub $0, $0, $0					#ensure $0 contains zero  address: 0x400'000

#---------------------------
#Store array variables

addi $t0, $ra,  0x0
addi $t1, $0,  11
sw $t1, 0($t0)

addi $t0, $ra,  0x4       #0x 400'010
addi $t1, $0,  22
sw $t1, 0($t0)

addi $t0, $ra,  0x8
addi $t1, $0,  33            #0x 400'020
sw $t1, 0($t0)

addi $t0, $ra,  0xc
addi $t1, $0,  44
sw $t1, 0($t0)                 #0x 400'030

addi $t0, $ra,  0x10
addi $t1, $0,  55
sw $t1, 0($t0)



addi $t0, $ra,  0x14		#store length variable, address 0x400'040
addi $t1, $0,  5
sw $t1, 0($t0)

#-----------------------
# Function to Sum array


addi $t0, $0, 0					#loop counter
addi $t2, $0, 0					#total             #0x 400'050
addi $t3, $ra, 0x0		#starting address
addi $t5, $t1, 0					#store length in $t5
#sumLoop:
	beq $t0, $t5, 0x400074    # branch to done
		lw $t4, 0($t3)				#load array value    #0x 400'060
		add $t2, $t2, $t4			#add to total
		addi $t3, $t3, 4			#increment address
		addi $t0, $t0, 1			#increment loop counter
		beq $0, $0, 0x40005c          #back to sumLoop                    # 0x 400'070

#done

