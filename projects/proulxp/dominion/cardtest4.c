/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the Village Card
 
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
    int villageBool = 1;

    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, feast};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (Village Card) ----------------\n");
    
    //TEST 1 - Check gain card mechanic
    
    printf("TEST 1 - Village pulls 1 card from deck.\n");
    printf("The players hand has 5 cards, all are village cards.\n");
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
    testGS.hand[0][0] = village;
    testGS.hand[0][1] = village;
    testGS.hand[0][2] = village;
    testGS.hand[0][3] = village;
    testGS.hand[0][4] = village;
    
    cardEffect(village, 0, 0, 0, &testGS, 0, 0);
    
    printf("After playing the village card the user should have 5 cards in their hand. 4 Village cards and 1 Gold Card\n");
    
    if(testGS.handCount[0] != 5)
    {
        villageBool = 0;
    }
    
    if(testGS.hand[0][0] != gold)
    {
        villageBool = 0;
    }
    
    asserttrue(villageBool, 1);
    
    villageBool = 1; //Reset villageBool
    
    //TEST 2 - Check discard mechanic
    
    printf("TEST 2 - Village properly leaves hand into played pile after being played.\n");
    printf("The players hand has 5 cards, all are village cards.\n");
    printf("The players played deck starts empty.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.playedCardCount = 0;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = village;
    testGS.hand[0][1] = village;
    testGS.hand[0][2] = village;
    testGS.hand[0][3] = village;
    testGS.hand[0][4] = village;
    
    cardEffect(village, 0, 0, 0, &testGS, 0, 0);
    
    printf("After playing the village card the user should have 1 played card and that is a village.\n");
    
    if(testGS.playedCardCount != 1)
    {
        villageBool = 0;
    }
    
    if(testGS.playedCards[0] != village)
    {
        villageBool = 0;
    }
    
    asserttrue(villageBool, 1);
    
    villageBool = 1; //Reset villageBool
    
    //TEST 3 - Check action mechanic
    
    printf("TEST 3 - Village properly adds +2 action points.\n");
    printf("The players hand has 5 cards, all are village cards.\n");
    printf("The player starts with 1 action point.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.numActions = 1;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = village;
    testGS.hand[0][1] = village;
    testGS.hand[0][2] = village;
    testGS.hand[0][3] = village;
    testGS.hand[0][4] = village;
    
    cardEffect(village, 0, 0, 0, &testGS, 0, 0);
    
    printf("After playing the village card the user should have 2 actions points remaining.\n");

    printf("Actual Value: %d\n", testGS.numActions);
    asserttrue(testGS.numActions, 2);
    
    //TEST 4 - Village does not affect supply deck
    
    villageBool = 1;
    
    printf("TEST 4 - Village does not pull from supply deck.\n");
    printf("The players hand has 5 cards, all are village cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    printf("Saving counts from vicotry piles and kingdom piles before playing Village.\n");
    
    int saveCount[27];
    int index = 0;
    
    for(index = 0; index < 28; index++)
    {
        saveCount[index] = testGS.supplyCount[index];
    }
    
    
    testGS.numActions = 1;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = village;
    testGS.hand[0][1] = village;
    testGS.hand[0][2] = village;
    testGS.hand[0][3] = village;
    testGS.hand[0][4] = village;
    
    cardEffect(village, 0, 0, 0, &testGS, 0, 0);
    
    printf("The saved counts should match the original counts.\n");
    
    index = 0;
    
    for(index = 0; index < 28; index++)
    {
        if(saveCount[index] != testGS.supplyCount[index])
        {
            villageBool = 0;
        }
    }
    
    asserttrue(villageBool, 1);
    
    //TEST 5 - Village does not affect other players
    
    villageBool = 1;
    
    printf("TEST 5 - Village does not affect other players.\n");
    printf("Player 1 has no affect on Player 2's deck counts, hand counts, and discard counts.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    printf("Saving player 2 counts before player 1 plays.\n");
    int discard2 = testGS.discardCount[1];
    int deck2 = testGS.deckCount[1];
    int hand2 = testGS.handCount[1];
    
    
    testGS.numActions = 1;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = gold;
    testGS.deck[0][1] = gold;
    testGS.deck[0][2] = gold;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = village;
    testGS.hand[0][1] = village;
    testGS.hand[0][2] = village;
    testGS.hand[0][3] = village;
    testGS.hand[0][4] = village;
    
    cardEffect(village, 0, 0, 0, &testGS, 0, 0);
    
    printf("The saved counts should match the original counts.\n");
    
    if(discard2 != testGS.discardCount[1])
    {
        villageBool = 0;
    }
    
    if(deck2 != testGS.deckCount[1])
    {
        villageBool = 0;
    }
    
    if(hand2 != testGS.handCount[1])
    {
        villageBool = 0;
    }
    
    
    asserttrue(villageBool, 1);
    
    
    return 0;
}


