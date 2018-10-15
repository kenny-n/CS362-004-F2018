//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

int testSmithy() {
    int card = smithy;

    int randSeed = 30;
    srand(randSeed);

    struct gameState testState;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, randSeed, &testState);

    int expectedHandCount = testState.handCount[0] + 3;

    int cardEffectResult = cardEffect(card, 0, 0, 0, &testState, 0, 0);

    if (cardEffectResult != 0) {
        return 1;
    }

    int actualHandCount = testState.handCount[0];

    return assertNotEqual(expectedHandCount, actualHandCount);
}

int main() {
    if (testSmithy()) {
        printf("TEST FAILED: smithy card failed\n");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED\n");
    return 0;
}
