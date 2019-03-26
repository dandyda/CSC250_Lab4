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
 **************************************************************************
 NEED to eliminate random generator and activate read_file function********
 **************************************************************************
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
                else printf("x");
                //print one number from the table w/out \n
            }       
        printf("\n");//after loop prints each item for a row (above) we print a \n to drop to the next line in output
        
    }
}

void countNeighbors(int sourceGrid[MAXROWS][MAXCOLS], int countGrid[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j, deltaRow, deltaCol;

for (i=0; i < nRows; i++)  { //loop for each row...
    for (j=0; j < nCols; j++)  { //loop for(2) each column....
        countGrid[i][j] = 0; //ensures neighbor count starts at zero
        for ( deltaRow = -1; deltaRow <= 1; deltaRow++)  { //loop for(3) each neighbor row....
            for ( deltaCol = -1; deltaCol <= 1; deltaCol++)  { //loop for(last) each neighbor column....
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
//    read_file (int table[MAXROWS][MAXCOLS], int nRows, int nCols);
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


int main(int argc, int *argv[])
{ 
	int table[100];//Array is for transfering .txt data from fileData and passes to golGrid[rowIndex][colIndex]
	int i;//establishes a counter and sets to zero, i will incremently store each value from .txt file
	//int screenSize;//derived from first value encountered in .txt file and is used to set userRows and useCols
	int fileData;//.txt file is read then stored into fileData
	FILE * myFile;// declares myFile as a file pointer 

	myFile = fopen("lifeTwo.txt","r");//file ptr 'myFile' opens .txt and reads
	
	//if statement ensures that if file is not found an exit is executed to prevent crash
	if (myFile == NULL) {
		printf("***File Not Found***\n");
		exit(1);	
		}
	
	fscanf(myFile, "%d", &fileData);//reads .txt file and sets row width and height (first line of .txt) by using fileData to store data in
		
    int useRows = fileData, useCols = fileData; // rows and columns of the active array (square screen)
    
    while ( ! feof(myFile) ) { //feof(file end of file) will be true if we hit end of file in previous attempt
        fscanf(myFile, "%d", &fileData);//attempt to read next value and store in fileData       
        table[i] = fileData;//stores data in array**********so now I need to use array as games input.
        i++;//keeps reading values from .txt
    }//end while
        
    //.txt file should be closed when your program is done using it
    fclose(myFile);


    int rowIndex, colIndex;   
    int golGrid[MAXROWS][MAXCOLS];  
    int golNeighborCounts[MAXROWS][MAXCOLS];
    
    
    for (rowIndex=0; rowIndex < useRows; rowIndex++)//loop over the rows of the table
    {   //nothing stops you from having instructions before the loop within loop if needed
        for (colIndex=0; colIndex < useCols; colIndex++)//loop over the columns of the table
         {
           golGrid[rowIndex][colIndex] = table[i];
         
         }//end for(2)       
        
    }//end for(1)    


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
        system("clear");//system function runs command 'clear' on WindowsOS 'clr'
            
    }   
    
    
}



