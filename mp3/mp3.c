/*  Partner: hc55, jihwank4
    Intro paragraph: This program written in C calculates the values of pascal's triangle in nth row which is inputted by user. 
    This program consists of two main loops, that calculates the kth digit and combination operation respectively. Further specific logic and formulas are commented below.

*/


#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
    unsigned long int final_result = 1;
    unsigned long int k_variable;
    unsigned long int pi_index;

    if (row == 0) {                                                           // In pascal's triangle, it always starts with 0 C 0, which is 1. Implementing this conditional statement optimizes code efficiency
      printf("1\n");
      exit(0);                                                                // If n (row)=0 is detected, print 1 and exit entire program
    } else {                                                                  // The formula used in this program for computing combination has one limitation, that it cannot compute when k=0. However, the result of n C 0 is always 1.
      printf("1 ");                                                          
    }

    for (k_variable= 1; k_variable <= row; k_variable++) {                    // Initalize outer loop, iterating through the numbers of pascal values in the given row
      final_result = 1;                                                       // As the combination formula requires self-multiplication, intial value of final_result is set to 1
      for (pi_index = 1; pi_index <= k_variable; pi_index++) {                // Initialize inner loop, allowing the combination formula (pi notation) to work properly. This is essentially calculating the variable k
        final_result = final_result * (row + 1 - pi_index) / pi_index;        // This is the formula used for combination
      }
      printf("%lu ", final_result);                                           // Once each inner loop is executed, print the final value for the kth pascal value for the nth row. This process is repeated n times
      

    }
    printf("\n");

  return 0;
}
