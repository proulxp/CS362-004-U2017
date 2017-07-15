/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the Smithy Card
 
  ** Referenced: Provided previous student cardtest4.c code
 
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
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
    int smithyBool = 1;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (Smithy Card) ----------------\n");
    
    //TEST 1 - Check drawing mechanic
    
    printf("TEST 1 - Smithy draws exactly 3 cards.\n");
    printf("The players hand has 5 cards and all are smithy.\n");
    printf("The players deck has 6 cards and they are all silver cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only have 7 cards after played.\n");
    printf("Actual Value: %d\n", testGS.handCount[0]);
    asserttrue(testGS.handCount[0], 8);
    
    //TEST 2 - Check discard mechanic
    
    printf("TEST 2 - Smithy is properly discarded after turn.\n");
    printf("The players hand has 5 cards and all are smithy.\n");
    printf("The played pile is empty to start.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.playedCardCount = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The played pile should increase by 1.\n");
    printf("Actual Value: %d\n", testGS.playedCardCount);
    asserttrue(testGS.playedCardCount, 1);
    
    //TEST 3 - Check removal from hand
    
    printf("TEST 3 - Smithy is properly removed from hand.\n");
    printf("The players hand has 5 cards and all are smithy.\n");
    printf("The players deck has 6 cards and all are silver cards.\n");
  
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players hand should only have 4 smithy cards after played.\n");
    
    int index = 0;
    int smithyCount = 0;
    
    for(index = 0; index < testGS.handCount[0]; index++)
    {
        if(testGS.hand[0][index] == smithy)
        {
            smithyCount++;
        }
    }
    
    printf("Actual Value: %d\n", smithyCount);
    asserttrue(smithyCount, 4);
    
    //TEST 4 - Check removal from own deck
    
    printf("TEST 4 - Smithy removes cards from own deck.\n");
    printf("The players hand has 5 cards and all are smithy.\n");
    printf("The players deck has 6 cards and all are silver cards.\n");
    
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The players deck should only have 1 silver card remaining (Known bug to remove 5 cards).\n");
    
    if(testGS.deck[0][0] != silver)
    {
        smithyBool = 0;
    }
    
    if(testGS.deckCount[0] != 1)
    {
        smithyBool = 0;
    }
    
    printf("Actual Value: %d\n", testGS.deckCount[0]);
    asserttrue(smithyBool, 1);
    
    smithyBool = 1; //Reset smithyBool
    
    //TEST 5 - Check affect on victory piles or kingdom card piles
    
    printf("TEST 5 - Smithy has no affect on victory piles or kingdom piles.\n");
    printf("Saving counts from vicotry piles and kingdom piles before playing Smithy.\n");

    int saveCount[27];
    index = 0;
    
    for(index = 0; index < 28; index++)
    {
        saveCount[index] = testGS.supplyCount[index];
    }
    
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The saved counts should match the original counts.\n");
    
    index = 0;
    
    for(index = 0; index < 28; index++)
    {
        if(saveCount[index] != testGS.supplyCount[index])
        {
            smithyBool = 0;
        }
    }
    
    asserttrue(smithyBool, 1);
    
    smithyBool = 1; //Reset smithyBool
    
    //TEST 6 - Check affect on other players
    
    printf("TEST 6 - Smithy has no affect on other player's state.\n");
    printf("Player 1 has no affect on Player 2's deck, hand, and discard counts.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    printf("Saving player 2 counts before player 1 plays.\n");
    int discard2 = testGS.discardCount[1];
    int deck2 = testGS.deckCount[1];
    int hand2 = testGS.handCount[1];
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = silver;
    testGS.deck[0][1] = silver;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = silver;
    testGS.deck[0][4] = silver;
    testGS.deck[0][5] = silver;
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = smithy;
    testGS.hand[0][3] = smithy;
    testGS.hand[0][4] = smithy;
    
    cardEffect(smithy, 0, 0, 0, &testGS, 0, 0);
    
    printf("The saved counts should match the original counts.\n");
    
    if(discard2 != testGS.discardCount[1])
    {
        smithyBool = 0;
    }
    
    if(deck2 != testGS.deckCount[1])
    {
       smithyBool = 0;
    }
    
    if(hand2 != testGS.handCount[1])
    {
       smithyBool = 0;
    }
    
    asserttrue(smithyBool, 1);

    
    return 0;
}
