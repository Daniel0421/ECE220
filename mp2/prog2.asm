;Partners: hc55, jihwank4
;
;Intro paragraph: 
;In this programming assignment, we have created a calculator that takes postfix expression notation as inputs, using stacks in LC-3. The program begins by reading input from keyboard, then checks for errors. The errors from keyboard
;arise from cases when characters are inputed. When these cases are detected, program directly displays an error message and HALTs. However, we also have to bypass characters when space (" ") is detected, and this is the subroutine "TEST_SPACE" 
;When all error filtering is completed, each input is examined, starting with digits 0 to 9, then operators. Finally, when program detects that input is neither digits, operators, special by characters ("=" and " "), it goes back to error message.
;When all input is examined, program goes to the EVALUATE subroutine, which then starts implementing calculations.
.ORIG x3000
	
;your code goes here

READ
	GETC					;Load input from keyboard, saved to R0
	OUT						;"Echo" input to the screen

TEST_EQUAL
	LD R1, EQUALITY
	JSR TWOS_COMP_MINUS		;R0-R1, checking if input is equality sign
	BRnp TEST_SPACE			;If input is not equality sign, check if it is spacebar

TEST_ERROR
	LD R2, LAST_STACK
	LD R3, STACK_FIRST
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R2, R3			;Test if "=" is the last stack
	BRn INVALID_EXPRESSION ;If not, branch

	LDI R0, FINAL		;Load the final result to R5

	JSR POP
    ADD R5,R0,#0
	ADD R3,R5,#0
	
	BRnzp PRINT_HEX		;Print its value in hexadecimal
	

INVALID_EXPRESSION
	LEA R0, ERROR_MESSAGE	;Print error message
	PUTS
	HALT

TEST_SPACE
	LD R1, SPACE
	JSR TWOS_COMP_MINUS		;R0-R1, checking if input is spacebar
	BRz READ				;Continue reading next input
	BRnzp EVALUATE ;NO EQUAL, NO SPACE -> digit, operator, none

;Commands
EQUALITY 		.Fill x003D
SPACE 			.FILL x0020
LAST_STACK 		.FILL x3FFF
ERROR_MESSAGE	.STRINGZ "Invalid Expression"
OFFSET_ASCII 	.FILL x0030
STACK_FIRST		.FILL x4000	
FINAL 			.FILL x4000





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

NUM 			.FILL x0030  	;'0'
LET 			.FILL x0037  	;'A'-10

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

PRINT_HEX                            ;Subroutine to print hex value to screen after evaluating code given first line of Code. Taken and accordingly fixed from lab1. 
START	
	AND R6, R6, #0
  	ADD R6, R6, #4    	;initialize printed hex counter to 4 in order to decrement it after each hex is printed.

;------------------------------------------------------------------------------------------------------------------------

;below is loop to initialize digit and bit counter

INI
  	AND R1, R1, #0
  	ADD R1, R1, #4    	;initialize bit counter.
  	AND R2, R2, #0    	;initialize digit.

;------------------------------------------------------------------------------------------------------------------------

;below is loop to shift digit until we go print it.

GO_PRINT
	ADD R1, R1, #0		;loop to check if bit counter now hit zero and go to print the hex we have.
	BRz PRINT

SHIFT_DIGIT
	ADD R2, R2, R2		;shift digit left.

DECIDE
  	ADD R3, R3, #0		;Is R3<0?
  	BRn ADD_ONE      	;branch to ADD_ONE if MSB=1
  	BRnzp ADD_ZERO

ADD_ONE
  	ADD R2, R2, #1   	;add 1 to digit.
	BRnzp SHIFT_R3

ADD_ZERO
	ADD R2, R2, #0		;add 0 to digit.
	BRnzp SHIFT_R3

SHIFT_R3
  	ADD R3, R3, R3    	;left shift R3.
  	ADD R1, R1, #-1   	;decrement bit counter.
  	BRnzp GO_PRINT		;jump to loop which determines if we should start printing.

;------------------------------------------------------------------------------------------------------------------------

;below is the loop used to print the hex on screen.

PRINT
  	ADD R0, R2, #-9   	;check if digit<9
  	BRp LT
  	BRnzp DIGIT

;below is to determine whether the hex to be printed is between 0-9 or A-F

LT
  	LD R0, LET 		;ld R6 with 'A'-10
	BRnzp SCREEN
 
DIGIT
	LD R0, NUM		;load R6 with ascii for '0' 	
	BRnzp SCREEN

;below is the part to print the hex on screen		

SCREEN	
	ADD R0, R0, R2   	;load R0 with ascii character to be printed
  	OUT
  	
	ADD R6, R6, #-1   	;decrement hex print counter as printed one hex
  	BRp INI			;if we haven't printed all four hex, go back to initializing digit and bit counter

DONE	
	HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE


;your code goes here
LD R2, OFFSET_ASCII ;x0000
NOT R2, R2			;x1111
ADD R2, R2, #1		;x0000


TEST_ZERO
	LD R1, ZERO
	JSR TWOS_COMP_MINUS
	BRnp TEST_ONE				;If not zero, test one	
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input
	
TWOS_COMP_MINUS					;Calcuates R0-R1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R0
	RET

TEST_ONE
	LD R1, ONE
	JSR TWOS_COMP_MINUS
	BRnp TEST_TWO				;If not one, test two
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_TWO
	LD R1, TWO
	JSR TWOS_COMP_MINUS
	BRnp TEST_THREE				;If not two, test three
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_THREE
	LD R1, THREE
	JSR TWOS_COMP_MINUS
	BRnp TEST_FOUR				;If not three, test four
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_FOUR	
	LD R1, FOUR
	JSR TWOS_COMP_MINUS
	BRnp TEST_FIVE				;If not four, test five
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_FIVE
	LD R1, FIVE
	JSR TWOS_COMP_MINUS
	BRnp TEST_SIX				;If not five, test six
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_SIX
	LD R1, SIX
	JSR TWOS_COMP_MINUS
	BRnp TEST_SEVEN				;If not six, test seven
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_SEVEN
	LD R1, SEVEN
	JSR TWOS_COMP_MINUS
	BRnp TEST_EIGHT				;If not seven, test eight
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_EIGHT
	LD R1, EIGHT
	JSR TWOS_COMP_MINUS
	BRnp TEST_NINE				;If not eight, test nine
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

TEST_NINE
	LD R1, NINE
	JSR TWOS_COMP_MINUS
	BRnp TEST_PLUS				;If not nine, test operator, plus
	ADD R0, R0, R2
	JSR PUSH					;Since correct input is read, push
	BRnzp READ					;Continue reading next input

;Now that the values are not digits, we test if they are operators

TEST_PLUS
	LD R1, ADDITION
	JSR TWOS_COMP_MINUS
	BRnp TEST_MINUS				;If not plus, test operator, minus
	BRnzp PLUS					;Since correct input is read, branch

TEST_MINUS
	LD R1, SUBTRACTION
	JSR TWOS_COMP_MINUS
	BRnp TEST_MULTIPLY			;If not minus, test operator, multiply
	BRnzp MIN					;Since correct input is read, branch

TEST_MULTIPLY
	LD R1, MULTIPLICATION
	JSR TWOS_COMP_MINUS
	BRnp TEST_DIVIDE			;If not multiply, test operator, divide
	BRnzp MUL					;Since correct input is read, branch

TEST_DIVIDE
	LD R1, DIVISION
	JSR TWOS_COMP_MINUS
	BRnp TEST_EXPONENT			;If not divide, test operator, exponent
	BRnzp DIV					;Since correct input is read, branch

TEST_EXPONENT
	LD R1, EXPONENTION
	JSR TWOS_COMP_MINUS			
	BRnp INVALID_EXPRESSION		;Since now none of the values for operators are detected, print error message
	BRnzp EXP					;Since correct input is read, branch

TEST_UNDERFLOW
	AND R5, R5, #1
	BRp INVALID_EXPRESSION
	RET
;Commands for digits
ZERO 	.FILL x0030
ONE 	.FILL x0031
TWO		.FILL x0032
THREE 	.FILL x0033
FOUR	.FILL x0034
FIVE 	.FILL x0035
SIX 	.FILL x0036
SEVEN 	.FILL x0037
EIGHT 	.FILL x0038
NINE 	.FILL x0039	

;Commands for operators
ADDITION 		.FILL x002B
SUBTRACTION 	.FILL x002D
MULTIPLICATION 	.FILL x002A
DIVISION 		.FILL x002F
EXPONENTION 	.FILL x005E



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;The subroutines below are reached only when the respected operators are found
;POP_TWICE
;	JSR POP					;First pop
;	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
;	JSR POP
;	LDI R3, STACK_TOP		;Store second popped value in R3 - this is the first operand
;	RET
PLUS	
;your code goes here
	JSR POP					;First pop
	JSR TEST_UNDERFLOW
	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
	JSR POP
	JSR TEST_UNDERFLOW
	LDI R3, STACK_TOP			;Since correct operand is found, pop twice
	ADD R0, R3, R4
	JSR PUSH
	BRnzp READ

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	JSR POP					;First pop
	JSR TEST_UNDERFLOW
	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
	JSR POP
	JSR TEST_UNDERFLOW
	LDI R3, STACK_TOP			;Since correct operand is found, pop twice
	NOT R4, R4				;Complement R4 (second operand) then add 1
	ADD R4, R4, #1
	ADD R0, R3, R4			;Add to subtract R3-R4
	JSR PUSH
	BRnzp READ
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	JSR POP					;First pop
	JSR TEST_UNDERFLOW
	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
	JSR POP
	JSR TEST_UNDERFLOW
	LDI R3, STACK_TOP			;Since correct operand is found, pop twice
	AND R1, R1, #0			;Reset R1
	ADD R1, R4, R1			;Initialize counter to R1, equal to second operand for mulplication
	ADD R1, R1, #-2			;Subtract counter by 2
	ADD R0, R3, R3			;Multiply R0 by 2

MUL_COUNTER
	ADD R0, R0, R3			;Add R0+=R3, this is multiplying by 2
	ADD R1, R1, #-1			;Decrease counter by 1
	BRnp MUL_COUNTER
	JSR PUSH
	BRnzp READ
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	JSR POP					;First pop
	JSR TEST_UNDERFLOW
	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
	JSR POP
	JSR TEST_UNDERFLOW
	LDI R3, STACK_TOP		;Since correct operand is found, pop twice
	NOT R4, R4				;Complement to make -R4
	AND R0, R0, #0
	ADD R4, R4, #1
	ADD R1, R3, R4			;Subtract R1=R3-R4
	BRn NO_QUOTIENT
	BRnzp DIV_COUNTER

NO_QUOTIENT					;If divisor > divident --> OUT 0
	AND R0, R0, #0
	JSR PUSH
	BRnzp READ

DIV_COUNTER
	ADD R0, R0, #1			;Increment counter by 1 (this calculates result, hence quotients)
	ADD R1, R1, R4			;Subtract R1-=R4
	BRp DIV_COUNTER
	BRz DIV_ZERO
	JSR PUSH
	BRnzp READ

DIV_ZERO
	ADD R0, R0, #1
	JSR PUSH
	BRnzp READ
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	JSR POP					;First pop
	JSR TEST_UNDERFLOW
	LDI R4, STACK_TOP		;Store first popped value in R4 - this is the second operand
	JSR POP
	JSR TEST_UNDERFLOW
	LDI R3, STACK_TOP	


	AND R6, R6, #0			;Initialize exponent counter
	ADD R6, R6, R4
	ADD R6, R6, #-1

	AND R4, R4, #0			;Set R4 as R3 for next multiplication
	ADD R4, R4, R3

	
	
EXP_MUL	
	AND R1, R1, #0			;Reset R1
	ADD R1, R3, R1			;Initialize counter to R1, equal to First operand for mulplication
	ADD R1, R1, #-2			;Subtract counter by 2
	ADD R0, R4, R4			;Multiply R0 by 2
	AND R3, R3, #0

EXP_MUL_COUNTER
	ADD R0, R0, R4			;Add R0+=R4
	ADD R1, R1, #-1			;Decrease counter by 1
	BRnp EXP_MUL_COUNTER
	ADD R3, R3, R0

	AND R1, R1, #0			;Reset R1
	ADD R1, R3, R1			;Initialize counter to R1, equal to second operand for mulplication
	ADD R1, R1, #-2			;Decrease counter by 2

	ADD R6, R6, #-1
	BRnp EXP_MUL_COUNTER
	
EXP_DONE
	JSR PUSH
	JSR READ 

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END
