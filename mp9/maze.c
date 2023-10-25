#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*Partners: hc55, jihwank4
In this MP, we have implemented a program that solves a maze based on the maze input in a text file. The code mainly consists of four
main functions, createMaze(), destroyMaze(), printMaze(), and solveMazeDFS() respectively. The main concept practiced in this code is the
utlization of structs, 2D arrays, pointers, memory allocation, and recusion. The purpose of each function is self-explanatory from their
names, however they will be explained in much deeper detail in comments within each function.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *openfile = fopen(fileName, "r");                      //open file using pointer

    //memory allocation
    maze_t *maze = malloc(sizeof(maze_t));                      //allocate memory for the maze and initalize its pointer

    int row,col;
    fscanf(openfile, "%d %d", &col, &row);                      //read dimensions and store in row and col
    maze->height = row;
    maze->width = col;
    maze->cells = malloc(sizeof(char*) * row);    //allocate memory for the row pointer

    int i,j;                                                    //initialize loop counter
    char mem;

    for (i=0;i<row;i++) {
        maze->cells[i] = malloc(sizeof(char*) * col);    //allocate memory for array in each row
    }
    fscanf(openfile, "%*c"); // Read and discard the newline character

    for (i=0;i<row;i++) {
        for (j=0;j<col;j++) {
            fscanf(openfile, "%c", &mem);
            maze->cells[i][j] = mem;
            if (mem=='S') {                         //if current character is start 
                maze->startColumn = j;              //set start conditions
                maze->startRow = i;
            }
            else if (mem=='E') {                    //if current character is end
            maze->endColumn = j;                    //set end conditions
            maze->endRow = i;
            }
        }
        fscanf(openfile, "%*c"); // Read and discard the newline character
    }
    fclose(openfile);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;              //initialize loop counter
    int row = maze->height;

    for (i=0;i<row;i++) {       //for each row, free the cells
        free(maze->cells[i]);
    }

    free(maze->cells);          //free entire maze
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;                    //initialize loop counters
    int row = maze->height;
    int col = maze->width;

    for (i=0;i<row;i++) {       //iterate through all cells in 2d array
        for (j=0;j<col;j++) {
            printf("%c", maze->cells[i][j]);        //print value of cell in each iteration
        }
        printf("\n");           //print next line as inner array is finished
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    //Book-keeping first before undergoing recursion
    if (col<0 || col>=(maze->width) || row<0 || row>=(maze->height)) {      //check if current position is out of bounds
        return 0;
    }
    if (maze->cells[row][col] == 'E') {     //return 1 if last cell is "E"
        return 1;   
    }
   
    if (maze->cells[row][col] != 'S') {
        if (maze->cells[row][col]!=' ') {
            return 0;                       //return 0 if non empty and not at start
        }
       maze->cells[row][col]='*';      //mark solution
    }

    //now undergo recursion
    if (solveMazeDFS(maze,col,row+1)) {     //check if there exists path in this direction
        return 1;
    }
    if (solveMazeDFS(maze,col+1,row)) {     //check if there exists path in this direction
        return 1;
    }
    if (solveMazeDFS(maze,col,row-1)) {     //check if there exists path in this direction
        return 1;
    }
    if (solveMazeDFS(maze,col-1,row)) {     //check if there exists path in this direction
        return 1;
    }
    if (maze->cells[row][col]!='S') {
         //if none of the directions provide solution, backtrack
        maze->cells[row][col] = '~';
    }
    return 0;
}
