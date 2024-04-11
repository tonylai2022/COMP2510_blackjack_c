#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    double playerMoney = 100.00; // Initialize player's money
    srand(time(NULL));

    char playAgain = 'y';
    do {
        if (playerMoney <= 0) {
            playYouAreBroke();
            printf("You've run out of money. Game over.\n");
            break;
        }
        playerMoney = playBlackjack(playerMoney);
        if (playerMoney > 0) {
            printf("You have $%.2f.\n", playerMoney); // Print player's money after the first game
            printf("Do you want to play again? (y/n): ");
            scanf(" %c", &playAgain);
            // Clear the input buffer
            while (getchar() != '\n');
        }
    } while (playAgain == 'y');

    printf("Thank you for playing!\n");
    return 0;
}



