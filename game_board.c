#include <stdio.h>

const int SQUARE_WIDTH = 5;     /* the width of each square is the number of '-' */
const int ROW_HEIGHT   = 2;     /* height of each row is the number of '|' */
const int BOARD_WIDTH  = 21;     /* number of squares in one row */
const int BOARD_HEIGHT = 21;     /* number of rows in one board */

int this_square_width;          /* width of current square */
int this_row_width;             /* width of current row */
int this_row_height;            /* height of current row */
int num_rows;                   /* how many rows we've done already */

int main(void) {

	for (num_rows = 0; num_rows < BOARD_HEIGHT; ++num_rows) {
		for (this_row_width = 0; this_row_width < BOARD_WIDTH; ++this_row_width) {
			printf("+");
			for (this_square_width = 0; this_square_width < SQUARE_WIDTH; ++this_square_width) {
				printf("-");
			}
		}
		printf("+\n");

		for (this_row_height = 0; this_row_height < ROW_HEIGHT; ++this_row_height) {
			for (this_row_width = 0; this_row_width < BOARD_WIDTH; ++this_row_width) {
				printf("|");
				for (this_square_width = 0; this_square_width < SQUARE_WIDTH; ++this_square_width) {
					printf(" ");
				}
			}
			printf("|\n");
		}
	}

	/* print closing row */
	for (this_row_width = 0; this_row_width < BOARD_WIDTH; ++this_row_width) {
		printf("+");
		for (this_square_width = 0; this_square_width < SQUARE_WIDTH; ++this_square_width) {
			printf("-");
		}
	}
	printf("+\n");

	return(0);
}
