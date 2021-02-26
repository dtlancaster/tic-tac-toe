
#define ROWS 3
#define COLS 3
#define NAME_SIZE 20

typedef struct {
  
  //Player 1 info.
  //Note player 1 will be Xs.
  char name1[NAME_SIZE];
  int age1;
  
  //Player 2 info
  //Note player 2 will be Os.
  char name2[NAME_SIZE];
  int age2;
  
  //The tictactoe board
  char board[ROWS][COLS];
  
} gameData_t;

