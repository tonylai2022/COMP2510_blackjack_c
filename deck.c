#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

void initializeDeck(int *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = (i % 13) + 1; // Cards are 1-13 (Ace to King)
    }
}

void shuffleDeck(int *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

int drawCard(int *deck, int *cardIndex) {
    if (*cardIndex >= DECK_SIZE) {
        printf("Ran out of cards!\n");
        exit(1);
    }
    return deck[(*cardIndex)++];
}
