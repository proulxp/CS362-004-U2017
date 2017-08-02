/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the function scoreFor()
 
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
    int returnedScore = 0;

    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (scoreFor) ----------------\n");
    printf("Note: Please see note in report regarding return value testing versus state testing. \n\n");
    
    //TEST 1 - Calculate Score for Player with entire deck in hand
    
    printf("TEST 1 - Calculating score with all cards in hand. 10 cards total\n");
    printf("The hand is made up of 2 curse, 2 estate, 2 duchy, 2 province, 1 great hall, and 1 gardens cards\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.handCount[0] = 10;
    testGS.hand[0][0] = curse;
    testGS.hand[0][1] = curse;
    testGS.hand[0][2] = estate;
    testGS.hand[0][3] = estate;
    testGS.hand[0][4] = duchy;
    testGS.hand[0][5] = duchy;
    testGS.hand[0][6] = province;
    testGS.hand[0][7] = province;
    testGS.hand[0][8] = great_hall;
    testGS.hand[0][9] = gardens;
    
    returnedScore = scoreFor(0, &testGS);
    
    printf("scoreFor should return 20\n");
    printf("Returned Value: %d\n", returnedScore);
    asserttrue(returnedScore, 20);
    
    returnedScore = 0; //Reset returnedScore
    
    //TEST 2 - Calculate Score for Player with deck split between hand, discard, and deck.
    
    printf("TEST 2 - Calculating score with cards split between hand, discard, and deck. 15 cards total\n");
    printf("The hand is made up of 2 estate cards, 2 curse cards, and a copper card.\n");
    printf("The discard is made up of 2 province cards and 3 silver cards.\n");
    printf("The deck is made up of 1 great hall, 1 smithy card, 1 duchy, and 2 gold cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = estate;
    testGS.hand[0][1] = estate;
    testGS.hand[0][2] = curse;
    testGS.hand[0][3] = curse;
    testGS.hand[0][4] = copper;
    
    testGS.discardCount[0] = 5;
    testGS.discard[0][0] = province;
    testGS.discard[0][1] = province;
    testGS.discard[0][2] = silver;
    testGS.discard[0][3] = silver;
    testGS.discard[0][4] = silver;
    
    testGS.deckCount[0] = 5;
    testGS.deck[0][0] = great_hall;
    testGS.deck[0][1] = smithy;
    testGS.deck[0][2] = duchy;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    
    returnedScore = scoreFor(0, &testGS);
    
    printf("scoreFor should return 16\n");
    printf("Returned Value: %d\n", returnedScore);
    asserttrue(returnedScore, 16);
    
    returnedScore = 0; //Reset returnedScore
    
    //TEST 3 - Calculate Score for Player with deck split between hand, discard, and deck with different amount of deck and discard amounts.
    
    printf("TEST 3 - Calculating score with cards split between hand, discard, and deck with different deck and discard amounts. 15 cards total\n");
    printf("The hand is made up of 2 estate cards, 2 curse cards, and a copper card.\n");
    printf("The discard is made up of 1 province card and 3 silver cards.\n");
    printf("The deck is made up of 1 great hall, 1 smithy card, 1 duchy, 1 province card, and 2 gold cards.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = estate;
    testGS.hand[0][1] = estate;
    testGS.hand[0][2] = curse;
    testGS.hand[0][3] = curse;
    testGS.hand[0][4] = copper;
    
    testGS.discardCount[0] = 4;
    testGS.discard[0][0] = province;
    testGS.discard[0][1] = silver;
    testGS.discard[0][2] = silver;
    testGS.discard[0][3] = silver;

    
    testGS.deckCount[0] = 6;
    testGS.deck[0][0] = great_hall;
    testGS.deck[0][1] = smithy;
    testGS.deck[0][2] = duchy;
    testGS.deck[0][3] = gold;
    testGS.deck[0][4] = gold;
    testGS.deck[0][5] = province;
    
    returnedScore = scoreFor(0, &testGS);
    
    printf("scoreFor should return 16\n");
    printf("Returned Value: %d\n", returnedScore);
    asserttrue(returnedScore, 16);
    
    returnedScore = 0; //Reset returnedScore
    
    //TEST 4 - Calculate Score for Player with no scoring cards
    
    printf("TEST 4 - Calculating score with all cards in hand and all are non point cards. 5 cards total\n");
    printf("The hand is made up of 5 copper cards\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = copper;
    testGS.hand[0][1] = copper;
    testGS.hand[0][2] = copper;
    testGS.hand[0][3] = copper;
    testGS.hand[0][4] = copper;
   
    
    returnedScore = scoreFor(0, &testGS);
    
    printf("scoreFor should return 0\n");
    printf("Returned Value: %d\n", returnedScore);
    asserttrue(returnedScore, 0);
    
    returnedScore = 0; //Reset returnedScore
    
    //TEST 5 - Calculate Score for Player with all curse cards
    
    printf("TEST 5 - Calculating score with all cards in hand and all are curse cards. 5 cards total\n");
    printf("The hand is made up of 5 curse cards\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.handCount[0] = 5;
    testGS.hand[0][0] = curse;
    testGS.hand[0][1] = curse;
    testGS.hand[0][2] = curse;
    testGS.hand[0][3] = curse;
    testGS.hand[0][4] = curse;
    
    
    returnedScore = scoreFor(0, &testGS);
    
    printf("scoreFor should return -5\n");
    printf("Returned Value: %d\n", returnedScore);
    asserttrue(returnedScore, -5);
    
    return 0;
}
