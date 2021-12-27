#include <stdio.h>
#include <stdlib.h>

//global variable definitons
char mineGrid[10][10];
char realGrid[10][10];
int mineCount = 10;

//Function definitions
void printGrid();
int check(int row, int col);
void flag(int row, int col);
int checkWin();

int main() {


    srand(2);

//Defining more useful variables
    int row, column, rowIndex, columnIndex;
    char move;



    //initialize both grids
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            mineGrid[i][j] = '0';
            realGrid[i][j] = '*';
        }
    }

    //add mines to the mineGrid
    for (int i=0; i<mineCount; i++){

        //Run loop until a random cell is generated that does not contain a mine
        do{
            row = rand() % 10;
            column = rand() % 10;
        } while(mineGrid[row][column] == 'M');

        mineGrid[row][column] = 'M';

        //add +1 to all adjacent cells; iterates through -1 to 1 to access all possible surrounding cells

        for (int r=-1; r<2; r++){
            for (int c=-1; c<2; c++){
                rowIndex = row+r;
                columnIndex = column+c;

                //checks if adjacent index actually exists in grid; avoids out of index errors when cells are in edges/corners
                if (rowIndex > -1 && rowIndex < 10 && columnIndex > -1 && columnIndex < 10){

                    //Finally check that the cell does not contain a mine, then add one to the int representation of the number, then convert back to char
                    if (mineGrid[rowIndex][columnIndex] != 'M'){
                        mineGrid[rowIndex][columnIndex] = (char)((int)mineGrid[rowIndex][columnIndex] + 1);
                    }
                }



            }
        }


    }

    //game is ready to play!

    //status legend 0 - running 1 - win 2 - loss

    int status = 0;

    //Runs until condition is met
    while (status == 0){


        if(checkWin()){
            status = 1;
        }

        //Outputs info and gets commands
        printf("Enter 'c' for check cell, 'f' for flag cell.\n");
        printf("Enter command & cell row col:");
        scanf(" %c %d %d", &move, &row, &column);





        if (move == 'c'){
            //If a mine is found (check returns '1') then set status to 2
            if(check(row, column)){
                status = 2;
            }

        } else {
            flag(row, column);
        }


        printGrid();




    }

    //Final statement dependent on exit status
    if (status == 2){
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

//If the real grid has an unrevealed square or flag at the specified cell, it toggles it (like the actual minesweeper)
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

            //Counts all unrevealed squares
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
            //Prints every cell followed by two spaces
            printf("%c  ", realGrid[r][c]);
        }
        //After each row iteration, print new line
        printf("\n");
    }
}
