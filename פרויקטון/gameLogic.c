#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "game.h" 

//מנקה את הלוח בתחילת כל משחק
void initBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = ' ';
}
//מדפיס את הצורה של הלוח
void printBoard(char board[ROWS][COLS]) {
    printf("\n 1 2 3 4 5 6 7 \n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) printf("%c|", board[i][j]);
        printf("\n");
    }
    printf("---------------\n");
}
//מקבל את מספר העמודה שהשחקן בוחר
int getPlayerInput(int player) {
    int col;
    printf("Player %d, enter column (1-7): ", player);
    scanf("%d", &col);
    while (col < 1 || col > 7) {
        printf("Invalid! Enter 1-7: ");
        scanf("%d", &col);
    }
    return col;
}
//ממקם את האיקס או העיגול במקום שנבחר
int placePiece(char board[ROWS][COLS], int col, char symbol) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col - 1] == ' ') {
            board[i][col - 1] = symbol;
            return i;
        }
    }
    return -1;
}
//בדיקה אם יש 4 בשורה
int checkHorizontalWin(char board[ROWS][COLS], int row, int col, char symbol) {
    int count = 0;
    int colIdx = col - 1;

    for (int j = 0; j < COLS; j++) {
        if (board[row][j] == symbol) {
            count++;
            if (count >= 4) return 1;
        }
        else {
            count = 0;
        }
    }
    return 0;
}
//בדיקה אם יש 4 בעמודה
int checkVerticalWin(char board[ROWS][COLS], int row, int col, char symbol) {
    int count = 0;
    for (int i = row; i < ROWS; i++) {
        if (board[i][col - 1] == symbol) count++;
        else break;
    }
    return (count >= 4);
}
//בדיקה אם יש 4 באלכסון
int checkDiagonalWin(char board[ROWS][COLS], int row, int col, char symbol) {
    int count, r, c;
    int colIdx = col - 1;

    // אלכסון ראשי (\)
    count = 1;
    for (r = row - 1, c = colIdx - 1; r >= 0 && c >= 0 && board[r][c] == symbol;r--, c--) {
        count++;
        
    }
    
    for (r = row + 1, c = colIdx + 1; r >= 0 && c >= 0 && board[r][c] == symbol;r++,c++) {
        count++;
        
    }
    if (count >= 4) return 1;

    // אלכסון משני (/)
    count = 1;
    for (r = row - 1, c = colIdx + 1; r >= 0 && c < COLS && board[r][c] == symbol; r--,c++) {
        count++;
    }
    
    for (r = row + 1, c = colIdx - 1; r < ROWS && c >= 0 && board[r][c] == symbol;r++,c--) {
        count++;
     
    }
    if (count >= 4) return 1;

    return 0;
}