#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

#include "game.h"

int playWinningSound() {
    // Open and play the WAV file
    PlaySound(TEXT("C:\\Users\\ephra\\Downloads\\krabs_money-1.wav"), NULL,
              SND_FILENAME | SND_ASYNC);

    // Wait for sound to finish (optional)
    Sleep(0);  // Sleep for 5 seconds

    return 0;
}

int playLosingSound() {
    // Open and play the WAV file
    PlaySound(TEXT("C:\\Users\\ephra\\Downloads\\sadtrombone.wav"),
              NULL, SND_FILENAME | SND_ASYNC);

    // Wait for sound to finish (optional)
    Sleep(0);  // Sleep for 5 seconds

    return 0;
}

int playInsuranceBetWins() {
    // Open and play the WAV file
    PlaySound(TEXT("C:\\Users\\ephra\\Downloads\\whoa-that-was-close-tommy-boy.wav"),
              NULL, SND_FILENAME | SND_ASYNC);

    // Wait for sound to finish (optional)
    Sleep(0);  // Sleep for 5 seconds

    return 0;
}

int playYouAreBroke() {
    // Open and play the WAV file
    PlaySound(TEXT("C:\\Users\\ephra\\Downloads\\youre-broke.wav"),
              NULL, SND_FILENAME | SND_ASYNC);

    // Wait for sound to finish (optional)
    Sleep(3000);  // Sleep for 5 seconds

    return 0;
}

int drawCardBasedOnDemo(int deck[], int *cardIndex, int demoValue) {
    return (DEMO == 0) ? drawCard(deck, cardIndex) : getDemoValue(demoValue, cardIndex);
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
    int playerCard1 = drawCardBasedOnDemo(deck, &cardIndex, 0);
    playerScore += getCardValue(playerCard1, &playerScore);

    int dealerCard1 = drawCardBasedOnDemo(deck, &cardIndex, 1);
    dealerScore += getCardValue(dealerCard1, &dealerScore);

    int playerCard2 = drawCardBasedOnDemo(deck, &cardIndex, 2);
    playerScore += getCardValue(playerCard2, &playerScore);

    int dealerCard2 = drawCardBasedOnDemo(deck, &cardIndex, 3);
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
                        playLosingSound();
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
                    playLosingSound();
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
            playInsuranceBetWins();
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
            playWinningSound();
            printf("Blackjack! You win 1.5 times your bet!\n");
            playerMoney += bet * 2.5; // Blackjack win (1.5 times the bet plus the original bet)
        } else if (dealerScore > BLACKJACK) {
            playWinningSound();
            printf("Dealer busts. You win!\n");
            playerMoney += bet * 2; // Regular win
        } else if (playerScore > dealerScore) {
            playWinningSound();
            printf("You win with %d against the dealer's %d!\n", playerScore, dealerScore);
            playerMoney += bet * 2; // Regular win
        } else if (playerScore == dealerScore) {
            if (playerScore == BLACKJACK) {
                printf("Both have blackjack. It's a tie!\n");
                playerMoney += bet; // Return the bet in case of a tie with blackjack
            } else {
                playLosingSound();
                printf("It's a tie! Dealer wins ties, so you lose.\n");
            }
        } else {
            playLosingSound();
            printf("Dealer wins with %d against your %d.\n", dealerScore, playerScore);
        }
    }
    return playerMoney;
}
