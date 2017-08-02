/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the function gaincard()
 
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
    int returnedGain = 0;
 
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (gainCard) ----------------\n");
    printf("Note: Please see note in report regarding return value testing versus state testing. \n\n");
    
    //TEST 1 - Card is not used in the game
    
    printf("TEST 1 - Try gaining a card that is not in the current game\n");
    printf("The gainCard function is run by trying to add feast (not in this game)\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    returnedGain = gainCard(feast, &testGS, 0, 0);
    
    printf("gainCard should return -1\n");
    asserttrue(-1, returnedGain);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 2 - Supply for gained card is 0
    
    printf("TEST 2 - Try gaining a card that has supply of 0\n");
    printf("The gainCard function is run by trying to add mine which has 0 supply count\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.supplyCount[mine] = 0;
    
    returnedGain = gainCard(mine, &testGS, 0, 0);
    
    printf("gainCard should return -1\n");
    asserttrue(-1, returnedGain);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 3 - Supply is decreased after gain
    
    printf("TEST 3 - Check if supply is decreased by one after gain\n");
    printf("The gainCard function is run using mine that has a starting card count of 5\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.supplyCount[mine] = 5;
    
    gainCard(mine, &testGS, 0, 0);
    
    printf("Supply count should now have 4 mine cards remaining.\n");
    asserttrue(4, testGS.supplyCount[mine]);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 4 - Check flag to see if card is added to discard
    
    printf("TEST 4 - Check if flag 0 sends card to discard\n");
    printf("The gainCard function is run using adventurer\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int preDiscard = testGS.discardCount[0];
    
    gainCard(adventurer, &testGS, 0, 0);
    
    printf("The next card in the top of the discard array should now be adventurer.\n");
    asserttrue(adventurer, testGS.discard[0][preDiscard]);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 5 - Check flag to see if card is added to deck
    
    printf("TEST 5 - Check if flag 1 sends card to deck\n");
    printf("The gainCard function is run using embargo\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int preDeck = testGS.deckCount[0];
    
    gainCard(embargo, &testGS, 1, 0);
    
    printf("The next card in the top of the deck array should now be embargo.\n");
    asserttrue(embargo, testGS.deck[0][preDeck]);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 6 - Check flag to see if card is added to hand
    
    printf("TEST 6 - Check if flag 2 sends card to hand\n");
    printf("The gainCard function is run using village\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int preHand = testGS.handCount[0];
    
    gainCard(village, &testGS, 2, 0);
    
    printf("The next card in the top of the hand array should now be village.\n");
    asserttrue(village, testGS.hand[0][preHand]);
    
    returnedGain = 0; //Reset returnedGain
    
    //TEST 7 - Check if gainCard increases discardCount, deckCount, and handCount
    
    printf("TEST 7 - Check if gainCard increases discardCount, deckCount, and handCount\n");
    printf("The gainCard function is run once with each of the three flags.\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    int boolTrue = 1;
    
    preDiscard = testGS.discardCount[0];
    preDeck = testGS.deckCount[0];
    preHand = testGS.handCount[0];
    
    gainCard(village, &testGS, 0, 0);
    gainCard(embargo, &testGS, 1, 0);
    gainCard(adventurer, &testGS, 2, 0);
    
    if(testGS.discardCount[0] != (preDiscard + 1))
    {
        boolTrue = 0;
    }
    
    if(testGS.deckCount[0] != (preDeck + 1))
    {
        boolTrue = 0;
    }
    
    if(testGS.handCount[0] != (preHand + 1))
    {
        boolTrue = 0;
    }
    
    printf("A boolean is set true (1) only if all three counts are increased by 1.\n");
    asserttrue(1, boolTrue);

    
    return 0;
}
