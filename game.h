#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "card.h"
#include "player.h" // For player-related functions and structures
#include "demo.h"

#define DECK_SIZE 52
#define BLACKJACK 21
#define DEALER_STAND 17
#define ACE_HIGH 11
#define ACE_LOW 1
#define FACE_CARD 10

// Main function to play a round of Blackjack.
double playBlackjack(double playerMoney);

#endif
