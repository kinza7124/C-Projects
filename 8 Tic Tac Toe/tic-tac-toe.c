#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int difficulty;

typedef struct {
	int player;
	int computer;
	int draw;
} Score;

Score score = {0, 0, 0};

void get_difficulty();
void clear_screen();
void print_board(char board[3][3]);
int checkwin(char board[3][3], char player);
int checkdraw(char board[3][3]);
void playgame();
void playermove(char board[3][3]);
void computermove(char board[3][3]);
void two_player_move(char board[3][3], char player);
int validmove(char board[3][3], int row, int col);


int main(){
	srand(time(NULL));
	int choice;
		get_difficulty();
	do {
 
	playgame();
	
	printf("\nDo you want to play again ? (1 for yes, 2 for no): ");
	scanf(" %d", &choice);
	
	} while(choice == 1);
	
	printf("\nDeveloped by HUSSAIN");
	printf("\nThanks for playing");
	
	return 0;
}

void playgame(){
		char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	};
	
	char current_player = 'X';
	
	if(difficulty == 1 || difficulty == 2) {
		if(rand() % 2 == 0) {
		current_player = 'X';
		} else {
		current_player = 'O';
	      }
	}
			
	while(1){
 	print_board(board); 

	if(difficulty == 3) {
       	    two_player_move(board, current_player);

		if(checkwin(board, current_player)) {
			
			if(current_player == 'X') {
		score.player++;
            print_board(board);
	 printf("\nCONGRATULATIONS Player %c won the game", current_player);
		return;

		} else {

		score.computer++;
		print_board(board);
 		printf("\nCONGRATULATIONS Player %c won the game", current_player);
		 return;
		}
	  }

        if(checkdraw(board)) {
           score.draw++;
           print_board(board);
        printf("\nIt's a draw!");
        return;
    }

	   current_player = (current_player == 'X') ? 'O' : 'X';
	} else {

	if(current_player == 'X'){
		playermove(board);

		 
		if(checkwin(board,'X')){	
		score.player++;		
		print_board(board);
		
		printf("\nCONGRATULATIONS Player X won the game");
			return;
		}
		
	current_player = 'O';
	
	} else {
		computermove(board);

			
		if(checkwin(board,'O')) {
			score.computer++;		
			print_board(board); 
			
			printf("\nCONGRATULATIONS Player O (COMPUTER) won the game");
			return;
		}
		
		current_player = 'X';
	}
	
	if(checkdraw(board)){
		score.draw++;
		print_board(board); 
		
		printf("\nIts a draw!");
		return;
	         }
 	    }
    	}
    }

int validmove(char board[3][3], int row, int col){
	return !(row < 0 || 
	         row > 2 || 
                  col < 0 || 
	         col > 2 || 
	     board[row][col] != ' ');
}


void two_player_move(char board[3][3], char player){
	
	int row, col;

	do{
	printf("\nPlayer %c's turn", player);
	printf("\nEnter row and column (1-3) for %c : ", player);
	scanf(" %d %d", &row, &col);
	
 	row--;
	col--;
 	} while(!validmove(board, row, col));
 
	board[row][col] = player;

}

void playermove(char board[3][3]){
	
	int count = 0, x, y;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == ' '){
				count++;
				 x = i;
				 y = j;
			}
		}
	}
	
	if(count == 1){
		board[x][y] = 'X';
		return;
	}
	
	int row, col;
	do {
		printf("\nPlayer X's turn");
		
		printf("\nEnter row and column (1-3) for X : ");
		scanf(" %d", &row);
		scanf(" %d", &col);
		
		row--;
		col--;
		
	}while(!validmove(board, row, col));
	
	board[row][col] = 'X';
}

void computermove(char board[3][3]){
	
           // 1.IMMEDIATE WIN
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		
		if(board[i][j] == ' '){
			board[i][j] = 'O';
			 if(checkwin(board, 'O')){
			 	return;
			 }
		board[i][j] = ' ';	 
		}
	 }
  }
  

  	// 2.IMMEDIATE BLOCK
  for(int i = 0; i < 3; i++){
  	for(int j = 0; j < 3; j++){
  		
  		if(board[i][j] == ' '){
  			board[i][j] = 'X';
  			if(checkwin(board, 'X')){
  				board[i][j] = 'O';
  				return;
			  }
			board[i][j] = ' ';
		  }
	  }
  }
  
  if(difficulty == 2){
  	

	//3. TAKE CENTER IF POSSIBLE
  	if(board[1][1] == ' '){
  		board[1][1] = 'O';
  		return;
	}
	
        // 4.Take opposite corner if player took one corner
        if(board[0][0] == 'X' && board[2][2] == ' '){
            board[2][2] = 'O';
            return;
        }
        if(board[2][2] == 'X' && board[0][0] == ' '){
            board[0][0] = 'O';
            return;
        }
        if(board[0][2] == 'X' && board[2][0] == ' '){
            board[2][0] = 'O';
            return;
        }
        if(board[2][0] == 'X' && board[0][2] == ' '){
            board[0][2] = 'O';
            return;
        }


	// 5.If player takes opposite corners, take any side to prevent fork
        if((board[0][0] == 'X' && board[2][2] == 'X') ||
           (board[0][2] == 'X' && board[2][0] == 'X')){
            if(board[0][1] == ' '){
                board[0][1] = 'O';
                return;
            }
            if(board[1][0] == ' '){
                board[1][0] = 'O';
                return;
            }
            if(board[1][2] == ' '){
                board[1][2] = 'O';
                return;
            }
            if(board[2][1] == ' '){
                board[2][1] = 'O';
                return;
            }
        }


        // 6.Prioritize remaining corners

	if(board[0][0] == ' '){
		board[0][0] = 'O';
		return;
	}
	
	 if(board[0][2] == ' '){
		board[0][2] = 'O';
		return;
	} 
	
	if(board[2][0] == ' '){
		board[2][0] = 'O';
		return;
	} 
	
	if(board[2][2] == ' '){
		board[2][2] = 'O';
		return;
	}


   
        // 7.Take sides if no corner is free
        if(board[0][1] == ' '){
            board[0][1] = 'O';
            return;
        }
        if(board[1][0] == ' '){
            board[1][0] = 'O';
            return;
        }
        if(board[1][2] == ' '){
            board[1][2] = 'O';
            return;
        }
        if(board[2][1] == ' '){
            board[2][1] = 'O';
            return;
	 } 
}
  //8.TAKE FIRST AVAIABLE MOVE
  for(int i = 0; i < 3; i++){
  	for(int j = 0; j < 3; j++){
  		
  		if(board[i][j] == ' '){
  			board[i][j] = 'O';
  			return;
		  }
	  }
    }
  
}

int checkdraw(char board[3][3]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == ' '){
				return 0;
			}
		}
	}
	
	return 1;
}

int checkwin(char board[3][3], char player){
	
	for(int i = 0; i < 3; i++){
		if(board[i][0] == player && board[i][1] == player && board[i][2] == player){
			return 1;
		}
		
		if(board[0][i] == player && board[1][i] == player && board[2][i] == player){
			return 1;
		}
	}
	
	if((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
	   (board[0][2] == player && board[1][1] == player && board[2][0] == player)){
	   	
	   	return 1;
	   }
	   
	return 0;
}

void print_board(char board[3][3]){
	
	clear_screen();
	if(difficulty == 3) {
   		printf("Score : PLAYER X = %d , PLAYER O = %d , DRAW (O/X)  = %d",
                   score.player, score.computer, score.draw);
	} else {
	printf("Score : PLAYER (X) = %d , COMPUTER (O) = %d , DRAW (O/X) = %d",
	                score.player, score.computer, score.draw);
	}

         
	printf("\n==================\nTIC_TAC_TOE (O/X)\n==================\n");
	
	for(int i = 0; i < 3; i++){
		 printf("\n");
		if(i != 0){
			printf("---+---+---\n");
		}
		for(int j = 0; j < 3; j++){
			if(j != 0){
				printf("|");
			}
			printf(" %c ", board[i][j]);
		}
	}
	printf("\n\n");          
}

void get_difficulty(){
	
		while(1){
		printf("\n==================\nTIC_TAC_TOE (O/X)\n==================\n");
		printf("\nChoose difficulty level: ");
		printf("\n1. Computer (Standard) ");
		printf("\n2. Computer (Impossible To Win) ");
		printf("\n3. Two Player Mode");
		printf("\nEnter your choice : ");
		scanf(" %d", &difficulty);
		
		if(difficulty != 1 && difficulty != 2 && difficulty != 3){
			printf("\nInvalid input. Please enter (1/2/3):\n");
		} else {
			break;
		}
		
	}
	
}

void clear_screen(){
	
	#ifdef _WIN32 
	  system("cls");
	
	#else 
	  system("clear");
	  
	#endif
}
