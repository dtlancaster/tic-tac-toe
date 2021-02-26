
#include <stdio.h>
#include "tictactoe.h"

void clearBoard(gameData_t *gameData) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            gameData->board[i][j] = ' ';
        }
    }
}

void getPlayerInfo(gameData_t *gameData) {
    printf("Player 1 enter your name: ");
    scanf("%s", &gameData->name1);
    printf("Player 1 enter your age: ");
    scanf("%d", &gameData->age1);
    printf("\n");
    printf("Player 2 enter your name: ");
    scanf("%s", &gameData->name2);
    printf("Player 2 enter your age: ");
    scanf("%d", &gameData->age2);
}

void printPlayerInfo(gameData_t gameData) {
    printf("Player 1 is %s age %d and will be Xs\n", gameData.name1, gameData.age1);
    printf("Player 2 is %s age %d and will be Os\n", gameData.name2, gameData.age2);
}

void printBoard(gameData_t gameData) {
    printf("    C1  C2  C3\n");
    printf("R1  %c | %c | %c \n", gameData.board[0][0], gameData.board[0][1], gameData.board[0][2]);
    printf("   -----------\n");
    printf("R2  %c | %c | %c \n", gameData.board[1][0], gameData.board[1][1], gameData.board[1][2]);
    printf("   -----------\n");
    printf("R3  %c | %c | %c \n", gameData.board[2][0], gameData.board[2][1], gameData.board[2][2]);     
}

void printTurnHeader(gameData_t gameData, char turn) {
    int i;
    for (i = 0; i < 50; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("-");
    }
    if (turn == 'X') {
        printf(" %s's Turn ", gameData.name1);
    }
    else if (turn == 'O') {
        printf(" %s's Turn ", gameData.name2);
    }
    for (i = 0; i < 20; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("-");
    }
    if (turn == 'X') {
        printf(" You are Xs ");
    }
    else if (turn == 'O') {
        printf(" You are Os ");
    }
    for (i = 0; i < 20; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 50; i++) {
        printf("-");
    }
    printf("\n");
}

void getMove(gameData_t *gameData, char turn) {

    if (turn == 'X') {
        printf("%s, please enter your move in the form RXCY: ", gameData->name1);
    }
    else if (turn == 'O') {
        printf("%s, please enter your move in the form RXCY: ", gameData->name2);
    }
   
    char r, c;
    char move[5];
    scanf("%4s", move);

    while (move[0] != 'r' && move[0] != 'R' || move[2] != 'C' && move[2] != 'c') {
        printf("Results must be in the form RxCy. Try again: ");
        move[0] = '\0';
        scanf("%4s", move);
    }

    while ((move[1] < 49 || move[1] > 51) || (move[3] < 49 || move[3] > 51)) {
        printf("Row and column must be in the range 1 to 3. Try again: ");
        move[0] = '\0';
        scanf("%4s", move);
    }
    
    r = move[1];
    c = move[3];

    while ((gameData->board[r-49][c-49] == 'X') || (gameData->board[r-49][c-49] == 'O')) {
        printf("That space is taken.  Try again: ");
        move[0] = '\0';
        scanf("%4s", move);
        r = move[1];
        c = move[3];
    }

    gameData->board[r-49][c-49] = turn;
}

int checkWin(gameData_t gameData, char turn) {
    int win = 0;
    if (gameData.board[0][0] == turn && gameData.board[0][1] == turn && gameData.board[0][2] == turn) win = 1;
    else if (gameData.board[1][0] == turn && gameData.board[1][1] == turn && gameData.board[1][2] == turn) win = 1;
    else if (gameData.board[2][0] == turn && gameData.board[2][1] == turn && gameData.board[2][2] == turn) win = 1;
    else if (gameData.board[0][0] == turn && gameData.board[1][0] == turn && gameData.board[2][0] == turn) win = 1;
    else if (gameData.board[0][1] == turn && gameData.board[1][1] == turn && gameData.board[2][1] == turn) win = 1;
    else if (gameData.board[0][2] == turn && gameData.board[1][2] == turn && gameData.board[2][2] == turn) win = 1;
    else if (gameData.board[0][0] == turn && gameData.board[1][1] == turn && gameData.board[2][2] == turn) win = 1;
    else if (gameData.board[0][2] == turn && gameData.board[1][1] == turn && gameData.board[2][0] == turn) win = 1;
    return win;   
}

int checkTie(gameData_t gameData) {
    int tie = 0;
    int i, j;
    if ((gameData.board[0][0] == 'X' || gameData.board[0][0] == 'O') 
        && (gameData.board[0][1] == 'X' || gameData.board[0][1] == 'O') 
        && (gameData.board[0][2] == 'X' || gameData.board[0][2] == 'O') 
        && (gameData.board[1][0] == 'X' || gameData.board[1][0] == 'O') 
        && (gameData.board[1][1] == 'X' || gameData.board[1][1] == 'O')
        && (gameData.board[1][2] == 'X' || gameData.board[1][2] == 'O')
        && (gameData.board[2][0] == 'X' || gameData.board[2][0] == 'O')
        && (gameData.board[2][1] == 'X' || gameData.board[2][1] == 'O')
        && (gameData.board[2][2] == 'X' || gameData.board[2][2] == 'O'))
    {
        tie = 1;
    }
    return tie;
}

void runGame() {
  
  gameData_t gameData;
  
  int win = 0;
  int tie = 0;  
  char turn = 'X';
  
  //Set board to all spaces.
  clearBoard(&gameData);
  
  //Get both players name and age
  getPlayerInfo(&gameData);
  
  //Show the player info
  printf("\n");
  printPlayerInfo(gameData);
  printf("\n");
  
  while (!win && !tie) {
    int count = 0;
    
    printTurnHeader(gameData, turn); 
    printBoard(gameData);
    getMove(&gameData, turn);    
    
    //Check for win
    win = checkWin(gameData, turn);        
    if (win == 1) {
      printf("--------------------------------------------------\n");      
      if (turn == 'X') {        
        printf("---------- %s WINS! --------------------\n", gameData.name1);
      } else {        
        printf("---------- %s WINS! --------------------\n", gameData.name2);
      }
      printf("--------------------------------------------------\n");      
      printBoard(gameData);
      printf("\n");
    } else {
      tie = checkTie(gameData);        
      if (tie == 1) {
        printf("--------------------------------------------------\n");      
        printf("---------- TIE GAME! --------------------\n");
        printf("--------------------------------------------------\n");      
        printBoard(gameData);
      }
    }
    
    //Toggle turn so other player goes next.
    if (turn == 'X') turn = 'O';
    else turn = 'X';
  }
}






