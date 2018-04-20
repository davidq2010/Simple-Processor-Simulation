# This is a test program it better not print this shit
# 000-18c

addi  $sp,  $sp,  0x10000000  # Memory contents follow 0x10000___
addi  $t1,  $t1,  6969
add   $t2,  $t1,  $t1         # Another comment for your ugly ass Tuan
sub   $t3,  $t1,  $t2
sw    $t1,  0($sp)            # Store the number in $t1 to the $sp + 0

sw    $t2,  4($sp)
sw    $t3,  8($sp)

# Should set
lw    $t4,  8($sp)
slt   $t3,  $t3,  $t1
lw    $t5,  4($sp)
lw    $t6,  0($sp)


beq   $t3


