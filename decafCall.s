	.text
	.global _PrintInt
	.global _PrintString
	.global _Alloc
	.global _PrintBool
	.global _Halt
	.global _ReadLine
	.global _ReadInteger
	.global _StringEqual


	.type	__c_call, @function
__c_call:
	addiu   $sp, $sp, -20
        sw      $ra, 16($sp)
        la	$ra, __c_call_after_call
	jr	$t0
__c_call_after_call:
        lw      $ra, 16($sp)
        addiu   $sp, $sp, 20
        jr      $ra


        .type   _PrintString, @function
_PrintString:
	lw	$a0, 4($sp)
	la	$t0, __decaf_printString
	j	__c_call


	.type	_PrintInt, @function
_PrintInt:
	lw	$a0, 4($sp)
	la	$t0, __decaf_printInt
	j	__c_call	


	.type	_Alloc, @function
_Alloc:

        lw      $a0, 4($sp)
	la	$t0, __decaf_alloc
	j	__c_call

	.type	_PrintBool, @function
_PrintBool:

	lw	$a0, 4($sp)
	la	$t0, __decaf_printBool
	j	__c_call	

	.type	_Halt, @function
_Halt:

	lw	$a0, 4($sp)
	la	$t0, __decaf_halt
	j	__c_call	
	
	.type	_ReadLine, @function
_ReadLine:

	lw	$a0, 4($sp)
	la	$t0, __decaf_readLine
	j	__c_call	
	
	.type	_ReadInteger, @function
_ReadInteger:

	lw	$a0, 4($sp)
	la	$t0, __decaf_readInt
	j	__c_call	
	
	.type	_StringEqual, @function
_StringEqual:

	lw	$a0, 4($sp)
	lw	$a1, 8($sp)
	la	$t0, __decaf_stringEqual
	j	__c_call	

