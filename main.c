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
void playBlackjack();
void placeBet();

int main() {
    playBlackjack();
    return 0;
}

double placeBet() {
    double playerMoney = 100.00; // Temporary value, need player money to import
    double bet = -1.00;
    while (bet <= 0 || bet > playerMoney) { // Continue loop until a valid bet is made
        printf("How much would you like to bet on this hand?: ");
        scanf("%lf", &bet);

        if (bet <= 0) {
            printf("The bet must be greater than $0.00.\n");
        } else if (bet > playerMoney) {
            printf("You cannot bet more than you have. You have $%.2f.\n", playerMoney);
        }
        // No need for an else - if the bet is valid, the loop will exit naturally
    }

    return bet; // Only return when a valid bet has been made
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

void playBlackjack() {
    int deck[DECK_SIZE];
    int cardIndex = 0;
    srand(time(NULL));

    initializeDeck(deck);
    shuffleDeck(deck);

    int playerScore = 0, dealerScore = 0;

    // Initial deal
    playerScore += getCardValue(drawCard(deck, &cardIndex), &playerScore);
    dealerScore += getCardValue(drawCard(deck, &cardIndex), &dealerScore);
    playerScore += getCardValue(drawCard(deck, &cardIndex), &playerScore);
    dealerScore += getCardValue(drawCard(deck, &cardIndex), &dealerScore);

    printf("Dealer's first card: ");
    printCard(dealerScore / 2); // Simplification for demonstration
    printf("\nYour cards: ");
    printCard(playerScore / 2); // Assuming two cards, simplified display
    printCard(playerScore / 2);
    printf("\n");

    // Player's turn
    int input;
    char choice;
    do {
        printf("Your score: %d\n", playerScore);
        printf("Hit (h) or Stand (s)? ");

        input = getchar();
        // Clear the input buffer
        while (getchar() != '\n');

        if (input == EOF) {
            printf("Error reading input. Exiting game.\n");
            return;
        } else {
            choice = (char)input;
        }

        if (choice == 'h') {
            int card = drawCard(deck, &cardIndex);
            playerScore += getCardValue(card, &playerScore);
            printf("You drew: ");
            printCard(card);
            printf("\n");
        }

        if (playerScore > BLACKJACK) {
            printf("Bust! Your score is %d. You lose.\n", playerScore);
            return;
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
    } else if (playerScore > dealerScore) {
        printf("You win with %d against the dealer's %d!\n", playerScore, dealerScore);
    } else if (playerScore == dealerScore) {
        printf("It's a tie! Dealer wins ties, so you lose.\n");
    } else {
        printf("Dealer wins with %d against your %d.\n", dealerScore, playerScore);
    }
}