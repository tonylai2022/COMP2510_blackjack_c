#include <stdio.h>
#include <stdlib.h>
#include "game.h"

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

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int checkStraight(int card1, int card2, int dealerCard) {
    int hand[3] = {card1, card2, dealerCard};
    qsort(hand, 3, sizeof(int), compare);

    // Check for regular straight
    if ((hand[0] + 1 == hand[1]) && (hand[1] + 1 == hand[2])) {
        return 1;
    }

    // Special case for Ace (1), 2, 3 straight
    if (hand[0] == 1 && hand[1] == 2 && hand[2] == 3) {
        return 1;
    }

    // Special case for Queen (12), King (13), Ace (1) straight
    if (hand[0] == 1 && hand[1] == 12 && hand[2] == 13) {
        return 1;
    }

    return 0;
}

