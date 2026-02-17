#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "game.h"

void playPvP(int isAdvanced, GameStats* stats) {
    char board[ROWS][COLS]; // הגדרת מערך הלוח
    initBoard(board);       // איפוס הלוח בערכים ריקים
    int turn = 1, moves = 0; // משתנים למעקב אחר התור ומספר המהלכים
    int win = 0;             // משתנה דגל לבדיקת ניצחון

    // לולאה שרצה כל עוד אין ניצחון והלוח לא מלא
    while (!win && moves < ROWS * COLS) {
        printBoard(board);                      // הדפסת המצב הנוכחי של הלוח
        char symbol = (turn == 1) ? 'X' : 'O';  
        int col = getPlayerInput(turn);         // קליטת עמודה מהשחקן
        int row = placePiece(board, col, symbol); // ניסיון הנחת הדיסקית בלוח

        // בדיקה אם העמודה שנבחרה כבר מלאה
        if (row == -1) {
            printf("Column full! Try again.\n");
            continue; 
        }

        // בדיקת ניצחון - פיצול לפי מצב משחק (מתקדם או רגיל)
        if (isAdvanced) {
            if (checkDiagonalWin(board, row, col, symbol)) {
                win = 1;
            }
        }
        else {
            if (checkHorizontalWin(board, row, col, symbol)) win = 1;
            if (checkVerticalWin(board, row, col, symbol)) win = 1;
        }

        // טיפול במקרה של ניצחון
        if (win) {
            printBoard(board);               
            printf("Player %d Wins!\n", turn); 
            if (turn == 1) stats->p1Wins++;   
            else stats->p2Wins++;             
        }

        turn = (turn == 1) ? 2 : 1; // החלפת התור לשחקן הבא
        moves++;                    // קידום מונה המהלכים
    }

    // בדיקה אם המשחק הסתיים בתיקו (לוח מלא ללא מנצח)
    if (!win && moves == ROWS * COLS) {
        printf("It's a tie!\n");
        stats->draws++; // עדכון סטטיסטיקת תיקו
    }
}