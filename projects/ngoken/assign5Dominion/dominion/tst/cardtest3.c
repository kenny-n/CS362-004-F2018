//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

int testVillage() {
    int card = village;

    int randSeed = 30;
    srand(randSeed);

    struct gameState testState;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, randSeed, &testState);

    int expectedHandCount = testState.handCount[0] + 1 - 1; // gain 1, use 1
    int expectedNumActions = testState.numActions + 2;
    int cardEffectResult = cardEffect(card, 0, 0, 0, &testState, 0, 0);

    if (cardEffectResult != 0) {
        return 1;
    }

    int actualHandCount = testState.handCount[0];
    int actualNumActions = testState.numActions;

    if (assertNotEqual(expectedHandCount, actualHandCount) || assertNotEqual(expectedNumActions, actualNumActions)) {
        return 1;
    }
    return 0;
}

int main() {
    if (testVillage()) {
        printf("TEST FAILED: village card failed\n");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED\n");
    return 0;
}
