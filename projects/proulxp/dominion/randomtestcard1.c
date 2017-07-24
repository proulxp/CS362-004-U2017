/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/22/2017
 
 ** Description: Random tester for Smithy Card
 
 ** Referenced: I referenced testDrawCard.c and Lecture 11.
 
 *********************************************************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int failCount = 0;

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
        failCount++;
    }
}


int checkSmithyCard(int numPlayer, int testHandPos, struct gameState *afterState) {
    
    struct gameState beforeState;
    
    afterState->whoseTurn = numPlayer;
    afterState->playedCardCount = floor(Random() * MAX_HAND);
    
    
    memcpy (&beforeState, afterState, sizeof(struct gameState));
    
    int state;

    
    
    state = cardEffect(smithy, 0, 0, 0, afterState, testHandPos, 0);
    
    int index = 0;
    int savedFinalCard = 0;

    
    for(index = 0; index < 3; index++)
    {
        if (beforeState.deckCount[numPlayer] > 0)
        {
            //Increase Hand Count by 3
            beforeState.handCount[numPlayer]++;
            
            beforeState.hand[numPlayer][beforeState.handCount[numPlayer]-1] = beforeState.deck[numPlayer][beforeState.deckCount[numPlayer]-1];
            
            beforeState.deckCount[numPlayer]--;
            
        }
        else if (beforeState.discardCount[numPlayer] > 0)
        {
            memcpy(beforeState.deck[numPlayer], afterState->deck[numPlayer], sizeof(int) * beforeState.discardCount[numPlayer]);
            memcpy(beforeState.discard[numPlayer], afterState->discard[numPlayer], sizeof(int)*beforeState.discardCount[numPlayer]);
            if(index == 2)
            {
                beforeState.hand[numPlayer][beforeState.handCount[numPlayer]] = afterState->hand[numPlayer][testHandPos];
            }
            else
            {
               beforeState.hand[numPlayer][beforeState.handCount[numPlayer]] = afterState->hand[numPlayer][beforeState.handCount[numPlayer]];
            }
            
            beforeState.handCount[numPlayer]++;
            beforeState.deckCount[numPlayer] = beforeState.discardCount[numPlayer]-1;
            beforeState.discardCount[numPlayer] = 0;
        }
        

    }
    

    //Simulate Discard
    beforeState.playedCards[beforeState.playedCardCount] = beforeState.hand[numPlayer][testHandPos];
    beforeState.playedCardCount++;
    
    //set played card to -1
    beforeState.hand[numPlayer][testHandPos] = -1;
    
    //remove card from player's hand
    if ( testHandPos == (beforeState.handCount[numPlayer] - 1) ) 	//last card in hand array is played
    {
        //reduce number of cards in hand
        beforeState.handCount[numPlayer]--;
    }
    else
    {

        //replace discarded card with last card in hand
        beforeState.hand[numPlayer][testHandPos] = beforeState.hand[numPlayer][ (beforeState.handCount[numPlayer] - 1)];
        //set last card to -1
        beforeState.hand[numPlayer][beforeState.handCount[numPlayer] - 1] = -1;
        //reduce number of cards in hand
        beforeState.handCount[numPlayer]--;
    }
    


    
    //asserttrue(state, 0);
    asserttrue(memcmp(&beforeState, afterState, sizeof(struct gameState)), 0);
    
    return 0;
}

int main () {
    
    //Removed r, deckCount, discardCount, and handCount to silence warnings
    int i;
    int n;
    int numPlayer;
    int testHandPos;
    int randomizer;
    
    
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    struct gameState GS;
    
    printf ("Testing drawCard.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 200000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&GS)[i] = floor(Random() * 256);
        }
        
        numPlayer = floor(Random() * 4);
        
        randomizer = floor(Random() * 500);
        
        initializeGame(numPlayer, k, randomizer, &GS);
        
        
        GS.deckCount[numPlayer] = floor(Random() * MAX_DECK);
        GS.discardCount[numPlayer] = floor(Random() * MAX_DECK);
        GS.handCount[numPlayer] = floor(Random() * MAX_HAND);
        
        //GS.deckCount[numPlayer] = 2;
        
        //Sets passed handposition to a random position in players current hand
        testHandPos = floor(Random() * GS.handCount[numPlayer]);
        
        printf("Testing Player: %d, DeckCount: %d, DiscardCount: %d, HandCount: %d\n", numPlayer, GS.deckCount[numPlayer], GS.discardCount[numPlayer], GS.handCount[numPlayer]);
        
        checkSmithyCard(numPlayer, testHandPos, &GS);
    }
    
    printf ("ALL TESTS OK\n");
    printf("Number of Failures: %d\n", failCount);
    
    exit(0);
    
    return 0;
}
