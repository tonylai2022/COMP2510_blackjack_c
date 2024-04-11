cmake_minimum_required(VERSION 3.27)

# Set the project name
project(blackjack C)

# Add the executable
add_executable(game main.c game.c deck.c card.c player.c
        demo.c
        demo.h)

# Link winm library to the game executable.
target_link_libraries(game PRIVATE winmm)

# Specify the C standard
set(CMAKE_C_STANDARD 90)