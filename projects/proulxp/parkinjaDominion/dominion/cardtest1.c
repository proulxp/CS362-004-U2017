/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the Adventuerer Card
 
  ** Referenced: Provided previous student cardtest4.c code
 
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

/*********************************************************************
 
 ** Description: An assertion function that prints whether the two parameters
 are the same indicating a passed test or if they are differnt which indicates
 a failing test.
 
 *********************************************************************/
void asserttrue(int param1, int param2)
{
    if(param1 == param2)
    {
        printf("TEST SUCCESSFULLY COMPLETED\n\n");
    }
    else
    {
        printf("TEST FAILED\n\n");
    }
}


int main() {
   
    int playerNum = 2;
    int randomizer = 10;
    int trueBool = 1;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (Adventurer Card) ----------------\n");
    
    //TEST 1 - Check drawing mechanic
    
    printf("TEST 1 - Adventurer stops drawing after 2 treasure cards are pulled\n");
    printf("The players hand has 5 cards and all are adventurer.\n");
    printf("The players deck has 5 cards and they are all silver cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = adventurer;
    testGS.hand[0][1] = adventurer;
    testGS.hand[0][2] = adventurer;
    testGS.hand[0][3] = adventurer;
    testGS.hand[0][4] = adventurer;
    
    cardEffect(adventurer, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only have 2 silver cards.\n");
    
    int index = 0;
    int silverCount = 0;
    
    for(index = 0; index < testGS.handCount[0]; index++)
    {
        if(testGS.hand[0][index] == silver)
        {
            silverCount++;
        }
    }
    
    printf("Actual Value: %d\n", silverCount);
    asserttrue(silverCount, 2);
    
    trueBool = 1; //Reset boolean
    
    //TEST 2 - Check drawing mechanic 2
    
    printf("TEST 2 - Adventurer stops drawing after 2 treasure cards are pulled (again)\n");
    printf("The players hand has 5 cards and all are adventurer.\n");
    printf("The players deck has 5 cards and they are 2 gold, 2 silver, and 1 copper.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = copper;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = adventurer;
    testGS.hand[0][1] = adventurer;
    testGS.hand[0][2] = adventurer;
    testGS.hand[0][3] = adventurer;
    testGS.hand[0][4] = adventurer;
    
    cardEffect(adventurer, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only have 6 cards.\n");
    
    printf("Actual Value: %d\n", testGS.handCount[0]);
    asserttrue(testGS.handCount[0], 6);
    
    //TEST 3 - Cards kept are only treasure
    
    printf("TEST 3 - Adventurer only keeps treasure cards in hand.\n");
    printf("The players hand has 5 cards and all are adventurer.\n");
    printf("The players deck has 5 cards and they are 2 gold, 2 smithy, and 1 mine.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = smithy;
    testGS.deck[0][3] = smithy;
    testGS.deck[0][4] = mine;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = adventurer;
    testGS.hand[0][1] = adventurer;
    testGS.hand[0][2] = adventurer;
    testGS.hand[0][3] = adventurer;
    testGS.hand[0][4] = adventurer;
    
    cardEffect(adventurer, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only contain adventuerer or gold cards.\n");
    
    index = 0;
    int otherCount = 0;
    
    for(index = 0; index < testGS.handCount[0]; index++)
    {
        if(testGS.hand[0][index] != adventurer && testGS.hand[0][index] != gold)
        {
            otherCount++;
        }
    }
    
    printf("Actual Value: %d\n", otherCount);
    asserttrue(otherCount, 0);
    
    trueBool = 1; //Reset boolean
    
    //TEST 4 - Test discard to deck mechanic
    
    printf("TEST 4 - Adventurer should take discard and place into deck if deck is empty.\n");
    printf("The players hand has 5 cards and all are adventurer.\n");
    printf("The players deck is empty and the players discard pile has 5 gold cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 0;
    
    testGS.discardCount[0] = 5;
    testGS.discard[0][0] = gold;
    testGS.discard[0][1] = gold;
    testGS.discard[0][2] = gold;
    testGS.discard[0][3] = gold;
    testGS.discard[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = adventurer;
    testGS.hand[0][1] = adventurer;
    testGS.hand[0][2] = adventurer;
    testGS.hand[0][3] = adventurer;
    testGS.hand[0][4] = adventurer;
    
    cardEffect(adventurer, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players deck should have 3 cards and all are gold cards.\n");
    
    index = 0;
    int goldCount = 0;
    
    for(index = 0; index < testGS.deckCount[0]; index++)
    {
        if(testGS.deck[0][index] == gold)
        {
            goldCount++;
        }
    }
    
    if(testGS.deckCount[0] != 3 || goldCount != 3)
    {
        trueBool = 0;
    }
    
    
    asserttrue(trueBool, 1);
    
    trueBool = 1;  //Reset bool
    
    //TEST 5 - Test discard mechanic
    
    printf("TEST 5 - Adventurer should take all non-treasure cards pulled and place into discard.\n");
    printf("The players hand has 5 cards and all are adventurer.\n");
    printf("The discard pile is empty to start.\n");
    printf("The players deck has 6 cards the top 3 are smithy, the next 2 are gold cards, and the last card is a smithy.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 0;
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = smithy;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = smithy;
    testGS.deck[0][4] = smithy;
    testGS.deck[0][5] = smithy;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = adventurer;
    testGS.hand[0][1] = adventurer;
    testGS.hand[0][2] = adventurer;
    testGS.hand[0][3] = adventurer;
    testGS.hand[0][4] = adventurer;
    
    cardEffect(adventurer, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only have 7 cards and the last two should be gold cards.\n");
    printf("The discard pile should only have 4 cards and those 4 cards are 3 smithy and the adventurer.\n");
    
    if(testGS.handCount[0] != 7)
    {
        trueBool = 0;
    }
    
    if(testGS.hand[0][5] != gold || testGS.hand[0][6] != gold)
    {
        trueBool = 0;
    }
    
    if(testGS.discardCount[0] != 4)
    {
        trueBool = 0;
    }
    
    asserttrue(trueBool, 1);
    

    
    
    return 0;
}


