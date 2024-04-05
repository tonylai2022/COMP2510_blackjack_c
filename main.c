#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define BLACKJACK 21
#define DEALER_STAND 17
#define ACE_HIGH 11
#define ACE_LOW 1
#define FACE_CARD 10

// Function prototypes
void shuffleDeck(int *deck);
void initializeDeck(int *deck);
int drawCard(int *deck, int *cardIndex);
void printCard(int card);
int getCardValue(int card, int *score);
double placeBet(double *playerMoney);
double placeSideBet(double *playerMoney);
int checkStraight(int, int, int); // Checks for three card straight for side bet
double playBlackjack(double playerMoney);

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

void shuffleDeck(int *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void initializeDeck(int *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = (i % 13) + 1; // Cards are 1-13 (Ace to King)
    }
}

int drawCard(int *deck, int *cardIndex) {
    if (*cardIndex >= DECK_SIZE) {
        printf("Ran out of cards!\n");
        exit(1);
    }
    return deck[(*cardIndex)++];
}

void printCard(int card) {
    if (card == 1) {
        printf("Ace ");
    } else if (card >= 11 && card <= 13) {
        if (card == 11) printf("Jack ");
        else if (card == 12) printf("Queen ");
        else printf("King ");
    } else {
        printf("%d ", card);
    }
}

int getCardValue(int card, int *score) {
    int value = (card >= 10) ? FACE_CARD : card;
    // Adjust for Ace
    if (card == 1) {
        value = (*score + ACE_HIGH <= BLACKJACK) ? ACE_HIGH : ACE_LOW;
    }
    return value;
}

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


int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int checkStraight(int card1, int card2, int dealerCard) {
    int hand[3] = {card1, card2, dealerCard};
    qsort(hand, 3, sizeof(int), compare);

    // Check for straight
    return (hand[0] + 1 == hand[1]) && (hand[1] + 1 == hand[2]);
}

double playBlackjack(double playerMoney) {
    int deck[DECK_SIZE];
    int cardIndex = 0;

    initializeDeck(deck);
    shuffleDeck(deck);

    double bet = placeBet(&playerMoney); // Place the bet
    double sideBet = placeSideBet(&playerMoney); // Optional side bet

    int playerScore = 0, dealerScore = 0;

    int insuranceBetExists = 0;

    // Initial deal
    int playerCard1 = drawCard(deck, &cardIndex);
    playerScore += getCardValue(playerCard1, &playerScore);
    int dealerCard1 = drawCard(deck, &cardIndex);
    dealerScore += getCardValue(dealerCard1, &dealerScore);
    int playerCard2 = drawCard(deck, &cardIndex);
    playerScore += getCardValue(playerCard2, &playerScore);
    int dealerCard2 = drawCard(deck, &cardIndex);
    dealerScore += getCardValue(dealerCard2, &dealerScore);

    printf("Dealer's first card: ");
    printCard(dealerCard1);
    printf("\nYour cards: ");
    printCard(playerCard1);
    printCard(playerCard2);
    printf("\n");

    if (sideBet > 0) { // Checks the side bet conditions if a side bet was placed
        int total = playerCard1 + playerCard2 + dealerCard1;
        // Adjust for Aces
        if (playerCard1 == 1) playerCard1 = 11;
        if (playerCard2 == 1) playerCard2 = 11;
        if (dealerCard1 == 1) dealerCard1 = 11;

        if (total == 21 || checkStraight(playerCard1, playerCard2, dealerCard1)) {
            printf("Congratulations! Your side bet wins.\n");
            // Assuming a payout of 5:1 for the side bet
            playerMoney += sideBet * 6; // Original bet plus winnings
        } else {
            printf("Side bet lost.\n");
        }
    }
    printf("\n");

// Insurance option if dealer draws an ace.
    if (dealerCard1 == 1) {
        printf("Dealer's card is an Ace. Would you like the insurance option? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            // Place insurance bet
            double insuranceBet = bet / 2.0;
            printf("Insurance bet placed: $%.2f\n", insuranceBet);
            insuranceBetExists = 1;
            playerMoney -= insuranceBet; // Deduct the insurance bet from player's money
        }
    }


    // Split logic
    int split = 0;
    if (playerCard1 == playerCard2 && playerMoney >= bet) {
        char choice;
        printf("Would you like to split? (y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        split = choice == 'y';
    }

    int hands[] = {-1, -1};
    double bets[] = {bet, bet};
    hands[0] = playerScore;
    if (split) {
        hands[0] = playerCard1;
        hands[1] = playerCard2;
        int hand1Card = drawCard(deck, &cardIndex);
        hands[0] += getCardValue(hand1Card, hands);
        int hand2Card = drawCard(deck, &cardIndex);
        hands[1] += getCardValue(hand2Card, hands + 1);
        printf("You were dealt a ");
        printCard(hand1Card);
        printf("to your first hand, and a ");
        printCard(hand2Card);
        printf("to your second hand.\n");
        playerMoney -= bet;
    }
    // TODO: Simplify loop - Jaiden
    for (int i = 0; i <= split; ++i) {
        if (split) {
            printf("Hand %d\n", i + 1);
            printf("Your score: %d\n", hands[i]);
        }
        playerScore = hands[i];
        bet = bets[i];
        // Double option
        char doubleChoice;
        int doubled = 0; // Flag to indicate if player has doubled
        if (playerScore != BLACKJACK) { // Only offer double option if player doesn't have blackjack
            printf("Would you like to double your bet? (y/n): ");
            scanf(" %c", &doubleChoice);
            // Clear the input buffer
            while (getchar() != '\n');

            if (doubleChoice == 'y') {
                if (playerMoney < bet) {
                    printf("You don't have enough money to double your bet.\n");
                } else {
                    playerMoney -= bet; // Deduct the additional bet from player's money
                    bet *= 2; // Double the bet
                    int card = drawCard(deck, &cardIndex);
                    playerScore += getCardValue(card, &playerScore);
                    printf("You drew: ");
                    printCard(card);
                    printf("\n");
                    if (playerScore > BLACKJACK) {
                        printf("Bust! Your score is %d. You lose.\n", playerScore);
                        hands[i] = -1;
                        continue;
                    }
                    doubled = 1; // Set flag to true
                }
            }
        }

        bets[i] = bet;

// Player's turn
        char choice;
        if (!doubled) {
            do {
                printf("Your score: %d\n", playerScore);
                if (playerScore == BLACKJACK) {
                    break; // Exit the loop if player has blackjack
                }
                do {
                    printf("Hit (h) or Stand (s)? ");
                    scanf(" %c", &choice);
                    // Clear the input buffer
                    while (getchar() != '\n');

                    if (choice != 'h' && choice != 's') {
                        printf("Invalid input. Please enter 'h' to hit or 's' to stand.\n");
                    }
                } while (choice != 'h' && choice != 's');

                if (choice == 'h') {
                    int card = drawCard(deck, &cardIndex);
                    playerScore += getCardValue(card, &playerScore);
                    printf("You drew: ");
                    printCard(card);
                    printf("\n");
                }

                if (playerScore > BLACKJACK) {
                    printf("Bust! Your score is %d. You lose.\n", playerScore);
                    hands[i] = -1;
                    choice = '\0';
                }
            } while (choice == 'h');
        }
        if (hands[i] != -1) {
            hands[i] = playerScore;
        }

    }

    int canWin = insuranceBetExists; // If there's insurance, wait to see the dealer's hand
    for (int i = 0; i <= split && canWin == 0; ++i) {
        if (hands[i] != -1) {
            canWin++;
        }
    }

    if (!canWin) {
        return playerMoney;
    }

    // Dealer's turn
    printf("Dealer's score: %d\n", dealerScore);
    while (dealerScore < DEALER_STAND) {
        int card = drawCard(deck, &cardIndex);
        dealerScore += getCardValue(card, &dealerScore);
        printf("Dealer draws: ");
        printCard(card);
        printf("\n");
    }
    printf("Dealer's final score: %d\n", dealerScore);

    // Determine insurance bet result.
    if (insuranceBetExists) {
        if (dealerScore == BLACKJACK && dealerCard1 == 1) {
            printf("Dealer has blackjack. Insurance bet wins! Your losses have been covered.\n");
            playerMoney += bet;
        } else {
            printf("Dealer does not have blackjack. Insurance bet loses.\n");
        }
    }

    for (int i = 0; i <= split; ++i) {
        playerScore = hands[i];
        bet = bets[i];
        if (split && playerScore != -1) {
            printf("Hand %d\n", i + 1);
        }
        if (playerScore == -1) {
            continue;
        }
// Determine winner
        if (playerScore == BLACKJACK && cardIndex == 4 && !split) { // Check if player has blackjack without splitting or doubling
            printf("Blackjack! You win 1.5 times your bet!\n");
            playerMoney += bet * 2.5; // Blackjack win (1.5 times the bet plus the original bet)
        } else if (dealerScore > BLACKJACK) {
            printf("Dealer busts. You win!\n");
            playerMoney += bet * 2; // Regular win
        } else if (playerScore > dealerScore) {
            printf("You win with %d against the dealer's %d!\n", playerScore, dealerScore);
            playerMoney += bet * 2; // Regular win
        } else if (playerScore == dealerScore) {
            if (playerScore == BLACKJACK) {
                printf("Both have blackjack. It's a tie!\n");
                playerMoney += bet; // Return the bet in case of a tie with blackjack
            } else {
                printf("It's a tie! Dealer wins ties, so you lose.\n");
            }
        } else {
            printf("Dealer wins with %d against your %d.\n", dealerScore, playerScore);
        }
    }
    return playerMoney;
}
