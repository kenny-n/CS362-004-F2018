//
// Created by Kenny Ngo on 10/13/18.
//
#include "../dominion.h"
#include "../dominion_helpers.h"
#include <printf.h>
#include <stdlib.h>

int assertNotEqual(int expectedValue, int actualValue) {
    return actualValue != expectedValue;
}

int testGetCost() {
    int failFlag = 0;
    failFlag = failFlag || assertNotEqual(0, getCost(curse));
    failFlag = failFlag || assertNotEqual(2, getCost(estate));
    failFlag = failFlag || assertNotEqual(5, getCost(duchy));
    failFlag = failFlag || assertNotEqual(8, getCost(province));
    failFlag = failFlag || assertNotEqual(0, getCost(copper));
    failFlag = failFlag || assertNotEqual(3, getCost(silver));
    failFlag = failFlag || assertNotEqual(6, getCost(gold));
    failFlag = failFlag || assertNotEqual(6, getCost(adventurer));
    failFlag = failFlag || assertNotEqual(5, getCost(council_room));
    failFlag = failFlag || assertNotEqual(4, getCost(feast));
    failFlag = failFlag || assertNotEqual(4, getCost(gardens));
    failFlag = failFlag || assertNotEqual(5, getCost(mine));
    failFlag = failFlag || assertNotEqual(4, getCost(remodel));
    failFlag = failFlag || assertNotEqual(4, getCost(smithy));
    failFlag = failFlag || assertNotEqual(3, getCost(village));
    failFlag = failFlag || assertNotEqual(4, getCost(baron));
    failFlag = failFlag || assertNotEqual(3, getCost(great_hall));
    failFlag = failFlag || assertNotEqual(5, getCost(minion));
    failFlag = failFlag || assertNotEqual(3, getCost(steward));
    failFlag = failFlag || assertNotEqual(5, getCost(tribute));
    failFlag = failFlag || assertNotEqual(3, getCost(ambassador));
    failFlag = failFlag || assertNotEqual(4, getCost(cutpurse));
    failFlag = failFlag || assertNotEqual(2, getCost(embargo));
    failFlag = failFlag || assertNotEqual(5, getCost(outpost));
    failFlag = failFlag || assertNotEqual(4, getCost(salvager));
    failFlag = failFlag || assertNotEqual(4, getCost(sea_hag));
    failFlag = failFlag || assertNotEqual(4, getCost(treasure_map));
    failFlag = failFlag || assertNotEqual(-1, getCost(-1)); // testing invalid card value returns -1

    return failFlag;
}

int main() {
    if (testGetCost()) {
        printf("TEST FAILED: getCost returned incorrect value");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED");
    return 0;
}