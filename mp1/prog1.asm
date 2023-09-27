; Jihwan Kim (jihwank4), Daniel Cho (HC55) are in the same group.

; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
;------------------------------------------------------------------------------------------------------------------------

;GROUP: Jihwan Kim (jihwank4), Daniel Cho (hc55)

;Intro paragraph:
;The following code is divided into 6 parts.
;First, initializing conditions for line counter, and an incrementor to keep track of the character to be printed and counted.
;Second, starting off with non alphabets, @, as I don't want the new line command to work there. (This was not needed, but
;at the start of the MP, we thought we would need to add the number of capitals: A-Z, with lower cases:a-z, which was not needed
;but did not want to change the code any further cause we would have needed to move the new line to another loop etc.)
;Third, the formating part where we move to the next line, print the character and a space.
;Fourth, Initializing the digit and bit counter
;Fifth, the loop to shift the digit in order to go to the next printing loop to print the hex.
;Sixth, printing the hexadecimals and going back to the third part to start a new line.
;We have divided 16 bits into four chuncks of four bits, and used the flow chart provided to us from the lab.

;------------------------------------------------------------------------------------------------------------------------

Register Table

	;R0 : temporary values.
	;R1 : bit counter.
	;R2 : digit.
	;R3 : Acts as R3 in flowchart.
	;R4 : increment character counter.
	;R5 : hex print counter = check how many hex have been printed.
	;R6 : 27 line printed? counter.

;------------------------------------------------------------------------------------------------------------------------

;below is intializing conditions

	LD R6, NUM_BINS		;initialize line counter to 27 as there are 27 lines to be printed to halt the code.
  	AND R4, R4, #0		;init character incrementor, currently 0 as we start from @

;------------------------------------------------------------------------------------------------------------------------

;below is starting with @ as the START loop as a next line output.
	
	LD R0, AT		;load @ to R0 and print @.
	OUT

	LD R0, SPACE		;print space for formating.
	OUT
	
	AND R5, R5, #0		;initialize hex print counter as for @, it will jump to the loop after it declares the print counter.
	ADD R5, R5, #4
	
	LD R3, HIST_ADDR	;this part is explained in START loop.
  	ADD R3, R3, R4    	
  	ST R3, TEMP  	
  	LDI R3, TEMP 	
	
	BRnzp INI		;as it is first line we don't need to print next line and all the initial conditions so jump straight to INI loop.

;------------------------------------------------------------------------------------------------------------------------

;the START loop is here to give the format "(Char)(space)" leaving the hex to the other loops.

START	LD R0, NL		;move to next line.
	OUT

	LD R0, AT		;load Ascii of @.
  	ADD R0, R0, R4 		;add character incrementor to @ to print the current counting character (A-Z).
  	OUT          		;print current character.

  	LD R0, SPACE  		;print space.
  	OUT
 	
	LD R3, HIST_ADDR	;load R3 with location of histogram
  	ADD R3, R3, R4    	;add character counter to store current char location to R3
  	ST R3, TEMP  		;store R3 to temporary location
  	LDI R3, TEMP 		;load R3 the number of char
  	
	AND R5, R5, #0
  	ADD R5, R5, #4    	;initialize printed hex counter to 4 in order to decrement it after each hex is printed.

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
  	
	ADD R5, R5, #-1   	;decrement hex print counter as printed one hex
  	BRp INI			;if we haven't printed all four hex, go back to initializing digit and bit counter

  	ADD R4, R4, #1		;if printed all four hex, increment R5 in order to get next character
  	ADD R6, R6, #-1   	;decrement counters for 27 lines to be printed
  	BRp START         	;loop if there are still more lines to print, otherwise all character are printed hence halt

;------------------------------------------------------------------------------------------------------------------------
	
	LD R0, NL		;although not needed, just here to match the out format.
	OUT

DONE 	HALT			;done

;------------------------------------------------------------------------------------------------------------------------

NL 		.FILL x000A 	;newline char
SPACE  		.FILL x0020  	;' '
AT 		.FILL x0040  	;'@'
NUM 		.FILL x0030  	;'0'
LET 		.FILL x0037  	;'A'-10
TEMP 		.BLKW #1


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
