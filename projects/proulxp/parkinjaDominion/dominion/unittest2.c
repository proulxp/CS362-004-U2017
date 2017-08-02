/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the function fullDeckCount()
 
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
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (fullDeckCount) ----------------\n");
    printf("Note: Please see note in report regarding return value testing versus state testing. \n\n");
    
    //TEST 1 - Counting from hand mechanic
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 1 - Test fullDeckCount with no cards in discard or deck, just in hand.\n");
    printf("The players hand has 6 cards total, 2 smithy, 1 silver, and 3 gold.\n");
    
   
    testGS.deckCount[0] = 0;
    testGS.discardCount[0] = 0;
    
    testGS.handCount[0] = 6;
    
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = silver;
    testGS.hand[0][3] = gold;
    testGS.hand[0][4] = gold;
    testGS.hand[0][5] = gold;
    
    printf("fullDeckCount is run with checking for the number of gold cards.\n");
    printf("The returned value should be 3.\n");
    
    asserttrue(fullDeckCount(0, gold, &testGS), 3);
    
    //TEST 2 - Counting from discard mechanic
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 2 - Test fullDeckCount with no cards in hand or deck, just in discard.\n");
    printf("The players has 6 cards total in discard, 2 smithy, 1 silver, and 3 gold.\n");
    
    
    testGS.deckCount[0] = 0;
    testGS.discardCount[0] = 6;
    testGS.handCount[0] = 0;
    
    testGS.discard[0][0] = smithy;
    testGS.discard[0][1] = smithy;
    testGS.discard[0][2] = silver;
    testGS.discard[0][3] = gold;
    testGS.discard[0][4] = gold;
    testGS.discard[0][5] = gold;
    
    printf("fullDeckCount is run with checking for the number of silver cards.\n");
    printf("The returned value should be 1.\n");
    
    asserttrue(fullDeckCount(0, silver, &testGS), 1);
    
    //TEST 3 - Counting from deck mechanic
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 3 - Test fullDeckCount with no cards in hand or discard, just in deck.\n");
    printf("The players hand has 6 cards total in deck, 2 smithy, 1 silver, and 3 gold.\n");
    
    
    testGS.deckCount[0] = 6;
    testGS.discardCount[0] = 0;
    testGS.handCount[0] = 0;
    
    testGS.deck[0][0] = smithy;
    testGS.deck[0][1] = smithy;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    testGS.deck[0][5] = gold;
    
    printf("fullDeckCount is run with checking for the number of smithy cards.\n");
    printf("The returned value should be 2.\n");
    
    asserttrue(fullDeckCount(0, smithy, &testGS), 2);
    
    //TEST 4 - Counting from all piles simultaneously
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 4 - Test fullDeckCount with cards in hand, discard, and deck.\n");
    printf("The players hand has 6 cards total in deck, 3 smithy, 1 silver, and 2 gold.\n");
    printf("The players hand has 6 cards total in hand, 2 smithy, 1 silver, and 3 gold.\n");
    printf("The players hand has 6 cards total in discard, 1 smithy, 1 silver, and 4 gold.\n");
    
    
    testGS.deckCount[0] = 6;
    testGS.discardCount[0] = 6;
    testGS.handCount[0] = 6;
    
    testGS.deck[0][0] = smithy;
    testGS.deck[0][1] = smithy;
    testGS.deck[0][2] = silver;
    testGS.deck[0][3] = smithy;
    testGS.deck[0][4] = gold;
    testGS.deck[0][5] = gold;
    
    testGS.hand[0][0] = smithy;
    testGS.hand[0][1] = smithy;
    testGS.hand[0][2] = silver;
    testGS.hand[0][3] = gold;
    testGS.hand[0][4] = gold;
    testGS.hand[0][5] = gold;
    
    testGS.discard[0][0] = gold;
    testGS.discard[0][1] = smithy;
    testGS.discard[0][2] = silver;
    testGS.discard[0][3] = gold;
    testGS.discard[0][4] = gold;
    testGS.discard[0][5] = gold;
    
    
    
    printf("fullDeckCount is run with checking for the number of gold cards.\n");
    printf("The returned value should be 9.\n");
    
    asserttrue(fullDeckCount(0, gold, &testGS), 9);
    

    
    
    
    
    return 0;
}


