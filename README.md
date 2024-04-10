# COMP2510_Term_Project_Blackjack_In_C

# Blackjack Game

This is a simple command-line implementation of the popular card game Blackjack written in C.

## Team Members - Students numbers:
Tony Lai - A01279412
Jasper Wang - A01362031
Jaiden Duncan - A01376315
Ephraim Hsu - A01366848
Peter Senyk - A01376857

## Features

- Allows the player to place bets and play Blackjack against the dealer.
- Implements basic Blackjack rules, including card values, dealer's stand threshold, and bust conditions.
- Supports features such as double, splitting and taking insurance.

## How to Play

1. Compile the source code files (`main.c`, `functions.c`, `functions.h`) using a C compiler such as GCC.
2. Run the compiled executable.
3. Follow the on-screen instructions to play the game.
4. Enjoy the thrill of Blackjack!

## Rules

- The objective of Blackjack is to beat the dealer's hand without exceeding a total of 21.
- Aces can be counted as 1 or 11 points, face cards (Jack, Queen, King) are worth 10 points, and all other cards are worth their face value.
- The dealer must hit until their hand reaches a total of 17 or higher.
- The player wins if their hand is closer to 21 than the dealer's hand without busting (exceeding 21).
- If the player's first two cards have a total value of 21, they have a "blackjack" and win immediately unless the dealer also has a blackjack.
- Splitting is allowed when the player's first two cards have the same value, allowing them to play two separate hands.

## File Structure

- `main.c`: Contains the main function to start the game.
- `functions.c`: Contains the implementation of various game functions.
- `functions.h`: Header file declaring function prototypes and constants used in the game.

## Future Improvements

- Add more advanced features such as surrendering and more decks with or without reshuffling.
- Implement a graphical user interface (GUI) for a more interactive experience.
- Introduce multiplayer functionality to allow multiple players to participate in the game.

