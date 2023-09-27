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


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number <= 1) {return 0;} // change == to <= as the input number can also be negative
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
	  return 0; //swap 1,0 with line below cause it is 0 when not prime
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
	  if (i%j == 0) { //the modulus here means j*some number = i hence, j might be prime that we want to print
                if (is_prime(j)) {
		  k = i/j;  // change % to / as we do not want the remainder but the value itself as it is the value we want to know if it is a semiprime
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1; //set ret = 1
			break; //break the second for loop if the loop goes through the if statement as we want to move to the next number
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}