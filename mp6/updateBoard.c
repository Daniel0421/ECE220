/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col) {
    int i,j;                                //initialize loop counter
    int liveNeighbor = 0;           //initialize live neighbor cells and status = 0

    for (i=row-1; i<=row+1; i++) {
        //if row is within bounds of the board
        if (i>=0 && i<boardRowSize) {
            for (j=col-1; j<=col+1; j++) {
                //if col is within bounds of the board
                if (j>=0 && j<boardColSize) {
                    //if current cell is not at (row,col)
                    if (!(i==row && j==col)) {
                        if (*(board+(i*boardColSize+j)) == 1) {
                            liveNeighbor++;         //increment liveNeighbor count
                        }
                    }
                }
            } 
        }
    }
    return liveNeighbor;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int currLiveNeighbor;
    int tempBoard[boardColSize*boardRowSize];        //initialize temporary board 
    int i,j;      //intilize loop counter for copying board to newBoard

    for (i=0; i<boardColSize*boardRowSize; i++) {
        tempBoard[i] = *(board+i);      //copy board to newBoard
    }
    for (i=0; i<boardRowSize; i++) { 
        for (j=0; j<boardColSize; j++) {
            //check live neighbor cells for every cell in tempBoard
            currLiveNeighbor = countLiveNeighbor(tempBoard,boardRowSize, boardColSize, i, j);
            //if current cell = 0, only becomes 1 if it has exactly 3 live neighbors
            if (tempBoard[i*boardColSize+j] == 0) {
                if (currLiveNeighbor == 3) {
                    *(board+(i*boardColSize+j)) = 1;
                }
            }
            //if current cell = 1 and 2 or 3 live neighbors exist, cell remains alive
            else if (currLiveNeighbor == 2 || currLiveNeighbor == 3) {
                *(board+(i*boardColSize+j)) = 1;
            }
            //otherwise cell dies
            else {
                *(board+(i*boardColSize+j)) = 0;
            }
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int i,j;                                                    //initialize loop counter
    int nextBoard[boardRowSize*boardColSize];                   //initialize nextBoard to compare with board
    
    for (i=0; i<boardRowSize*boardColSize; i++) {
        nextBoard[i] = *(board+i);                              //copy board to nextBoard
    }

    updateBoard(nextBoard, boardRowSize, boardColSize);     //updateBoard to nextBoard

    for (i=0; i<boardRowSize; i++) {
        for (j=0; j<boardColSize; j++) {
            //return 0 if cell changes statea
            if (nextBoard[i*boardRowSize+j] != *(board + (i*boardRowSize+j))) {
                return 0;
            }
        }
    }
    return 1;
}