#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"

int main() {
    int mode = 0, level;
    
    GameStats myStats = { 0, 0, 0, 0 };

    while (mode != 4) { 
        printf("\n--- CONNECT 4 MASTER MENU ---\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("3. View Statistics\n"); 
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &mode);

        if (mode == 4) break;

        if (mode == 3) {
            printf("\n--- GAME STATISTICS ---\n");
            printf("Player 1 Wins: %d\n", myStats.p1Wins);
            printf("Player 2 Wins: %d\n", myStats.p2Wins);
            printf("Computer Wins: %d\n", myStats.computerWins);
            printf("Draws:         %d\n", myStats.draws);
            continue; // חוזר לתפריט
        }
        printf("\nChoose Rule Level:\n");
        printf("1. Classic (Vertical or Horizontal only)\n");
        printf("2. Advanced (Diagonal)\n");
        printf("Enter choice: ");
        scanf("%d", &level);

        int isAdvanced = (level == 2);

        if (mode == 1) {
            playPvP(isAdvanced, &myStats); // שולחים כתובת
        }
        else if (mode == 2) {
            playPvC(isAdvanced, &myStats); // שולחים כתובת
        }
    }

    return 0;
}