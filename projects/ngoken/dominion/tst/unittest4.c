//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion.h"
#include <printf.h>
#include <stdlib.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

struct gameState* initMockGameState(int numPlayers) {
    struct gameState *state = newGame();

    //set number of players
    state->numPlayers = numPlayers;

    state->whoseTurn = 0;

    return state;
}

int testWhoseTurn(int numPlayers) {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    struct gameState *expectedState = initMockGameState(numPlayers);

    int randSeed = 30;
    srand(randSeed);

    struct gameState actualState;

    initializeGame(numPlayers, k, randSeed, &actualState);

    return assertNotEqual(whoseTurn(expectedState), whoseTurn(&actualState));
}

int main() {
    if (testWhoseTurn(2)) {
        printf("TEST FAILED: whoseTurn returned incorrect player");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED");
    return 0;
}
