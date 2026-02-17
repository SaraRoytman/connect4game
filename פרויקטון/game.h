#ifndef GAME_H
#define GAME_H

#define ROWS 6
#define COLS 7

// הגדרת המבנה
typedef struct {
    int p1Wins;
    int p2Wins;
    int computerWins;
    int draws;
} GameStats;

// הצהרות על מצבי המשחק
void playPvP(int isAdvanced, GameStats* stats);
void playPvC(int isAdvanced, GameStats* stats);

// הלוגיקה של המשחק
void initBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int getPlayerInput(int player);
int placePiece(char board[ROWS][COLS], int col, char symbol);
int checkHorizontalWin(char board[ROWS][COLS], int row, int col, char symbol);
int checkVerticalWin(char board[ROWS][COLS], int row, int col, char symbol);
int checkDiagonalWin(char board[ROWS][COLS], int row, int col, char symbol);

#endif
