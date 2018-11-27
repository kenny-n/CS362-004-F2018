//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion.h"
#include <printf.h>
#include <stdlib.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

struct gameState* initMockGameState(int numPlayers, const int* kingdomCards) {
    struct gameState *state = newGame();
    int i, j;

    //set number of players
    state->numPlayers = numPlayers;

    //set number of Curse cards
    if (numPlayers == 2) {
        state->supplyCount[curse] = 10;
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else if (numPlayers == 3) {
        state->supplyCount[curse] = 20;
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }
    else {
        state->supplyCount[curse] = 30;
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    //set number of Kingdom cards
    for (i = adventurer; i <= treasure_map; i++) {
        for (j = 0; j < 10; j++) {
            if (kingdomCards[j] == i) {
                //check if card is a 'Victory' Kingdom card
                if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens) {
                    if (numPlayers == 2) {
                        state->supplyCount[i] = 8;
                    }
                    else {
                        state->supplyCount[i] = 12;
                    }
                } else {
                    state->supplyCount[i] = 10;
                }
                break;
            } else  {
                state->supplyCount[i] = -1;
            }
        }
    }

    //set player decks
    for (i = 0; i < numPlayers; i++) {
        state->deckCount[i] = 0;
        for (j = 0; j < 3; j++) {
            state->deck[i][j] = estate;
            state->deckCount[i]++;
        }
        for (j = 3; j < 10; j++) {
            state->deck[i][j] = copper;
            state->deckCount[i]++;
        }
    }
    return state;
}

int testInitializeGame(int numPlayers) {
    int i, j;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    struct gameState *expectedState = initMockGameState(numPlayers, k);

    int randSeed = 30;
    srand(randSeed);

    struct gameState actualState;

    initializeGame(numPlayers, k, randSeed, &actualState);

    printf ("Starting test with %d players.\n", numPlayers);

    int initGame = initializeGame(numPlayers, k, randSeed, &actualState);

    if ((numPlayers < 2 || numPlayers > MAX_PLAYERS) && (initGame != -1)) {
        printf("TEST FAILED: incorrect number of players (%i) allowed\n", numPlayers);
        return 1;
    } else if (initGame == -1) {
        return 0;
    }

    int failFlag = 0;

    for (i = curse; i <= treasure_map; i++) {
        if (assertNotEqual(expectedState->supplyCount[i], actualState.supplyCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of card: %d\n", i);
        }
    }

    for (i = 0; i < numPlayers; i++) {
        int estateCount = 0;
        int copperCount = 0;
        for (j = 0; j < 10; j++) {
            if (estate == actualState.deck[i][j]) {
                estateCount++;
            } else if (copper == actualState.deck[i][j]) {
                copperCount++;
            }
        }

        if (assertNotEqual(3, estateCount)) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of estate cards\n");
        } else if (assertNotEqual(7, copperCount)) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of copper cards\n");
        }

        if (i == 0 && assertNotEqual(5, actualState.handCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect hand count for player 1\n");
        } else if (i != 0 && assertNotEqual(0, actualState.handCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect hand count for player %d\n", i);
        } else if (assertNotEqual(0, actualState.discardCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect discard count\n");
        }
    }

    for (i = 0; i <= treasure_map; i++) {
        if (assertNotEqual(0, actualState.embargoTokens[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of card: %d\n", i);
        }
    }

    if (assertNotEqual(0, actualState.outpostPlayed) ||
        assertNotEqual(0, actualState.phase) ||
        assertNotEqual(1, actualState.numActions) ||
        assertNotEqual(1, actualState.numBuys) ||
        assertNotEqual(0, actualState.playedCardCount) ||
        assertNotEqual(0, actualState.whoseTurn) ||
        assertNotEqual(5, actualState.handCount[actualState.whoseTurn])) {
        failFlag = 1;
        printf("TEST FAILED: incorrect initialized stats\n");
    }

    return failFlag;
}

int main() {
    int failFlag = 0;

    failFlag = testInitializeGame(1) || failFlag;
    failFlag = testInitializeGame(2) || failFlag;
    failFlag = testInitializeGame(3) || failFlag;
    failFlag = testInitializeGame(4) || failFlag;
    failFlag = testInitializeGame(MAX_PLAYERS + 1) || failFlag;

    if (!failFlag) {
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
}
