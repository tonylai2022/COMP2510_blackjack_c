#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

//#define DECK_SIZE 52
//#define BLACKJACK 21
//#define DEALER_STAND 17
//#define ACE_HIGH 11
//#define ACE_LOW 1
//#define FACE_CARD 10

// Function prototypes
//void shuffleDeck(int *deck);
//void initializeDeck(int *deck);
//int drawCard(int *deck, int *cardIndex);
//void printCard(int card);
//int getCardValue(int card, int *score);
//double placeBet(double *playerMoney);
//double placeSideBet(double *playerMoney);
//int checkStraight(int, int, int); // Checks for three card straight for side bet
//double playBlackjack(double playerMoney);
//
int main() {
    double playerMoney = 100.00; // Initialize player's money
    srand(time(NULL));

    char playAgain = 'y';
    do {
        if (playerMoney <= 0) {
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






