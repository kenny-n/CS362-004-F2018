//
// Created by Kenny Ngo on 11/13/18.
//

#include "../dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "../rngs.h"

// Randomly test the village card of dominion
int main (int argc, char** argv) {
    printf("Random test: village\n");

    srand(time(NULL));

    int numberOfTests = 100;
    int numberOfChecks = 2;
    int totalChecks = numberOfTests * numberOfChecks;
    int failedChecks = 0;

    for (int i = 0; i < numberOfTests; i++) {
        int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        int randomSeed = rand();
        struct gameState state;

        initializeGame(numPlayers, k, randomSeed, &state);

        int player = rand() % numPlayers;
        state.whoseTurn = player;
        state.deckCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND;

        int choice1 = rand() % 10;
        int choice2 = rand() % 10;
        int choice3 = rand() % 10;
        int handPos = rand() % MAX_HAND;
        int bonus = rand() % 10;

        int expectedHandCount = state.handCount[player] + 1 - 1; // gain 1, use 1
        int expectedNumActions = state.numActions + 2;

        cardEffect(village, choice1, choice2, choice3, &state, handPos, &bonus);

        if (state.handCount[player] != expectedHandCount) {
            printf("TEST FAILED: player %d didn't draw 2 cards\n", player);
            failedChecks++;
        }
        if (state.numActions != expectedNumActions) {
            printf("TEST FAILED: unexpected number of actions\n");
            failedChecks++;
        }
    }
    printf("%d/%d checks passed\n\n", totalChecks - failedChecks, totalChecks);
}