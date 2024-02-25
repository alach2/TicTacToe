#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_BOARD_SZ 100
#define MIN_SCORE -100
#define MAX_SCORE 100

typedef char board_t[MAX_BOARD_SZ][MAX_BOARD_SZ];

struct Move { 
	int row;
	int col;
}; //this struct is used to find the best move, and it has a row and col variable

int min(int i, int j){
	if (i < j) {
		return i;
	} else {
		return j;
	}
}

int max(int i, int j){
	if (i > j) {
		return i;
	} else {
		return j;
	}
}

/*
 * Function that initializes the tic tac toe board  
 * based on whether -s size was called or not
 */
void init_board(board_t board, char **argv, int size){
int i = 1;

	if (size > 3) {
   		i = 3;
	}
	
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			 board[r][c] = *argv[i];
			 i++;
		}
	}
}


/*
 * Function that prints the board accordingly  
 */
void print_board(board_t board, int size){
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
	
		if (board[i][j] == '_') {
			    printf(" %c ", '_');
	    }
		if (board[i][j] == 'O') {
			printf(" %c ", 'O');
	    }
		if (board[i][j] == 'X') {
			printf(" %c ", 'X');
		}

		if (j < (size-1)) {
			printf("|");
		}
	
	}

	printf("\n");
	if (size > 3) {
	  	if (i < (size-1)) {
			printf("---+---+---+---\n");
	  	}
   	 } else {
	 	if (i < (size-1)) {
			printf("---+---+---\n");
	 	}
    }
}
}


/*
 * Function that checks for any wins in  
 * rows, columns or diagonals
 */
int check_winner(board_t board, char player, int size){
int row = 0;
int col = 0;
int diag1 = 0;
int diag2 = 0;

//check rows to find a win
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (board[i][j] == player) {
			row++;
		}
	}
	if (row == size) {
	    return 1;
	}
	row = 0;
}

//check columns for a win
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (board[j][i] == player) {
			col++;
		}
	}
	if (col == size) {
	    return 1;
	}
	col = 0;
}

//check diag1 and diag2 for a win
for (int i = 0; i < size; i++) {
	if (board[i][i] == player) {
		diag1++;
	} else if(board[i][size-1-i] == player) {
		diag2++;
	}
}

if (diag1 == size || diag2 == size) {
	return 1;
}
return 0;	
}


/*
 * Function that checks if there is any empty space left
 */
bool movesLeft(board_t board, int size){
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (board[i][j] == '_') {
		   return true;
		}
	}
}
return false;
}

/*
 * Function that checks if there is a win for X or O in 
 * rows, columns, or diagonals, used for minimax function
 */
int check_board(board_t board, int size){
int row_X = 0;
int row_O = 0;
int col_X = 0;
int col_O = 0;
int diag1_X = 0;
int diag1_O = 0;
int diag2_X = 0;
int diag2_O = 0;


//check rows to find a win
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (board[i][j] == 'X') {
			row_X++;
		} else if (board[i][j] == 'O') {
			row_O++;
		}
		
	}
	if (row_X == size) {
		return +10;
	} else if(row_O == size) {
		return -10;
	}
	row_X = 0;
	row_O = 0;
}


//check the columns for a win
for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (board[j][i] == 'X') {
			col_X++;
		} else if(board[j][i] == 'O') {
			col_O++;
		}
	}
	if (col_X == size) {
		return +10;
	} else if(col_O == size) {
		return -10;
	}
	col_X = 0;
	col_O = 0;
}

//check diagonal1 for win
for (int i = 0; i < size; i++) {
	if (board[i][i] == 'X') {
   	    diag1_X++;
	} else if (board[i][i] == 'O') {
   		diag1_O++;
	}

	if (diag1_X == size) {
		return +10;
    } else if (diag1_O == size) {
	    return -10;
    }
}

//check diagonal2 for win
for (int i = 0; i < size; i++) {
	if (board[i][size-1-i] == 'X') {
        diag2_X++;
    } else if (board[i][size-1-i] == 'O') {
        diag2_O++;
    }

    if (diag2_X == size) {
	   return +10;
    } else if(diag2_O == size) {
	   return -10;
    }
}
return 0;
}

/*
 * Minimax function that recursively calls minimax to
 * find the total score for minimizer and maximizer
 */
int minimax(board_t board, int depth, bool x_max, int size){

//base case X wins or O wins or no moves left
int score = check_board(board, size);
if (score == 10) {
	return score;
}
if (score == -10) {
	return score;
} 
if (movesLeft(board, size) == false) {
	return 0;
}

if (x_max) {
	int total_score = MIN_SCORE;
    for (int i = 0; i < size; i++) {
	    for (int j = 0; j < size; j++) {
		     if (board[i][j] == '_') {
				 board[i][j] = 'X';
			     int curr_score = ((minimax(board, depth+1, !x_max, size)) - depth);
			     total_score = max(total_score, curr_score);
			     board[i][j] = '_';
		     }
	    }
    }
return total_score;	
} else {
    int total_score = MAX_SCORE;
    for (int i = 0; i < size; i++) {
	    for (int j = 0; j < size; j++) {
		     if (board[i][j] == '_') {
			     board[i][j] = 'O';
			     int curr_score = ((minimax(board, depth+1, !x_max, size)) + depth);
			     total_score = min(total_score, curr_score);
			     board[i][j] = '_';
		     }
	    }
    }
return total_score;
}
}

/*
 * Function that finds the most optimal move
 * for O who is the minimizer
 */
void findBestMove(board_t board, int size){
int best_score = MAX_SCORE;
int best_i = -1;
int best_j = -1;
int empty = 0;

/*
 * First, it checks to see if the whole board is empty,
 * and prints 0,0 as the most optimal move if empty
 */
for (int x = 0; x < size; x++) {
	for (int y = 0; y < size; y++) {
		 if (board[x][y] == '_') {
			 empty++;
		 }
	}
}

if (empty == (size*size)) {
	printf("O: %d %d\n", 0, 0);

} else {

for (int i = 0; i < size; i++) {
	 for (int j = 0; j < size; j++) {	
		  if (board[i][j] == '_') {
			  board[i][j] = 'O';
			  int score = minimax(board, 0, true, size);
			  board[i][j] = '_';
	
		  if (score < best_score) {
			  best_i = i;
			  best_j = j;	
              best_score = score;
	      }
	
	      }
	}
}
printf("O: %d %d\n", best_i, best_j);
}
}
/*
 * Function that gets the next best move for the computer
 * when its playing against human, and saves it as a struct Move
 */
struct Move getBestMove(board_t board, int size, char player){
int best_score = MAX_SCORE;
struct Move bestMove;
bestMove.row = -1;
bestMove.col = 1;
int empty = 0;

/*
 * Again, first, it checks to see if the whole board is empty,
 * and prints 0,0 as the most optimal move if empty
 */
for (int x = 0; x < size; x++) {
	for (int y = 0; y < size; y++) {
		 if (board[x][y] == '_') {
			 empty++;
		 }
	}
}

if (empty == (size*size)) {
	bestMove.row = 0;
	bestMove.col = 0;
	return bestMove;

} else {

    for (int i = 0; i < size; i++) {
	    for (int j = 0; j < size; j++) {	
		     if (board[i][j] == '_') {
			     board[i][j] = player;
			     int score = minimax(board, 0, true, size);
			     board[i][j] = '_';
	
		     if (score < best_score) {
			     bestMove.row = i;
		         bestMove.col = j;	
			     best_score = score;
	         }
	
	         }
	    }
    }
return bestMove;	
}
}

int main(int argc, char **argv){
int size = 3;
board_t board;

/*
 * If there is more than 9 args, 
 * the program will find the next optimal move for O
 */
if (argc > 9) {

    if (strcmp(argv[1], "-s") == 0) {
   	    size = atoi(argv[2]);
    }

    init_board(board, argv, size);
    print_board(board, size);
    findBestMove(board, size);
    return 0;


/*
 * If there is less than 4 args, 
 * the computer and user will play a game
 */
} else if (argc < 4) {

    if (strcmp(argv[1], "-s") == 0) {
	    size = atoi(argv[2]);
    }

    char player = 'X'; //since the user gets to go first
    int turn = 0;
    int total_moves = (size*size);
    for (int i = 0; i < size; i++) {
  		for (int j = 0; j < size; j++) {
  		     board[i][j] = '_';
  	    }
    }

    while (turn < total_moves) {
    print_board(board, size);
  	int row;
  	int col;

  	if (check_winner(board, player, size)) {
  		printf("Player %c wins!!!\n", player);
  		return 0;
  	}

	if (player == 'O') {
		printf("Player O turn\n");
		struct Move newBestMove = getBestMove(board, size, player);
		row = newBestMove.row;
		col = newBestMove.col;
		board[row][col] = player;

		//switches player
		if (player == 'O') {
  			player = 'X';
  		} else {
  			player = 'O';
  		}
	} else {
  		printf("Player %c choose your move: ", player);
  		scanf("%d %d", &row, &col);

  		if (row < 0 || col < 0 || row >= size || col >= size) {
  			printf("Out of bounds! Choose your move again: ");
  			scanf("%d %d", &row, &col);
  	    }
  	
  		if (board[row][col] != '_') {
  			printf("That spot is filled, try a different move: ");
  			scanf("%d %d", &row, &col);
  		}
  	
  		board[row][col] = player;

		//switches player
  		if (player == 'X') {
  	   		player = 'O';
  		} else {
  	   		player = 'X';
  		}
  	}
  	turn++;
   }
  
  printf("TIE GAME\n");
  return 0;
  
}
}

