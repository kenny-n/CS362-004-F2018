//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

int mockAdventure(int currentPlayer, struct gameState *state) {
    int temphand[MAX_HAND];
    int treasureCount = 0;
    int cardDrawn;
    int temphandCount = 0;

    while(treasureCount < 2){
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            treasureCount++;
        }
        else{
            temphand[temphandCount]=cardDrawn;
            state->handCount[currentPlayer]--;
            temphandCount++;
        }
    }

    while(temphandCount - 1 >= 0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[temphandCount - 1];
        temphandCount--;
    }

    return 0;
}

int testAdventurer() {
    int card = adventurer;

    int randSeed = 30;
    srand(randSeed);

    struct gameState expectedState, actualState;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(2, k, randSeed, &actualState);
    memcpy(&expectedState, &actualState, sizeof(struct gameState));

    int actualCardEffect = cardEffect(card, 0, 0, 0, &actualState, 0, 0);
    int expectedCardEffect = mockAdventure(expectedState.whoseTurn, &expectedState);

    if (assertNotEqual(expectedCardEffect, actualCardEffect)) {
        return 1;
    }

    int expectedTreasureCount = 0;
    int actualTreasureCount = 0;

    int i;
    for (i = 0; i < expectedState.handCount[expectedState.whoseTurn]; i++) {
        if (expectedState.hand[expectedState.whoseTurn][i] == copper ||
            expectedState.hand[expectedState.whoseTurn][i] == silver ||
            expectedState.hand[expectedState.whoseTurn][i] == gold) {
            expectedTreasureCount++;
        }
        if (actualState.hand[actualState.whoseTurn][i] == copper ||
             actualState.hand[actualState.whoseTurn][i] == silver ||
             actualState.hand[actualState.whoseTurn][i] == gold) {
            actualTreasureCount++;
        }
    }

    if (assertNotEqual(expectedTreasureCount, actualTreasureCount)) {
        return 1;
    }
    return 0;
}

int main() {
    if (testAdventurer()) {
        printf("TEST FAILED: adventure card failed\n");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED\n");
    return 0;
}
