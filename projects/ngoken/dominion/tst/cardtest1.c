//
// Created by Kenny Ngo on 10/13/18.
//
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

int testAdventurer()
{
    int card = adventurer;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    struct gameState *state = newGame();
    int handPos = 0;
    int *bonus = 0;

    cardEffect(card, choice1, choice2, choice3, state, handPos, bonus);
}

int initializeGameState()
{
    int randSeed = 30;
    srand(randSeed);

    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf ("Starting test.\n");

    initializeGame(2, k, randSeed, &G);
}
