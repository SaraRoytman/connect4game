#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// פונקציית עזר פנימית למחשב - בחירת עמודה אקראית
int getRandomMove(char board[ROWS][COLS]) {
    int col;
    do {
        col = (rand() % 7) + 1; // הגרלת מספר בין 1 ל-7
    } while (board[0][col - 1] != ' '); // וידוא שהעמודה שנבחרה לא מלאה
    return col;
}

void playPvC(int isAdvanced, GameStats* stats) {
    srand((unsigned int)time(NULL)); // אתחול מחולל המספרים האקראיים לפי הזמן
    char board[ROWS][COLS];          // יצירת מערך הלוח
    initBoard(board);                // איפוס הלוח
    int turn = 1, moves = 0, win = 0; // משתני עזר לניהול המשחק

    printf("\n--- Playing against the Computer ---\n");

    // לולאת המשחק הראשית
    while (!win && moves < ROWS * COLS) {
        printBoard(board);
        char symbol = (turn == 1) ? 'X' : 'O';
        int col;

        // קביעה מי מבצע את המהלך הנוכחי
        if (turn == 1) {
            col = getPlayerInput(1); // תור השחקן - קלט מהמקלדת
        }
        else {
            printf("Computer is thinking...\n");
            col = getRandomMove(board); // תור המחשב - בחירה אקראית
            printf("Computer chose column: %d\n", col);
        }

        int row = placePiece(board, col, symbol); // השחלת הדיסקית ללוח

        // בדיקת תקינות המהלך
        if (row == -1) {
            if (turn == 1) printf("Column full! Try again.\n");
            continue; // אם העמודה מלאה, חוזרים לתחילת התור
        }

        // לוגיקת בדיקת ניצחון (פיצול לפי רמת קושי)
        if (isAdvanced) {
            if (checkDiagonalWin(board, row, col, symbol)) { // במצב מתקדם: רק אלכסונים
                win = 1;
            }
        }
        else {
            // במצב רגיל: אופקי או אנכי
            if (checkHorizontalWin(board, row, col, symbol)) win = 1;
            if (checkVerticalWin(board, row, col, symbol)) win = 1;
        }

        // טיפול בסיום המשחק במקרה של ניצחון
        if (win) {
            printBoard(board);
            if (turn == 1) {
                printf("Congratulations! You won!\n");
                stats->p1Wins++; // עדכון ניצחון לשחקן בסטטיסטיקה
            }
            else {
                printf("The Computer won! Better luck next time.\n");
                stats->computerWins++; // עדכון ניצחון למחשב בסטטיסטיקה
            }
        }

        turn = (turn == 1) ? 2 : 1; // החלפת תור
        moves++;                    // קידום מונה מהלכים
    }

    // בדיקה אם המשחק נגמר ללא מנצח
    if (!win && moves == ROWS * COLS) {
        printf("It's a draw!\n");
        stats->draws++; // עדכון תיקו בסטטיסטיקה
    }
}