/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the Feast Card
 
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
    int feastBool = 1;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, feast};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (Feast Card) ----------------\n");
    
    //TEST 1 - Check trash mechanic
    
    printf("TEST 1 - Feast is trashed after played.\n");
    printf("The players hand has 5 cards, 4 are copper and 1 is a Feast.\n");
    printf("The discard deck is empty.\n");
    printf("The players deck has 5 cards and they are all gold cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;

    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = feast;
    testGS.hand[0][1] = copper;
    testGS.hand[0][2] = copper;
    testGS.hand[0][3] = copper;
    testGS.hand[0][4] = copper;
    
    cardEffect(feast, smithy, 0, 0, &testGS, 0, 0);
    
    printf("The players hand, deck, and discard should not contain a feast card.\n");
    
    int index = 0;
    int index2 = 0;
    int index3 = 0;
    
    for(index = 0; index < testGS.discardCount[0]; index++)
    {
        if(testGS.discard[0][index] == feast)
        {
            feastBool = 0;
        }
    }
    
    for(index2 = 0; index2 < testGS.deckCount[0]; index2++)
    {
        if(testGS.deck[0][index2] == feast)
        {
            feastBool = 0;
        }
    }
    
    for(index3 = 0; index3 < testGS.handCount[0]; index3++)
    {
        if(testGS.hand[0][index3] == feast)
        {
            feastBool = 0;
        }
    }
    
    
    asserttrue(feastBool, 1);
    
    feastBool = 1; //Reset feast bool
    
    //TEST 2 - Check card gain mechanic
    
    printf("TEST 2 - Feast sends user's choice to discard pile.\n");
    printf("The players hand has 5 cards, 4 are copper and 1 is a Feast.\n");
    printf("The discard deck is empty.\n");
    printf("For this test, the user chooses a silver card to obtain.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = feast;
    testGS.hand[0][1] = copper;
    testGS.hand[0][2] = copper;
    testGS.hand[0][3] = copper;
    testGS.hand[0][4] = copper;
    
    cardEffect(feast, silver, 0, 0, &testGS, 0, 0);
    
    printf("The players discard deck should contain one card and it should be a silver card.\n");
    
    printf("Actual Value: %d\n", testGS.discard[0][0]);
    asserttrue(testGS.discard[0][0], silver);

    //TEST 3 - Check gained card is removed from supply
    
    printf("TEST 3 - Feast gains a card, ensure this is properly removed from supply.\n");
    printf("The players hand has 5 cards, 4 are copper and 1 is a Feast.\n");
    printf("For this test, the user chooses a smithy card to obtain.\n");
    printf("Copy smithy count before cardEffect.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int smithyNumber = testGS.supplyCount[smithy];
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = feast;
    testGS.hand[0][1] = copper;
    testGS.hand[0][2] = copper;
    testGS.hand[0][3] = copper;
    testGS.hand[0][4] = copper;
    
    cardEffect(feast, smithy, 0, 0, &testGS, 0, 0);
    
    printf("The supply count should be 1 less than originally started.\n");
    printf("Actual Value: %d\n", testGS.supplyCount[smithy]);
    asserttrue(testGS.supplyCount[smithy], (smithyNumber - 1));
    
    //TEST 4 - Check affect on other players
    
    feastBool = 1; //Reset feast bool
    
    printf("TEST 4 - Feast gains a card but does not affect other players.\n");
    printf("For this test, the user chooses a village card to obtain.\n");
    printf("Copy Player 2 deck, hand, and disgard counts before test.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int discard2 = testGS.discardCount[1];
    int deck2 = testGS.deckCount[1];
    int hand2 = testGS.handCount[1];
    
    testGS.discardCount[0] = 0;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = feast;
    testGS.hand[0][1] = copper;
    testGS.hand[0][2] = copper;
    testGS.hand[0][3] = copper;
    testGS.hand[0][4] = copper;
    
    cardEffect(feast, village, 0, 0, &testGS, 0, 0);
    
    printf("The deck, hand, and disgard counts for player 2 shoudld be unchanged.\n");
    
    if(discard2 != testGS.discardCount[1])
    {
        feastBool = 0;
    }
    
    if(deck2 != testGS.deckCount[1])
    {
        feastBool = 0;
    }
    
    if(hand2 != testGS.handCount[1])
    {
        feastBool = 0;
    }
    
    asserttrue(feastBool, 1);
    
    
    return 0;
}

