#include "demo.h"

int getDemoValue(int forCard, int *cardIndex) {
    // for forCard, 0 represents playerCard1, 1 represents dealerCard 1, 2 is playerCard2, and 3 is dealerCard2
    if (DEMO != 0) {
        // 0 is not demo
        (*cardIndex)++;
    }
    switch (DEMO) {
        case 1:
            // tie
            switch (forCard) {
                case 0:
                    return 10;
                case 1:
                    return 10;
                case 2:
                    return 7;
                case 3:
                    return 7;
            }
        case 2:
            // user win
            switch (forCard) {
                case 0:
                    return 1;
                case 1:
                    return 10;
                case 2:
                    return 10;
                case 3:
                    return 10;
            }
        case 3:
            // user side bet
            switch (forCard) {
                case 0:
                    return 7;
                case 1:
                    return 8;
                case 2:
                    return 9;
                case 3:
                    return 10;
            }
        case 4:
            // Insurance loss
            switch (forCard) {
                case 0:
                    return 8;
                case 1:
                    return 1;
                case 2:
                    return 7;
                case 3:
                    return 2;
            }
        case 5:
            // Insurance win
            switch (forCard) {
                case 0:
                    return 8;
                case 1:
                    return 1;
                case 2:
                    return 7;
                case 3:
                    return 10;
            }
        case 6:
            // Double win
            switch (forCard) {
                case 0:
                    return 8;
                case 1:
                    return 10;
                case 2:
                    return 3;
                case 3:
                    return 6;
            }
    }
}
