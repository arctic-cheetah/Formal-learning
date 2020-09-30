// Assignment 1 20T1 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by JEREMY MANG (z5312813)
// on 16/03/2020
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.
// Version 1.0.2 (2020-03-08): Fix second line of header comment to say minesweeper.c

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

// Add any extra #defines here.

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);


// Place your function prototyes here.
int detect_row(int firstInput, int secondInput, int minefield[SIZE][SIZE]);
int detect_col(int firstInput, int secondInput, int minefield[SIZE][SIZE]);
int detect_square(int firstInput, int secondInput, int thirdInput, int fourthInput, int minefield[SIZE][SIZE]);
int reveal_square(int firstInput, int secondInput, int thirdInput, int minefield[SIZE][SIZE], int *gameWinp, int *gameRoundp);
int print_gameplay_minefield (int gameOver, int minefield[SIZE][SIZE], int mineCountArray3x3[SIZE][SIZE]);
int reveal_radial(int firstInput, int secondInput, int thirdInput, int minefield[SIZE][SIZE], int *gameWinp, int *gameRoundp, int mineCountArray3x3[SIZE][SIZE]);
int shift_mine_round1 (int minefield[SIZE][SIZE], int *gameRoundp);

//These functions support the command functions above:
int mine_count( int minefield[SIZE][SIZE], int mineCountArray3x3[SIZE][SIZE]);
int win_game(int minefield[SIZE][SIZE], int *gameWinp);
int boundary_check_3x3 (int secondInput, int thirdInput, int boundaryArray[]);


int main(void) {

	int mineCountArray3x3[SIZE][SIZE] = {0}; // This stores another map the number of mines around the minefield map
    int mines = 0;
    int pointMine1, pointMine2; // This sets the position of the mines  

    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");
    scanf("%d", &mines);

    //This scans number of pairs of mines.

    printf("Enter pairs:\n");

    int i = 0;
    while ( i < mines) {
      scanf("%d %d", &pointMine1, &pointMine2);  
        if((0 <= pointMine1) && (pointMine1 < SIZE) && (0 <= pointMine2) && (pointMine2 < SIZE)) {      
            minefield[pointMine1][pointMine2] = HIDDEN_MINE;
        }
      i++;
    }
    

    //This scans in pairs of mines and places them on the grid.
    printf("Game Started\n");
    print_debug_minefield(minefield);
	mine_count(minefield, mineCountArray3x3);	
    int gameOver = 0;
	int gameWin = 0;
	int *gameWinp = &gameWin;
	int gameMode = 6; 
	int gameRound = 1;
	int *gameRoundp = &gameRound;
	int hintCount = 0;
	int input1 = 0;

    while( gameOver != 1 && gameWin != 1 && scanf("%d", &input1) == 1){
     
    int input2 = 0; //Obtains input from the user
    int input3 = 0;       
    int input4 = 0;
    
    if(input1 == DEBUG_MODE){
        printf("Debug mode activated\n");
        print_debug_minefield(minefield);//
        gameMode = DEBUG_MODE;
    }
    else if (input1 == GAMEPLAY_MODE){
        printf("Gameplay mode activated\n");
		print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
        gameMode = GAMEPLAY_MODE;
    }    
    else{
        if(hintCount < 3){

        //Stage 1 commands: detect row and col
		
            if (input1 == DETECT_ROW){
                scanf("%d", &input2);
                detect_row(input1, input2, minefield);       
                hintCount++;
				if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }
            else if (input1 == DETECT_COL){
                scanf("%d", &input2);
                detect_col(input1, input2, minefield);
                hintCount++;
                if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }

            //Stage 2 commands: detects # mines in a square
            else if (input1 == DETECT_SQUARE){
                scanf("%d %d %d", &input2, &input3, &input4);
                detect_square(input1, input2, input3, input4, minefield);
                hintCount++;
                if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }
            else if (input1 == REVEAL_SQUARE){
                scanf("%d %d", &input2, &input3);
				// this condition checks if the player has stepped on a mine.
		        if(minefield[input2][input3] == HIDDEN_MINE && gameRound != 1){ 
			        gameOver = 1;
			        printf("Game over\n");
			        if(gameMode == DEBUG_MODE){
                		print_debug_minefield(minefield);
					}
					else if (gameMode == GAMEPLAY_MODE){
						print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
					}
			        return 0;
			
		        }
				// This section shifts the grid down if the player steps on a mine on the first turn
		        else{                   
					if(minefield[input2][input3] == HIDDEN_MINE && gameRound == 1){
						shift_mine_round1 (minefield, gameRoundp);				
						reveal_square(input1, input2, input3, minefield, gameWinp, gameRoundp);
						print_debug_minefield(minefield);
						mine_count(minefield, mineCountArray3x3);
					}
					
					else{
		            	reveal_square(input1, input2, input3, minefield, gameWinp, gameRoundp);
		            	if(gameMode == DEBUG_MODE){
		            		print_debug_minefield(minefield);
						}
						else if (gameMode == GAMEPLAY_MODE){
							print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
						}
					}
		        }
            }
			else if (input1 == REVEAL_RADIAL){
				scanf("%d %d", &input2, &input3);
				//this condition checks if the player stepped on a mine	
				if(minefield[input2][input3] == HIDDEN_MINE && gameRound != 1){							
			        gameOver = 1;
			        printf("Game over\n");
			        if(gameMode == DEBUG_MODE){
                		print_debug_minefield(minefield);
					}
					else if (gameMode == GAMEPLAY_MODE){
						print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
					}
			        return 0;
		        }
				else{
					// This section shifts the grid down if the player steps on a mine on the first turn
					if(minefield[input2][input3] == HIDDEN_MINE && gameRound == 1){
						shift_mine_round1 (minefield, gameRoundp);				
						reveal_radial(input1, input2, input3, minefield, gameWinp, gameRoundp, mineCountArray3x3);
						print_debug_minefield(minefield);
						mine_count(minefield, mineCountArray3x3);
					}
					else{
						reveal_radial(input1, input2, input3, minefield, gameWinp, gameRoundp, mineCountArray3x3);
						if(gameMode == DEBUG_MODE){
				    		print_debug_minefield(minefield);
						}
						else if (gameMode == GAMEPLAY_MODE){
							print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
						}
					}
				}
			} 
        }
        
        else { 
 
// --------------------------------------------------This section prevents the player from getting more hints by showing help already used
            if (input1 == DETECT_ROW){
                scanf("%d", &input2);
                printf("Help already used\n");
                if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }
            else if (input1 == DETECT_COL){
                scanf("%d", &input2);
                printf("Help already used\n");
                if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }
            else if (input1 == DETECT_SQUARE){ 
                scanf("%d %d %d", &input2, &input3, &input4);
                printf("Help already used\n");
                if(gameMode == DEBUG_MODE){
                	print_debug_minefield(minefield);
				}
				else if (gameMode == GAMEPLAY_MODE){
					print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
				}
            }
            
			//These are the only permissible input after 3 hints are given           
             else if (input1 == REVEAL_SQUARE){
                scanf("%d %d", &input2, &input3);
				// this condition checks if the player stepped on a mine	
		        if(minefield[input2][input3] == HIDDEN_MINE && gameRound != 1){							
			        gameOver = 1;
			        printf("Game over\n");
			        if(gameMode == DEBUG_MODE){
                		print_debug_minefield(minefield);
					}
					else if (gameMode == GAMEPLAY_MODE){
						print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
					}
			        return 0;
			
		        }
		        else{
					if(minefield[input2][input3] == HIDDEN_MINE && gameRound == 1){
						shift_mine_round1 (minefield, gameRoundp);				
						reveal_square(input1, input2, input3, minefield, gameWinp, gameRoundp);
						print_debug_minefield(minefield);
						mine_count(minefield, mineCountArray3x3);
					}
					
					else{
		            	reveal_square(input1, input2, input3, minefield, gameWinp, gameRoundp);
		            	if(gameMode == DEBUG_MODE){
		            		print_debug_minefield(minefield);
						}
						else if (gameMode == GAMEPLAY_MODE){
							print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
						}
					}
		        }
	        }
			else if (input1 == REVEAL_RADIAL){
				scanf("%d %d", &input2, &input3);
				// This condition checks if the player stepped on a mine	
				if(minefield[input2][input3] == HIDDEN_MINE && gameRound != 1){							
			        gameOver = 1;                                              
			        printf("Game over\n");
			        if(gameMode == DEBUG_MODE){
                		print_debug_minefield(minefield);
					}
					else if (gameMode == GAMEPLAY_MODE){
						print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
					}
			        return 0;
			
		        }
				//This section shifts the grid down if the player steps on a mine on the first turn
				else{
					if(minefield[input2][input3] == HIDDEN_MINE && gameRound == 1){
						shift_mine_round1 (minefield, gameRoundp);				
						reveal_radial(input1, input2, input3, minefield, gameWinp, gameRoundp, mineCountArray3x3);
						print_debug_minefield(minefield);
						mine_count(minefield, mineCountArray3x3);
					}
					else{
						reveal_radial(input1, input2, input3, minefield, gameWinp, gameRoundp, mineCountArray3x3);
						if(gameMode == DEBUG_MODE){
				    		print_debug_minefield(minefield);
						}
						else if (gameMode == GAMEPLAY_MODE){
							print_gameplay_minefield (gameOver, minefield, mineCountArray3x3);
						}
					}
				}
			}       
        }
    }
       
        
    gameRound++;
        
    }
    
    
    return 0;
}








//----------------------------------------------------------------------------------------- FUNCTIONS EXIST DOWN HERE







// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    
}

//-----------------------------------------------------------------Stage 1 Functions


//Detects mines in a row
int detect_row(int firstInput, int secondInput, int minefield[SIZE][SIZE]) {

    int i = 0;
    int numberOfMines = 0;
    while (i < SIZE){
    	if (minefield[secondInput][i] == HIDDEN_MINE){
            numberOfMines++;
        }
	    i++;
    }
    
    printf("There are %d mine(s) in row %d\n", numberOfMines, secondInput);
    
    return 0;

}


//detects mines in a column 
int detect_col(int firstInput, int secondInput, int minefield[SIZE][SIZE]) {

    int i = 0;
    int numberOfMines = 0;
    while (i < SIZE){

      if (minefield[i][secondInput] == HIDDEN_MINE){
        numberOfMines++;
      }
      i++;
    }
    
    printf("There are %d mine(s) in column %d\n", numberOfMines, secondInput);
    return 0;
}


//------------------------------------------------------------------STAGE 2 Functions


//Detects mines in a square
int detect_square(int firstInput, int secondInput, int thirdInput, int fourthInput, int minefield[SIZE][SIZE]) {


    int rowLoopMax = 0;
    int colLoopMax = 0;

	int rowLoopMin = 0;
	int colLoopMin = 0;
	
    
    //This section accounts for inputs near the array boundaries
    if (secondInput == 0) {
		if (thirdInput == 0){
			rowLoopMin = 0;
			colLoopMin = 0;
			rowLoopMax = 1;
			colLoopMax = 1;
		} 
		else {
			if(thirdInput == SIZE - 1){
				rowLoopMin = 0;
				colLoopMin = SIZE - 2;
				rowLoopMax = 1;
				colLoopMax = SIZE - 1;
			}
			else{
				rowLoopMin = 0;
				colLoopMin = thirdInput - 1;
				rowLoopMax = 1;
				colLoopMax = thirdInput + 1;
			}
		}
	}
	else {
		if (secondInput == SIZE - 1){
			if(thirdInput == 0){
				rowLoopMin = SIZE - 2;
				colLoopMin = 0;
				rowLoopMax = SIZE - 1;
				colLoopMax = 1;
			}
			else {
				if (thirdInput == SIZE - 1){
					rowLoopMin = SIZE - 2;
					colLoopMin = SIZE - 2;
					rowLoopMax = SIZE - 1;
					colLoopMax = SIZE - 1;
				}
				else{
					rowLoopMin = SIZE - 2;
					colLoopMin = thirdInput - 1;
					rowLoopMax = SIZE - 1;
					colLoopMax = thirdInput + 1;					
				}
			}					
		}


		else{
			if (thirdInput == 0){
				rowLoopMin = secondInput - 1;
				colLoopMin = 0;
				rowLoopMax = secondInput + 1;
				colLoopMax = 1;
			}

			else{
				if (thirdInput == SIZE - 1){
					rowLoopMin = secondInput - 1;
					colLoopMin = SIZE - 2;
					rowLoopMax = secondInput + 1;
					colLoopMax = SIZE - 1; 
				}
				else{
					rowLoopMin = secondInput - 1;
					colLoopMin = thirdInput - 1;
					rowLoopMax = secondInput + 1;
					colLoopMax = thirdInput + 1;
				}
			}
		}
	}
 	

// loop through row, then column---> This counts the # of mines in a 3x3 area
    int numberOfMines = 0;
    int i = rowLoopMin;
        while (i <= rowLoopMax ){
        int j = colLoopMin;
            while(j <= colLoopMax ){
            	if (minefield[i][j] == HIDDEN_MINE){
					numberOfMines++;
				
                }
            j++;
            }
        i++;
        }		
            
    printf("There are %d mine(s) in the square centered at row %d, column %d of size %d\n", 
    numberOfMines, secondInput, thirdInput, fourthInput);

    return 0;
}


//Reveals mines in a square

int reveal_square(int firstInput, int secondInput, int thirdInput, int minefield[SIZE][SIZE], int *gameWinp, int *gameRoundp) {
    

    int rowLoopMax = 0;
    int colLoopMax = 0;

	int rowLoopMin = 0;
	int colLoopMin = 0;

    
    //This section accounts for inputs near the array boundaries
    if (secondInput == 0) {
		if (thirdInput == 0){
			rowLoopMin = 0;
			colLoopMin = 0;
			rowLoopMax = 1;
			colLoopMax = 1;
		} 
		else {
			if(thirdInput == SIZE - 1){
				rowLoopMin = 0;
				colLoopMin = SIZE - 2;
				rowLoopMax = 1;
				colLoopMax = SIZE - 1;
			}
			else{
				rowLoopMin = 0;
				colLoopMin = thirdInput - 1;
				rowLoopMax = 1;
				colLoopMax = thirdInput + 1;
			}
		}
	}
	else {
		if (secondInput == SIZE - 1){
			if(thirdInput == 0){
				rowLoopMin = SIZE - 2;
				colLoopMin = 0;
				rowLoopMax = SIZE - 1;
				colLoopMax = 1;
			}
			else {
				if (thirdInput == SIZE - 1){
					rowLoopMin = SIZE - 2;
					colLoopMin = SIZE - 2;
					rowLoopMax = SIZE - 1;
					colLoopMax = SIZE - 1;
				}
				else{
					rowLoopMin = SIZE - 2;
					colLoopMin = thirdInput - 1;
					rowLoopMax = SIZE - 1;
					colLoopMax = thirdInput + 1;					
				}
			}					
		}


		else{
			if (thirdInput == 0){
				rowLoopMin = secondInput - 1;
				colLoopMin = 0;
				rowLoopMax = secondInput + 1;
				colLoopMax = 1;
			}

			else{
				if (thirdInput == SIZE - 1){
					rowLoopMin = secondInput - 1;
					colLoopMin = SIZE - 2;
					rowLoopMax = secondInput + 1;
					colLoopMax = SIZE - 1; 
				}
				else{
					rowLoopMin = secondInput - 1;
					colLoopMin = thirdInput - 1;
					rowLoopMax = secondInput + 1;
					colLoopMax = thirdInput + 1;
				}
			
			}
        }
	}
 	

// loop through row, then column
    int numberOfMines = 0;
    int i = rowLoopMin;
        while (i <= rowLoopMax ){
        int j = colLoopMin;
            while(j <= colLoopMax ){
               if (minefield[i][j] == HIDDEN_MINE){
                 numberOfMines++;
               }
               j++;
            }
          i++;
        }
        
    //Changes coordinate to Visible safe
    i = rowLoopMin;
    if (numberOfMines >= 1){
        	minefield[secondInput][thirdInput] = VISIBLE_SAFE; // This section reveals the square
	}
    else if (numberOfMines == 0){
        while (i <= rowLoopMax ){
        int j = colLoopMin;
            while(j <= colLoopMax ){
            	minefield[i][j] = VISIBLE_SAFE; // This section reveals the square
           		j++;
            }
          i++;
        }
    }
    

    win_game(minefield, gameWinp);

    return 0;
}



//This function determines if the player has uncovered all the mines
int win_game(int minefield[SIZE][SIZE], int *gameWinp) {

	int hidSafeCounter = 0;

	// This code counts all of coordinates which are HIDDEN_SAFE or equal to 1. Once hidSafeCounter == 0, the game is won! 
	int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
			int gridCounter = 0;
            gridCounter = minefield[i][j];
			
			if(gridCounter == HIDDEN_SAFE){
				hidSafeCounter++;
			}
            j++;
        }
        i++;
	}
	
	if (hidSafeCounter == 0){
		*gameWinp = 1;
		printf("Game Won!\n");
	}
		
	return 0;	
	
}

//---------------------------------------------------------------------Stage 3: Formatted Printing && debug mode


//Prints out formatted printing (gameplay mode)
int print_gameplay_minefield (int gameOver, int minefield[SIZE][SIZE], int mineCountArray3x3[SIZE][SIZE]){


    if(gameOver == 0){
        printf("..\n");
        printf("\\/\n");
    }
    if(gameOver == 1){
        printf("xx\n");
        printf("/\\\n");
    }
    
    printf("    00 01 02 03 04 05 06 07 \n");
    printf("   -------------------------\n"); //Top line
    

    int i = 0; //Prints out grid
    while (i < 8){
		printf("0%d", i);
		printf(" |");

		int j = 0;
		while(j < 8){
			
			if(minefield[i][j] == HIDDEN_MINE || minefield[i][j] == HIDDEN_SAFE){
				if(mineCountArray3x3[i][j] == 9 && gameOver == 1){
					printf("()");
				}
				else{
					printf("##");
				}

			}
			else{
				if(mineCountArray3x3[i][j] == VISIBLE_SAFE){
					printf("  ");
				}
				else if(0 < mineCountArray3x3[i][j] && mineCountArray3x3[i][j] < 9){  // We may put the # of mines here
					printf("0%d", mineCountArray3x3[i][j]);				
				}

			}

			if(j < 7){
				printf(" "); // this prints the spaces between  ##
			}
			j++;
		}
		
		printf("|\n");
			
		i++;
	}
	printf("   -------------------------\n");// Bottom line

    return 0;
}




//This stores the number of mines in a coordinates of the map (minefield) as an array

int mine_count( int minefield[SIZE][SIZE], int mineCountArray3x3[SIZE][SIZE]) {


	for(int corRow = 0; corRow < SIZE; corRow++){

		for(int corCol = 0; corCol < SIZE; corCol++){

		int rowLoopMax = 0;
		int colLoopMax = 0;

		int rowLoopMin = 0;
		int colLoopMin = 0;
		
		//This section accounts counts for mines near the array boundaries
		if (corRow == 0) {
			if (corCol == 0){
				rowLoopMin = 0;
				colLoopMin = 0;
				rowLoopMax = 1;
				colLoopMax = 1;
			} 
			else {
				if(corCol == SIZE - 1){
					rowLoopMin = 0;
					colLoopMin = SIZE - 2;
					rowLoopMax = 1;
					colLoopMax = SIZE - 1;
				}
				else{
					rowLoopMin = 0;
					colLoopMin = corCol - 1;
					rowLoopMax = 1;
					colLoopMax = corCol + 1;
				}
			}
		}
		else {
			if (corRow == SIZE - 1){
				if(corCol == 0){
					rowLoopMin = SIZE - 2;
					colLoopMin = 0;
					rowLoopMax = SIZE - 1;
					colLoopMax = 1;
				}
				else {
					if (corCol == SIZE - 1){
						rowLoopMin = SIZE - 2;
						colLoopMin = SIZE - 2;
						rowLoopMax = SIZE - 1;
						colLoopMax = SIZE - 1;
					}
					else{
						rowLoopMin = SIZE - 2;
						colLoopMin = corCol - 1;
						rowLoopMax = SIZE - 1;
						colLoopMax = corCol + 1;					
					}
				}					
			}


			else{
				if (corCol == 0){
					rowLoopMin = corRow - 1;
					colLoopMin = 0;
					rowLoopMax = corRow + 1;
					colLoopMax = 1;
				}

				else{
					if (corCol == SIZE - 1){
						rowLoopMin = corRow - 1;
						colLoopMin = SIZE - 2;
						rowLoopMax = corRow + 1;
						colLoopMax = SIZE - 1; 
					}
					else{
						rowLoopMin = corRow - 1;
						colLoopMin = corCol - 1;
						rowLoopMax = corRow + 1;
						colLoopMax = corCol + 1;
					}
				}
			}
		}
	 	

	// loop through row, then column---> This counts the # of mines in a 3x3 area
			if(minefield[corRow][corCol] == HIDDEN_MINE){
				mineCountArray3x3[corRow][corCol] = 9;
			}		
			else{
			int numberOfMines = 0;
			int i = rowLoopMin;
				while (i <= rowLoopMax ){
				int j = colLoopMin;
				    while(j <= colLoopMax ){
				    	if (minefield[i][j] == HIDDEN_MINE){
							numberOfMines++;
						
				        }
				    j++;
				    }
				i++;
				}
				
			mineCountArray3x3[corRow][corCol] = numberOfMines; // This stores the # of mines around that coordinate
        	} 
		}
	}
	
	//This section prints out the each square's value if there are adjacent mines in the memory array
/*	
	for (int k = 0; k < SIZE; k++ ){
	
	for(int l = 0; l < SIZE; l++ ){
		printf("%d ", mineCountArray3x3[k][l]);		
	}	
	printf("\n");
	}
	printf("Completed printing 2D array\n\n");
	
*/

    return 0;
}



//----------------------------------------------------------------------------------STAGE 4: Reveal Radial 


int reveal_radial(int firstInput, int secondInput, int thirdInput, int minefield[SIZE][SIZE], int *gameWinp, int *gameRoundp, int mineCountArray3x3[SIZE][SIZE]) {
    
    
    int bArray[4]; // This array is used to set up the boundaries to check for mines
    
    boundary_check_3x3(secondInput, thirdInput, bArray);
 	

// Count number of mines in a 3x3 area for the selected coordinates
    int numberOfMines = 0;
    int i = bArray[1];
        while (i <= bArray[0] ){
        int j = bArray[3];
            while(j <= bArray[2] ){
               if (minefield[i][j] == HIDDEN_MINE){
                 numberOfMines++;
               }
               j++;
            }
          i++;
        }
        
    //Changes coordinate to Visible safe
    i = bArray[1];
    if (numberOfMines >= 1){
        	minefield[secondInput][thirdInput] = VISIBLE_SAFE; // This section reveals an individual square
    }
    else if (numberOfMines == 0){//This section will send the points of the star outwards

		// This part reveals a 3x3 square
        while (i <= bArray[0] ){
        int j = bArray[3];
            while(j <= bArray[2] ){
                minefield[i][j] = VISIBLE_SAFE;
               
           		j++;
            }
          i++;
        }
		// This section declares variables based on the angle radians used for radial reveal
		
		
		int zero = thirdInput + 0;
        
		int Pi_d_4_one = secondInput - 0; //eg Pi/4 = Pi_d_4_one
		int Pi_d_4_two = thirdInput + 0; // suffix 'two' denotes to the axis it is moving. In this case two = columns.
        
		int Pi_d_2 = secondInput - 0; //eg Pi/2 = Pi_d_2
        
		int threePi_d_4_one = secondInput - 0; //eg 3Pi/2 = threePi_d_2
		int threePi_d_4_two = thirdInput - 0;
        
		int Pi = thirdInput - 0;
        
		int fivePi_d_4_one = secondInput + 0; //eg 5Pi/4 == fivePi_d_4
		int fivePi_d_4_two = thirdInput - 0;
        
		int threePi_d_2 = secondInput + 0;
        
		int sevenPi_d_4_one = secondInput + 0;
		int sevenPi_d_4_two = thirdInput + 0;
		
		
		//These loops send out a horizontal and vertical line to reveal squares. 
		//But it will also check the number of mines around one node to determine if it will cease moving

		int keyVar = 1;

		while(zero <= SIZE - 1 && (minefield[secondInput][zero] != HIDDEN_MINE && keyVar == 1)){
		
			if(mineCountArray3x3[secondInput][zero] == 0){
				minefield[secondInput][zero] = VISIBLE_SAFE;		
				zero++;
			}
			else{
				minefield[secondInput][zero] = VISIBLE_SAFE;
				keyVar = 0;	
			}
		}

		keyVar = 1;
		while(Pi_d_2 >= 0 && (minefield[Pi_d_2][thirdInput] != HIDDEN_MINE && keyVar == 1)) {
			if(mineCountArray3x3[Pi_d_2][thirdInput] == 0){			
				minefield[Pi_d_2][thirdInput] = VISIBLE_SAFE;		
				Pi_d_2--;
			}
			else{
				minefield[Pi_d_2][thirdInput] = VISIBLE_SAFE;
				keyVar = 0;	
			}
		}

		
		keyVar = 1;
		while(Pi >= 0 && (minefield[secondInput][Pi] != HIDDEN_MINE && keyVar == 1)) {
			if(mineCountArray3x3[secondInput][Pi] == 0){	    	
				minefield[secondInput][Pi] = VISIBLE_SAFE;		
				Pi--;
			}
			else{
				minefield[secondInput][Pi] = VISIBLE_SAFE;
				keyVar = 0;
			}
					
		}

		keyVar = 1;
		while(threePi_d_2 <= SIZE - 1 && (minefield[threePi_d_2][thirdInput] != HIDDEN_MINE && keyVar == 1)) {	
		    if(mineCountArray3x3[threePi_d_2][thirdInput] == 0){
				minefield[threePi_d_2][thirdInput] = VISIBLE_SAFE;		
				threePi_d_2++;
			}
			else{
				minefield[threePi_d_2][thirdInput] = VISIBLE_SAFE;
				keyVar = 0;
			}			
			
		}

		//These loops send out diagonal lines to reveal squares
		keyVar = 1;
		while(Pi_d_4_one >= 0 && Pi_d_4_two <= SIZE - 1 && (minefield[Pi_d_4_one][Pi_d_4_two] != HIDDEN_MINE && keyVar == 1)){
			if(mineCountArray3x3[Pi_d_4_one][Pi_d_4_two] == 0){
			    minefield[Pi_d_4_one][Pi_d_4_two] = VISIBLE_SAFE;
			    Pi_d_4_two++;		
			    Pi_d_4_one--;
			}
			else{
				minefield[Pi_d_4_one][Pi_d_4_two] = VISIBLE_SAFE;
				keyVar = 0;
			}

			
		}	

		keyVar = 1;
		while(threePi_d_4_one >= 0 && threePi_d_4_two >= 0 && (minefield[threePi_d_4_one][threePi_d_4_two] != HIDDEN_MINE && keyVar == 1)){
			if(mineCountArray3x3[threePi_d_4_one][threePi_d_4_two] == 0){
				minefield[threePi_d_4_one][threePi_d_4_two] = VISIBLE_SAFE;
				threePi_d_4_two--;		
				threePi_d_4_one--;
			}
			else{
				minefield[threePi_d_4_one][threePi_d_4_two] = VISIBLE_SAFE;
				keyVar = 0;
			}
		}

		keyVar = 1;
		while(fivePi_d_4_one <= SIZE - 1 && fivePi_d_4_two >= 0 && (minefield[fivePi_d_4_one][fivePi_d_4_two] != HIDDEN_MINE && keyVar == 1)){
			if(mineCountArray3x3[fivePi_d_4_one][fivePi_d_4_two] == 0){
				minefield[fivePi_d_4_one][fivePi_d_4_two] = VISIBLE_SAFE;
				fivePi_d_4_two--;			
				fivePi_d_4_one++;
			}
			else{
				minefield[fivePi_d_4_one][fivePi_d_4_two] = VISIBLE_SAFE;			
				keyVar = 0;			
			}
		}
		
		keyVar = 1;
		while(sevenPi_d_4_one <= SIZE - 1 && sevenPi_d_4_two <= SIZE - 1 && (minefield[sevenPi_d_4_one][sevenPi_d_4_two] != HIDDEN_MINE && keyVar == 1)){

			if(mineCountArray3x3[sevenPi_d_4_one][sevenPi_d_4_two] == 0 ){
				minefield[sevenPi_d_4_one][sevenPi_d_4_two] = VISIBLE_SAFE;
				sevenPi_d_4_two++;			
				sevenPi_d_4_one++;
			}
			else{
				minefield[sevenPi_d_4_one][sevenPi_d_4_two] = VISIBLE_SAFE;
				keyVar = 0;
			}
        
    	}
	}
    
	
    win_game(minefield, gameWinp);

    return 0;
}

//------This function shifts a mine down if the user selected a mine on the first round

int shift_mine_round1 (int minefield[SIZE][SIZE], int *gameRoundp){

	int tempArray[8] = {0};	
	
	for(int k = 0; k <= SIZE - 1 ; k++){
		tempArray[k] = minefield[SIZE - 1][k];
		//printf("%d\n", tempArray[k]);
	}
	

	//Shifts row 0 to 6, one row down
	for (int i = SIZE - 1; i > 0; i--){
		for(int j = SIZE - 1; j >= 0; j--){
			minefield[i][j] = minefield[i - 1][j];
		}
		
	}

	for(int k = 0; k <= SIZE - 1 ; k++){
		minefield[0][k] = tempArray[k];
	}

	return 0;
}



//----This function sets up the 3x3 area boundary to check for mines

int boundary_check_3x3 (int secondInput, int thirdInput, int boundaryArray[]){

    
    if(secondInput > SIZE - 1){
        secondInput = SIZE - 1;
    }
    
    else if(secondInput < 0){
        secondInput = 0;
    }

    
    if(thirdInput > SIZE - 1){
        thirdInput = SIZE - 1;
    }
    else if(thirdInput < 0){
        thirdInput = 0;
    }
    

    int rowLoopMax = 0;
    int colLoopMax = 0;

	int rowLoopMin = 0;
	int colLoopMin = 0;

    if (secondInput == 0) {
		if (thirdInput == 0){
			rowLoopMin = 0;
			colLoopMin = 0;
			rowLoopMax = 1;
			colLoopMax = 1;
		} 
		else {
			if(thirdInput == SIZE - 1){
				rowLoopMin = 0;
				colLoopMin = SIZE - 2;
				rowLoopMax = 1;
				colLoopMax = SIZE - 1;
			}
			else{
				rowLoopMin = 0;
				colLoopMin = thirdInput - 1;
				rowLoopMax = 1;
				colLoopMax = thirdInput + 1;
			}
		}
	}
	else {
		if (secondInput == SIZE - 1){
			if(thirdInput == 0){
				rowLoopMin = SIZE - 2;
				colLoopMin = 0;
				rowLoopMax = SIZE - 1;
				colLoopMax = 1;
			}
			else {
				if (thirdInput == SIZE - 1){
					rowLoopMin = SIZE - 2;
					colLoopMin = SIZE - 2;
					rowLoopMax = SIZE - 1;
					colLoopMax = SIZE - 1;
				}
				else{
					rowLoopMin = SIZE - 2;
					colLoopMin = thirdInput - 1;
					rowLoopMax = SIZE - 1;
					colLoopMax = thirdInput + 1;					
				}
			}					
		}


		else{
			if (thirdInput == 0){
				rowLoopMin = secondInput - 1;
				colLoopMin = 0;
				rowLoopMax = secondInput + 1;
				colLoopMax = 1;
			}

			else{
				if (thirdInput == SIZE - 1){
					rowLoopMin = secondInput - 1;
					colLoopMin = SIZE - 2;
					rowLoopMax = secondInput + 1;
					colLoopMax = SIZE - 1; 
				}
				else{
					rowLoopMin = secondInput - 1;
					colLoopMin = thirdInput - 1;
					rowLoopMax = secondInput + 1;
					colLoopMax = thirdInput + 1;
				}
			}
        }
	}
 	
    boundaryArray[0] = rowLoopMax;
 	boundaryArray[1] = rowLoopMin;
 	boundaryArray[2] = colLoopMax;
 	boundaryArray[3] = colLoopMin;
    
    return 0;
}










