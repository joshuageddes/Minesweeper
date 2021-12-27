#include <stdio.h>
#include <stdlib.h>

char mineGrid[10][10];
char realGrid[10][10];
int mineCount = 10;

void printGrid();
int check(int row, int col);
void flag(int row, int col);
int determineMove();
int checkWin();

int main() {
    //Change value in srand function for different generated minefields and thus different results
    //AI is not perfect and will not solve 100% of time, makes guesses occasionally (minesweeper is a bit of luck)
    srand(3);



    int row, column, rowIndex, columnIndex;
    char move;

    //board initialization

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mineGrid[i][j] = '0';
            realGrid[i][j] = '*';
        }
    }

    for (int i = 0; i < mineCount; i++) {

        do {
            row = rand() % 10;
            column = rand() % 10;
        } while (mineGrid[row][column] == 'M');

        mineGrid[row][column] = 'M';

        //Code used repeatedly; iterates through all adjacent cells, conditional checks for out of bounds errors
        for (int r = -1; r < 2; r++) {
            for (int c = -1; c < 2; c++) {
                rowIndex = row + r;
                columnIndex = column + c;


                if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10) {


                    if (mineGrid[rowIndex][columnIndex] != 'M') {
                        mineGrid[rowIndex][columnIndex] = (char) ((int) mineGrid[rowIndex][columnIndex] + 1);
                    }
                }


            }
        }


    }



    int status = 0;
    int moveNumber = 1;


    //Algorithm begins now!

    //Runs until condition is met
    while (status == 0) {


        int moveMade = 1;

        //All cells are iterated through constantly until a full loop is done where no moves can be made
        //Similar to a bubble sort algorithm
        while (moveMade) {
            moveMade = 0;

            for (int row = 0; row < 10; row++) {
                for (int col = 0; col < 10; col++) {

                    char state = realGrid[row][col];



                    //If a number exists within a cell
                    if (state != '*' && state != 'F') {



                        //This code determines the amount of adjacent unrevealed cells and flagged cells (mines)

                        int unrevealedCellCount = 0;
                        int flagCount = 0;


                        for (int r = -1; r < 2; r++) {
                            for (int c = -1; c < 2; c++) {
                                int rowIndex = row + r;
                                int columnIndex = col + c;

                                if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10) {
                                    if (realGrid[rowIndex][columnIndex] == '*') {


                                        unrevealedCellCount += 1;

                                    } else if (realGrid[rowIndex][columnIndex] == 'F') {

                                        flagCount += 1;


                                    }
                                }
                            }


                        }

                        //Algorithmic magic below, let x = # of adacent mines - # of adjacent flags

                        //If empty adjacent cells = x, all empty cells must be flagged

                        if (unrevealedCellCount == (int) state-48-flagCount) {
                            for (int r = -1; r < 2; r++) {
                                for (int c = -1; c < 2; c++) {
                                    int rowIndex = row + r;
                                    int columnIndex = col + c;


                                    if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10) {
                                        if (realGrid[rowIndex][columnIndex] == '*') {

                                            flag(rowIndex, columnIndex);
                                            printf("Move #%d\n", moveNumber);
                                            printGrid();
                                            moveNumber += 1;
                                            moveMade = 1;
                                        }
                                    }
                                }
                            }


                            //If empty adjacent cells > 0 and x = 0 (so no mines left in vicinity), all adjacent cells can be safely checked

                        } else if (unrevealedCellCount > 0 && (int) state -48 - flagCount == 0) {
                            for (int r = -1; r < 2; r++) {
                                for (int c = -1; c < 2; c++) {
                                    int rowIndex = row + r;
                                    int columnIndex = col + c;


                                    if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10) {
                                        if (realGrid[rowIndex][columnIndex] == '*') {

                                            check(rowIndex, columnIndex);
                                            printf("Move #%d\n", moveNumber);
                                            printGrid();
                                            moveNumber += 1;
                                            moveMade = 1;
                                        }
                                    }
                                }
                            }
                        }


                    }
                }
            }

        }


        if (checkWin()) {
            status = 1;
            break;
        }
        //No moves are made and algorithm cannot determine an safe solution, so an empty square is chosen at random
        do {
            row = rand() % 10;
            column = rand() % 10;


        } while (realGrid[row][column] != '*');


        if (check(row, column)) {
            status = 2;
        }
        printGrid();
        printf("Move #%d\n", moveNumber);
        moveNumber+=1;

    }




    //Final statement dependent on exit status
    if (status == 2) {
        printf("You hit a mine, game over.\n");

    } else {
        printf("Congratulations! You win!\n");
    }


    return 0;



}



int check(int row, int col){
    //4 possible cases
    char cell = mineGrid[row][col];



    //case 1 : mine hit
    if (cell == 'M'){
        realGrid[row][col] = 'M';
        return 1;
    }

        //case 2 : Non zero number is hit. Also acts as a "base case" when function is run recursively
    else if (cell != '0'){
        realGrid[row][col] = cell;
        return 0;

    }


    else {

        //case 3 : Zero hit, and is not yet revealed on the board
        if (realGrid[row][col] == '*' || realGrid[row][col] == 'F') {
            realGrid[row][col] = '0';

            //Similar adjacent square code explained previously
            for (int r = -1; r < 2; r++) {
                for (int c = -1; c < 2; c++) {
                    int rowIndex = row + r;
                    int columnIndex = col + c;


                    if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10) {

                        //Runs check recursively on all adjacent squares if a 0 is found
                        check(rowIndex, columnIndex);

                    }

                }
            }

        }

            //case 4: 0 hit, and is already revealed. Acts as one of the "base cases" recursively
        else {
            return 0;

        }

    }



}
void flag(int row, int col) {


    if (realGrid[row][col] == '*') {
        realGrid[row][col] = 'F';

    } else if (realGrid[row][col] == 'F') {
        realGrid[row][col] = '*';

    }
}


int checkWin() {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            if (realGrid[i][j] == '*' || realGrid[i][j] == 'F') {
                count += 1;
            }
        }
    }

    //If the amount of unrevealed squares is equal to the number of mines, the player wins (return 1) or else continue playing (return 0)
    if (count == mineCount) {
        return 1;
    } else {
        return 0;
    }


}

void printGrid(){
    for (int r=0; r<10; r++){
        for (int c=0; c<10; c++){
            printf("%c  ", realGrid[r][c]);
        }
        printf("\n");
    }


}
