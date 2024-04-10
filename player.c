#include <stdio.h>
#include "player.h"

double placeBet(double *playerMoney) {
    double bet = 0.0;
    printf("You have $%.2f.\n", *playerMoney);
    while (bet <= 0 || bet > *playerMoney) {
        printf("How much would you like to bet on this hand?: ");
        scanf("%lf", &bet);

        if (bet <= 0) {
            printf("The bet must be greater than $0.00.\n");
        } else if (bet > *playerMoney) {
            printf("You cannot bet more than you have.\n");
        }
    }
    *playerMoney -= bet; // Deduct the bet from player's money
    return bet;
}

double placeSideBet(double *playerMoney) {
    printf("Would you like to place a side bet? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    while (getchar() != '\n'); // Clear the input buffer.

    if (choice == 'y' || choice == 'Y') {
        double sideBet = 0.0;
        do {
            printf("How much would you like to bet? (Maximum bet $5.00, you have $%.2f): ", *playerMoney);
            scanf("%lf", &sideBet);
            // Clear the input buffer.
            while (getchar() != '\n');

            if (sideBet < 0 || sideBet > 5.0) {
                printf("The bet must be between $0.00 and $5.00.\n");
            } else if (sideBet > *playerMoney) {
                printf("You cannot bet more than you have.\n");
            }
        } while (sideBet <= 0 || sideBet > 5.0 || sideBet > *playerMoney);

        *playerMoney -= sideBet; // Deduct bet from player's money
        return sideBet;
    } else {
        return 0.0;
    }
}
