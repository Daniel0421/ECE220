#include "sudoku.h"
/*Intro Paragraph:  
  Partners: hc55, jihwank4
  In this MP7, we have implemented the Sudoku game. 
  The code presented here consists of functions designed to solve Sudoku puzzles. 
  This code aims to solve the Sudoku game automatically using for loops and recursive backtracking. 
  The functions included in this code cover various aspects of Sudoku solving, such as checking the 
  validity of a value in a given cell, solving the Sudoku puzzle, and printing the solved puzzle. 
  Specific walkthrough of these codes are commented on below in their respective functions. 
  These functions work together to provide a functional Sudoku-solving tool.  
*/
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j;                //declare loop counter variable

  for (j=0; j<9; j++) {
    if (sudoku[i][j] == val) {  //check if val exists in current row
      return 1;                 //if so return true
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;              // declare loop counter variable

  for (i=0; i<9; i++) {
    if (sudoku[i][j] == val) {  //check if val exists in current column
      return 1;                 //if so return true
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int zone_i = i/3;           //dividing i,j by three will give use the 3x3 zone
  int zone_j = j/3;
  int m,n;                    //declare loop counter variable

  for (m = zone_i*3; m < zone_i*3+3; m++) {
    for (n = zone_j*3; n <zone_j*3+3; n++) {
      if (sudoku[m][n] == val) {
        return 1;
      }
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku)) {        //checks validity of entire sudoku by checking all rows and columns individually. 
    return 0;
  }
  else if (is_val_in_3x3_zone(val, i, j, sudoku) == 1) {                       //checks validity of entire sudoky by checking the 3x3 sub squares indiviually.      
    return 0;
  }
  else{
    return 1;
  }

  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;                            //declare loop counter variables
  int num;                            //declare variable for a number to fitted in between 1 and 9

  for (i = 0; i < 9; i++) {           //iterate through all cells
    for (j = 0; j<9; j++) {
      if (sudoku[i][j] == 0) {        //if an empty cell is found
        for (num=1; num <10; num++) { //iterate through all possible numbers to be filled between 1 and 9
          if (is_val_valid(num, i, j, sudoku)) {    //check if num is valid in this cell
            sudoku[i][j] = num;       //if valid, replace the empty cell with num
            if (solve_sudoku(sudoku)) { //call solve_sudoku recursively to check for next empty cells if they exist
              return 1;
            }
            sudoku[i][j] = 0;         //if no num is possible, i.e. game is broken, fill the cell with 0, empty.
          }
        }
        return 0;
      }
    }
  }

  return 1;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





