/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/27/2017
 
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
#include <math.h>

//GLOBAL VARIABLE - Used to keep track of total failing tests during testing
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


/*********************************************************************
 
 ** Description: An oracle function called checkSmithyCard() this function
 checks the execution of the smithy card using a set of random inputs
 in the passed game state.
 
 Referenced: checkDrawCard() in testDrawCard.c
 
 *********************************************************************/
int checkSmithyCard(int playerIndex, int testHandPos, struct gameState *afterState) {
    
    //New game state for comparision
    struct gameState beforeState;
    
    //Chooses current players tern based on fed player index
    afterState->whoseTurn = playerIndex;
    
    //Randomly selects game states played card count
    afterState->playedCardCount = floor(Random() * MAX_HAND);
    
    //Copies before and after game state for comparison
    memcpy (&beforeState, afterState, sizeof(struct gameState));
    
    //Call cardEffect on smithy card
    cardEffect(smithy, 0, 0, 0, afterState, testHandPos, 0);
    
    int index = 0;  //Index for 3 card draws
    
    //Loop to simulate drawing three cards on before state
    for(index = 0; index < 3; index++)
    {
        //If the card has cards in the deck
        if (beforeState.deckCount[playerIndex] > 0)
        {
            //Increment hand count
            beforeState.handCount[playerIndex]++;
            
            //Take top card from deck
            beforeState.hand[playerIndex][beforeState.handCount[playerIndex]-1] = beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1];
            
            //Decrement deck count
            beforeState.deckCount[playerIndex]--;
            
        }
        else if (beforeState.discardCount[playerIndex] > 0) //If the player has no cards in deck simulate discard draw
        {
            //Copies over shuffled state from after state
            memcpy(beforeState.deck[playerIndex], afterState->deck[playerIndex], sizeof(int) * beforeState.discardCount[playerIndex]);
            memcpy(beforeState.discard[playerIndex], afterState->discard[playerIndex], sizeof(int)*beforeState.discardCount[playerIndex]);
            
            //Prevents bug from discard mechanic from not catching discard from hand position
            if(index == 2)
            {
                beforeState.hand[playerIndex][beforeState.handCount[playerIndex]] = afterState->hand[playerIndex][testHandPos];
            }
            else
            {
               beforeState.hand[playerIndex][beforeState.handCount[playerIndex]] = afterState->hand[playerIndex][beforeState.handCount[playerIndex]];
            }
            
            //Updates hand count, deck count, and discard count
            beforeState.handCount[playerIndex]++;
            beforeState.deckCount[playerIndex] = beforeState.discardCount[playerIndex]-1;
            beforeState.discardCount[playerIndex] = 0;
        }
        

    }
    

    //Simulate Discard
    beforeState.playedCards[beforeState.playedCardCount] = beforeState.hand[playerIndex][testHandPos];
    beforeState.playedCardCount++;
    
    //set played card to -1
    beforeState.hand[playerIndex][testHandPos] = -1;
    
    //remove card from player's hand
    if ( testHandPos == (beforeState.handCount[playerIndex] - 1) ) 	//last card in hand array is played
    {
        //reduce number of cards in hand
        beforeState.handCount[playerIndex]--;
    }
    else
    {

        //replace discarded card with last card in hand
        beforeState.hand[playerIndex][testHandPos] = beforeState.hand[playerIndex][ (beforeState.handCount[playerIndex] - 1)];
        //set last card to -1
        beforeState.hand[playerIndex][beforeState.handCount[playerIndex] - 1] = -1;
        //reduce number of cards in hand
        beforeState.handCount[playerIndex]--;
    }
    
    //Compare memory size of before and after state
    asserttrue(memcmp(&beforeState, afterState, sizeof(struct gameState)), 0);
    
    return 0;
}

int main () {
    

    int index;  //Index for cycle game state generation
    int numTests;   //Index for number of tests
    int totalPlayers;   //Holds total number of players 2-4
    int testHandPos;    //Random hand position chosen from total hand count.
    int randomizer;     //Random integer from 0 500 to seed game.
    int playerIndex;    //Random player index to test checkSmithyCard()
    
    clock_t t1, t2;  //Initialize time variables
    
    //Seeds supply with chosen cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    struct gameState GS;
    
    printf ("TESTING SMITHY CARD.\n");

    //Based off of testDrawCard.c
    SelectStream(2);
    PutSeed(3);
    
    t1 = clock();
    
    //Cycles through test cases
    for (numTests = 0; numTests < 2000; numTests++) {
        for (index = 0; index < sizeof(struct gameState); index++) {
            ((char*)&GS)[index] = floor(Random() * 256);
        }
        
        //Random total player count from 2 to 4
        totalPlayers = floor(Random() * 3) + 2;
        
        //Random int from 0 to 500
        randomizer = floor(Random() * 500);
        
        //Sets up game state
        initializeGame(totalPlayers, k, randomizer, &GS);
        
        //Choose random player index based on total players
        playerIndex = floor(Random() * totalPlayers);
        
        GS.deckCount[playerIndex] = floor(Random() * MAX_DECK);     //Random deck Count
        GS.discardCount[playerIndex] = floor(Random() * MAX_DECK);  //Random discard Count
        GS.handCount[playerIndex] = floor(Random() * MAX_HAND);     //Random hand Count
    
        
        //Sets passed handposition to a random position in players current hand
        testHandPos = floor(Random() * GS.handCount[playerIndex]);
        
        printf("Testing Player Index: %d, DeckCount: %d, DiscardCount: %d, HandCount: %d\n", playerIndex, GS.deckCount[playerIndex], GS.discardCount[playerIndex], GS.handCount[playerIndex]);
        
        checkSmithyCard(playerIndex, testHandPos, &GS);
    }
    
    t2 = clock();
    
    
    //Output statements to the user.
    if(failCount == 0)
    {
      printf ("ALL TESTS PASSED\n");
    }
    else
    {
      printf ("THERE WERE FAILURES\n");
    }
    
    printf("Number of Failures: %d\n", failCount);
    
    //Referenced: https://stackoverflow.com/questions/1083142/what-s-the-correct-way-to-use-printf-to-print-a-clock-t
    printf("The random tester ran in (sec): %Lf\n", ((long double)(t2 - t1))/CLOCKS_PER_SEC);

    
    exit(0);
    
    return 0;
}
