#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame -> cols = cols;          //use "->"" to access the struct 
    mygame -> rows = rows;          //use "->"" to access the struct 
    mygame -> score = 0;            //initialize score to 0

    int i;                          //initialize loop counter
    for (i=0; i<rows*cols; i++) {   //set all cells as -1
        mygame -> cells[i] = -1;
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr) -> cols = new_cols;    //reinitialize cols
    (*_cur_game_ptr) -> rows = new_rows;    //reinitialize rows
    (*_cur_game_ptr) -> score = 0;          //reinitialize score

    int i;
    for (i=0; i<new_rows*new_cols; i++) {   //reinitialize all cells to -1
        (*_cur_game_ptr) -> cells[i] = -1;
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if (cur_game->rows < row || cur_game->cols < col) {
        return &cur_game->cells[(cur_game->rows)*row+col]; //return pointer to the corresponding cell
    }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int i,j,k;                      //initialize loop counter
    int changedCells = 0;          //initialize variable that checks if change in tile has occured

    for (i=0; i<(cur_game->cols); i++) {
        int previous = -1;          //this checks for previously checked cells
        for (j=0; j<(cur_game->rows); j++) {
            if (cur_game->cells[(cur_game->cols)*j+i] != -1) {      //if current cell is not empty
                for (k=0; k<j; k++) {               //loop though a cells in the current row
                    if (cur_game->cells[(cur_game->cols)*k+i] == -1) {  //if the column cell is empty
                        cur_game->cells[(cur_game->cols)*k+i] = cur_game->cells[(cur_game->cols)*j+i]; //move up current cell to one above
                        cur_game->cells[(cur_game->cols)*j+i] = -1;      //reset current cell to -1
                        changedCells++;   //declare changed
                        break; //done moving cells so leave
                    } 
                }
                if ((k-1)!=previous) {      //if above row is not just modified
                    if (cur_game->cells[(k-1)*(cur_game->cols)+i]==cur_game->cells[(cur_game->cols)*k+i]) {     //if above cell is equal to current
                        cur_game->cells[(k-1)*(cur_game->cols)+i] += cur_game->cells[(k-1)*(cur_game->cols)+i];     //set above cell to 2*current 
                        cur_game->cells[(cur_game->cols)*k+i] = -1;     //empty current cell
                        cur_game->score += cur_game->cells[(k-1)*(cur_game->cols)+i];   //increment score with the new cell value
                        changedCells++; //declare changed
                        previous = k-1; //update previous to the newly modified row
                    }
                }
            }
        }
    }
    if (changedCells != 0) {
        return 1;
    }
    return changedCells;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int i,j,k;                  //initialize loop counter
    int changedCells = 0;       //initialize varible that checks if change in tile has occured

    for (i=0; i<(cur_game->cols); i++) {
        int previous = -1;      //this checks for previously checked cells
        for (j=(cur_game->rows)-1; i>=0; i--) {
            if(cur_game->cells[(cur_game->cols)*j+i] != -1) {       //if current cell is not empty
                for (k=(cur_game->rows)-1; k>j; k--) {              //loop throught the rows from bottom to top
                    if (cur_game->cells[(cur_game->cols*k+i)] == -1) {      //if the cell is empty
                        cur_game->cells[(cur_game->cols)*k+i] = cur_game->cells[(cur_game->cols)*j+i]; //move down current cell to one below
                        cur_game->cells[(cur_game->cols)*j+i] = -1;     //reset current cell to -1
                        changedCells++;       //declare changed
                        break;      //done moving cells so leave
                    }
                }
                if ((k+1)!=previous) {      //if below cell is not just modified
                    if (cur_game->cells[(cur_game->cols)*(k+1)+i]==cur_game->cells[(cur_game->cols)*k+i]) {     //if below cell is equal to current
                        cur_game->cells[(cur_game->cols)*(k+1)+i] += cur_game->cells[(cur_game->cols)*(k+1)+i];   //set below cell to 2*current
                        cur_game->cells[(cur_game->cols)*k+i] = -1;     //empty current cell
                        cur_game->score += cur_game->cells[(cur_game->cols)*(k+1)+i];      //increment score with the new cell value
                        changedCells++;   //declare changed
                        previous = k+1;     //update previous to the newly modified 
                    }
                }
            }

        }
    }
    if (changedCells != 0) {
        return 1;
    }
    return changedCells;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int i,j,k; //intialize loop counter
    int changedCells = 0;       //initialize variable that checks if change in tile has occured

    for (i=0; i<(cur_game->rows); i++) {
        int previous = -1;
        for (j=0; j<(cur_game->cols); j++) {
            if (cur_game->cells[(cur_game->cols)*i+j] != -1) {      //if current cell is not empty
                for (k=0; k<j; k++) {     //loops through the current row
                    if (cur_game->cells[(cur_game->cols)*i+k] == -1) {      //if the current cell is empty
                        cur_game->cells[(cur_game->cols)*i+k] = cur_game->cells[(cur_game->cols)*i+j];  //copy current cell to the cell one left
                        cur_game->cells[(cur_game->cols)*i+j] = -1;     //reset current cell to -1
                        changedCells++;       //declare changed
                        break;                  //done moving cells so leave

                    }
                }
                if ((k-1)!=previous) {          //if left cell is not just modified
                    if (cur_game->cells[(cur_game->cols)*i+(k-1)] == cur_game->cells[(cur_game->cols)*i+k]) {       //if left cell is equal to current
                        cur_game->cells[(cur_game->cols)*i+(k-1)] += cur_game->cells[(cur_game->cols)*i+(k-1)];     //set left cell to 2*current
                        cur_game->cells[(cur_game->cols)*i+k] = -1;     //empty current cell
                        cur_game->score += cur_game->cells[(cur_game->cols)*i+(k-1)]; //increment score with the new cell value
                        changedCells++;   //declare changed
                        previous = k-1;     //update previous to the newly modified 
                    }
                }
            }
        }
    }
    if (changedCells != 0) {
        return 1;
    }
    return changedCells;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i,j,k;              //intialize loop counter
    int changedCells = 0;   //initialize variable that checks if change in tile has occured
    
    for (i=0; i<cur_game->rows; i++) {
        int previous = -1;
        for (j=(cur_game->cols)-1; j>=0; j--) {
            if (cur_game->cells[(cur_game->cols)*i+j] != -1) {      //if current cell is not empty
                for (k=((cur_game->cols)-1); k>j;k--) {         //loop through the current row
                    if (cur_game->cells[(cur_game->cols)*i+k] == -1) {      //if cell is empty
                        cur_game->cells[(cur_game->cols)*i+k] = cur_game->cells[(cur_game->cols*i+j)];  //copy current cell to the cell one right
                        cur_game->cells[(cur_game->cols)*i+j] = -1;     //reset current cell to -1
                        changedCells++; //declare changed
                        break; //done moving cells so leave
                    }
                }
                if ((k+1)!=previous) {      //if right cell is not just modified
                    if (cur_game->cells[(cur_game->cols)*i+(k+1)] == cur_game->cells[(cur_game->cols)*i+k]) {   //if right cell is equal to current
                        cur_game->cells[(cur_game->cols)*i+(k+1)] += cur_game->cells[(cur_game->cols)*i+(k+1)];     //set right cell to 2*current
                        cur_game->cells[(cur_game->cols)*i+k] = -1;         //empty current cell
                        cur_game->score += (cur_game->cells[(cur_game->cols)*i+(k+1)]);     //increment score with the new cell value
                        changedCells++;               //declare changed
                        previous = k+1;                 //update previous to the newly modified
                    }
                }
            }
        }
    }
    if (changedCells != 0) {
        return 1;
    }
    return changedCells;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int returnValue = 0;        //initialize return value
    int posX, negX, posY,negY,origin;   //initialize direction variable
    int i,j;                    //initialize loop counter

    for (i=0; i<cur_game->rows; i++) {      //iterate through all rows
        for (j=0; j<cur_game->cols; j++) {  //iterate through all columns
            if (cur_game->cells[(cur_game->cols)*i+j] == -1) {      //if empty cells exist
                returnValue++;
            }

            if (j+1<cur_game->cols) {       //if cells exist to the right
                posX = cur_game->cells[(cur_game->cols)*i+(j+1)];
            }else {posX = 0;}

            if (j-1>=0) {                   //if cells exist to the left 
                negX = cur_game->cells[(cur_game->cols)*(i)+(j-1)];
            } else {negX = 0;}

            if (i-1>0) {                    //if cells exist above
                posY = cur_game->cells[(cur_game->cols)*(i-1)+j];
            } else {posY = 0;}

            if (i+1<cur_game->rows) {       //if cells exist below
                negY = cur_game->cells[(cur_game->cols)*(i+1)+j];
            } else {negY = 0;}

            origin = cur_game->cells[(cur_game->cols)*i+j];  //current cell
            if (origin==posX || origin==negX || origin==posY || origin==negY) { //if current cell and any neighboring cell have sam tile
                returnValue++;      //increment returnValue
            }
        }
    }
    if (returnValue != 0) {     //if returnValue is not 0 make returnValue 1
        returnValue = 1; 
    }
    return returnValue;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
