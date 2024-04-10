#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52

// Initializes the deck of cards.
void initializeDeck(int *deck);

// Shuffles the deck of cards.
void shuffleDeck(int *deck);

// Draws a card from the deck.
int drawCard(int *deck, int *cardIndex);

#endif
