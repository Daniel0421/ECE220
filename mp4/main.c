// partners: hc55, jihwank4
// intro paragraph: for this mp we have been debugging the program for main.c and semiprime.c.
//                  for main.c, as in canvas we added a semicolon.
//                  for semiprime.c the debugging reasons and how are written below.
//                  briefly explaining, we swaped the return value for is_prime,
//                  changed % to /, set ret=1 once k is semiprime
//                  and break the loop after printing the semi prime as if not,
//                  we will be printing the same semi prime.

#include <stdlib.h>
#include <stdio.h>
#include "semiprime.h"


/*
    Main function: checks for valid inputs and runs the print_semiprimes function.
    Inputs: none
    Outputs: if provided a,b are invalid, returns -1. If there were no
    semiprimes in the range, returns 0. If there were semiprimes, returns 1.
*/
int main(){
   int a, b, ret;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return -1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return -1;
   }

   ret = print_semiprimes(a, b); //add semicolon as we need it, this bug was found through gdb
   return ret;
}