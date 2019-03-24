/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbors 
 * a cell dies of loneliness, if it has less than two neighbors 
 * a cell dies of overcrowding, if it has more than three neighbors 
 * a cell survives to the next generation, if it does not die of loneliness 
 * or overcrowding 
 *
 * In this version, a 2D array of ints is used with a 
 * random number generator.  A 1 cell is on, a 0 cell is off.
 *
 */




#include <stdio.h>
#include <stdlib.h>//system();
#include <time.h>
#include <unistd.h>//usleep, only on linux
#define MAXROWS 200
#define MAXCOLS 200

void printTableOfInts(int table[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j;
for (i=0; i < nRows; i++)//loop over the rows of the table
    {   //nothing stops you from having instructions before the loop within loop if needed
            for (j=0; j < nCols; j++)//loop over the columns of the table
            {
                printf("%5d", table[i][j]);//print one number from the table w/out \n
            }       
        printf("\n");//after loop prints each item for a row (above) we print a \n to drop to the next line in output
        
    }
}
void printGameOfLife(int table[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j;
for (i=0; i < nRows; i++)//loop over the rows of the table
    {   //nothing stops you from having instructions before the loop within loop if needed
            for (j=0; j < nCols; j++)//loop over the columns of the table
            {
                if (table[i][j]==1 ){
                    printf("*");
                }
                else printf(" ");
                //print one number from the table w/out \n
            }       
        printf("\n");//after loop prints each item for a row (above) we print a \n to drop to the next line in output
        
    }
}

void countNeighbors(int sourceGrid[MAXROWS][MAXCOLS], int countGrid[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j, deltaRow, deltaCol;

for (i=0; i < nRows; i++)  { //loop for each row...
    for (j=0; j < nCols; j++)  { //loop for each column....
        countGrid[i][j] = 0; //ensures neighbor count starts at zero
        for ( deltaRow = -1; deltaRow <= 1; deltaRow++)  { //loop for each neighbor row....
            for ( deltaCol = -1; deltaCol <= 1; deltaCol++)  { //loop for each neighbor column....
                //if sourceGrid[i+deltaRow][j+deltaCol] is 1 then add 1 to the count for that location
                //that means increment countGrid[i][j] 
                
                //if neighbor isn't out of bounds            
                if ( i+deltaRow >=0 && j+deltaCol >= 0 && i+deltaRow < nRows && j+deltaCol < nCols )  {
                    //if neighbor is not itself
                    if (  ( deltaRow != 0 ) || ( deltaCol != 0 )  ) {
                    //count the neighbor if its a 1
                    countGrid[i][j] = countGrid[i][j] + sourceGrid[i+deltaRow][j+deltaCol];
                    }//end last if
                }//end if
            }//end last for               
        }//end 3'rd for
    }//end 2'nd for
}//end for          

}//end function countNeighbors               

void updateGameOfLife(int golGrid[MAXROWS][MAXCOLS], int nRows, int nCols) 
{
    int countGrid[MAXROWS][MAXCOLS];
    countNeighbors(golGrid, countGrid, nRows, nCols);
    //look at each cell of the golGrid and corresponding count and decide whether it should be updated to a 1 or 0 according to the rules
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            if ( golGrid[i][j]==1 )  { //if cell is currently alive
                if ( countGrid[i][j] < 2 || countGrid[i][j] >= 4)  {
                    golGrid[i][j] = 0;
                }
        } else {// cell is currently empty
            if ( countGrid[i][j] == 3 )  {//we have exactly 3 neighbors
                golGrid[i][j] = 1; // a cell is born
            }
          }
        }


    }

}


int main(int argc, char *argv[])
{
    srand(time(NULL));//seed random generator at start
    
    int useRows = 20, useCols = 20; //how many rows and columns out of array we actually use
    int rowIndex, colIndex;
    //create a 2Darray filled with random#'s then print to terminal
    
    //2Darray of doubles
    int golGrid[MAXROWS][MAXCOLS];   /* {0},//initialze entire row to '0'      This commented out section is used without radom gen
                                        {0},                                   It also creates a 'walker' effect
                                        {0},
                                        {0,0,1,0,1,0,0,0,0,0},//walker
                                        {0,0,1,1,0,0,0,1,1,1},//walker                                        
                                        {0,0,0,1,0,0,0,0,0,0},//wlaker
                                        {0},
                                        {0},
                                        {0},
                                        {0}     };
                                    */
    int golNeighborCounts[MAXROWS][MAXCOLS];
    
    //Fill with random #s 0.0 to 100.0
    for (rowIndex=0; rowIndex < useRows; rowIndex++)//loop over the rows of the table
    {   //nothing stops you from having instructions before the loop within loop if needed
        for (colIndex=0; colIndex < useCols; colIndex++)//loop over the columns of the table
         {
           golGrid[rowIndex][colIndex] = rand() % 2;//remainder of divide by 2 is 0 or 1
         
         }       
        
    } 
//random generator


    //print array to terminal in a neat table
    //tips: use formatting in printf to make sure values are printed in same width and same number digits
      //in printf double is %lf, you can set size w/# between % and the letter(s)
      // example: %10lf<----extra spaces will be put in front of shorter #s
      //         for floats, put a .number after width to specify how many digits after
      //         decimal...ex// %10.3lf
      
    printTableOfInts( golGrid, useRows, useCols );
    printGameOfLife( golGrid, useRows, useCols );
    
    countNeighbors( golGrid, golNeighborCounts, useRows, useCols );
    
    printTableOfInts( golNeighborCounts, useRows, useCols );
    
    while(1)  {
        printf("----------------------------\n");
        printGameOfLife( golGrid, useRows, useCols );
        updateGameOfLife( golGrid, useRows, useCols );
        usleep(1000000);
        system("clear");//system function runs command 'clear' on windows 'clr'
            
    }   
    
    
}



