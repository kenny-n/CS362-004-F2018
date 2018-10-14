//
// Created by Kenny Ngo on 10/13/18.
//
#include <dominion.h>
#include <printf.h>

int testKingdomCards()
{
    int i;
    int expectedCards[10];

    for (i = 0; i < 10; i++)
    {
        expectedCards[i] = i;
    }

    int* actualCards = kingdomCards(expectedCards[0], expectedCards[1], expectedCards[2], expectedCards[3],
            expectedCards[4], expectedCards[5], expectedCards[6], expectedCards[7], expectedCards[8], expectedCards[9]);

    for (i = 0; i < 10; i++)
    {
        if (actualCards[i] != expectedCards[i])
        {
            printf("TEST FAILED");
            return 1;
        }
    }
    printf("TEST SUCCESSFULLY COMPLETED");
    return 0;
}

int main() {
    if (testKingdomCards()) {
        printf("TEST FAILED: kingdomCards failed");
        return 1;
    }
    printf("TEST SUCCESSFULLY COMPLETED");
    return 0;
}
