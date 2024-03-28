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

double playBlackjack(double playerMoney) {
    int deck[DECK_SIZE];
    int cardIndex = 0;

    initializeDeck(deck);
    shuffleDeck(deck);

    double bet = placeBet(&playerMoney); // Place the bet

    int playerScore = 0, dealerScore = 0;

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

    // Player's turn
    char choice;
    do {
        printf("Your score: %d\n", playerScore);
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
            return playerMoney;
        }
    } while (choice == 'h');

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

    // Determine winner
    if (dealerScore > BLACKJACK) {
        printf("Dealer busts. You win!\n");
        return playerMoney + bet * 2;
    } else if (playerScore > dealerScore) {
        printf("You win with %d against the dealer's %d!\n", playerScore, dealerScore);
        return playerMoney + bet * 2;
    } else if (playerScore == dealerScore) {
        printf("It's a tie! Dealer wins ties, so you lose.\n");
        return playerMoney;
    } else {
        printf("Dealer wins with %d against your %d.\n", dealerScore, playerScore);
        return playerMoney - bet;
    }
}
