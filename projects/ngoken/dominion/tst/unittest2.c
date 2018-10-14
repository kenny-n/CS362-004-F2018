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

    printf ("Starting test.\n");

    if ((numPlayers < 2 || numPlayers > MAX_PLAYERS) && (initializeGame(numPlayers, k, randSeed, &actualState) != -1)) {
        printf("TEST FAILED: incorrect number of players (%i) allowed", numPlayers);
    }

    int failFlag = 0;

    for (i = curse; i <= treasure_map; i++) {
        if (assertNotEqual(expectedState->supplyCount[i], actualState.supplyCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of card: %d", i);
        }
    }

    for (i = 0; i < numPlayers; i++) {
        for (j = 0; j < 3; j++) {
            if (assertNotEqual(estate, actualState.deck[i][j])) {
                failFlag = 1;
                printf("TEST FAILED: estate card not found");
            }
        }
        for (j = 3; j < 10; j++) {
            if (assertNotEqual(copper, actualState.deck[i][j])) {
                failFlag = 1;
                printf("TEST FAILED: copper card not found");
            }
        }
        if (assertNotEqual(0, actualState.handCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect hand count");
        } else if (assertNotEqual(0, actualState.discardCount[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect discard count");
        }
    }

    for (i = 0; i <= treasure_map; i++) {
        if (assertNotEqual(0, actualState.embargoTokens[i])) {
            failFlag = 1;
            printf("TEST FAILED: incorrect number of card: %d", i);
        }
    }

    if (assertNotEqual(0, actualState.outpostPlayed) ||
        assertNotEqual(0, actualState.phase) ||
        assertNotEqual(1, actualState.numActions) ||
        assertNotEqual(1, actualState.numBuys) ||
        assertNotEqual(0, actualState.playedCardCount) ||
        assertNotEqual(0, actualState.whoseTurn) ||
        assertNotEqual(0, actualState.handCount[actualState.whoseTurn])) {
        failFlag = 1;
        printf("TEST FAILED: incorrect initialized stats");
    }

    return failFlag;
}

int main() {
    int successFlag = 1;

    successFlag = !testInitializeGame(1);
    successFlag = !testInitializeGame(2);
    successFlag = !testInitializeGame(3);
    successFlag = !testInitializeGame(4);
    successFlag = !testInitializeGame(MAX_PLAYERS + 1);

    if (successFlag) {
        printf("TEST SUCCESSFULLY COMPLETED");
    }
}
