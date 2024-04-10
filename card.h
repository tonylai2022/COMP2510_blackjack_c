#ifndef CARD_H
#define CARD_H

// Prints the card's name based on its numerical value.
void printCard(int card);

// Gets the card's value for scoring, adjusting for Aces as needed.
int getCardValue(int card, int *score);

// Checks for three card straight for side bet
int checkStraight(int, int, int);

// Compares two integers
int compare(const void *a, const void *b);

#endif
