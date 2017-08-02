/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/27/2017
 
 ** Description: Random tester for the Adventurer Card
 
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
 
 ** Description: An oracle function called checkAdventruerCard() this function
 checks the execution of the adventurer card using a set of random inputs
 in the passed game state.
 
 Referenced: checkDrawCard() in testDrawCard.c
 
 *********************************************************************/
int checkAdventurerCard(int playerIndex, int testHandPos, struct gameState *afterState) {
    
    //New game state for comparision
    struct gameState beforeState;
    
    //Chooses current players tern based on fed player index
    afterState->whoseTurn = playerIndex;
    
    //Copies before and after game state for comparison
    memcpy (&beforeState, afterState, sizeof(struct gameState));
    
    //Call cardEffect on adventurer card
    cardEffect(adventurer, 0, 0, 0, afterState, testHandPos, 0);
    
    int treasureCount = 0;  //Logs acquired treasure cards
    int wasteCards[500];    //Stores cards to send to discard
    int wasteCount = 0;     //Index for wastCards[] array
    
    //Cycle until two treasure cards are found
    while(treasureCount < 2)
    {
        //If there are cards in the deck
        if (beforeState.deckCount[playerIndex] > 0)
        {
            //Take top card from deck if a treasure card
            if(beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1] == copper || beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1] == silver || beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1] == gold)
            {
               beforeState.handCount[playerIndex]++;
               beforeState.hand[playerIndex][beforeState.handCount[playerIndex]-1] = beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1];
                
                treasureCount++;
            }
            else    //Store the none treasure card in the waste pile
            {
                wasteCards[wasteCount] = beforeState.deck[playerIndex][beforeState.deckCount[playerIndex]-1];
                wasteCount++;
            }
            
            //Decrement deck count
            beforeState.deckCount[playerIndex]--;
            
        }
        else if (beforeState.discardCount[playerIndex] > 0) //If the player has no cards in deck simulate discard draw
        {
            //Copies over shuffled state from after state
            memcpy(beforeState.deck[playerIndex], afterState->deck[playerIndex], sizeof(int) * beforeState.discardCount[playerIndex]);
            memcpy(beforeState.discard[playerIndex], afterState->discard[playerIndex], sizeof(int)*beforeState.discardCount[playerIndex]);
            
            //Add discarded card from afterState to beforeState
            wasteCards[wasteCount] = afterState->discard[playerIndex][(afterState->discardCount[playerIndex])- 1 -wasteCount];
            wasteCount++;
            
            
            
            //Updates hand count, deck count, and discard count
            beforeState.deckCount[playerIndex] = beforeState.discardCount[playerIndex]-1;
            beforeState.discardCount[playerIndex] = 0;
        }
    }
    
    //Transfer waste cards back to discard
    int index3 = 0;
    for(index3 = wasteCount-1; index3 >= 0; index3--)
    {
        beforeState.discard[playerIndex][beforeState.discardCount[playerIndex]] = wasteCards[index3];
        beforeState.discardCount[playerIndex]++;
        
    }
    
    
    //Compare memory size of before and after state
    asserttrue(memcmp(&beforeState, afterState, sizeof(struct gameState)), 0);
    
    return 0;
}

int main () {
    
    
    int index;  //Index for cycle game state generation
    int numTests;   //Index for number of tests
    
    
    clock_t t1, t2;  //Initialize time variables
    
    //Seeds supply with chosen cards
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    struct gameState GS;

    
    printf ("TESTING ADVENTURER CARD.\n");
    
    //Based off of testDrawCard.c
    SelectStream(2);
    PutSeed(3);
    
    
    t1 = clock();
    
    //Cycles through test cases
    for (numTests = 0; numTests < 4000; numTests++) {
        for (index = 0; index < sizeof(struct gameState); index++) {
            ((char*)&GS)[index] = floor(Random() * 256);
        }
        
        
        int totalPlayers = 0;   //Holds total number of players 2-4
        int testHandPos = 0;    //Random hand position chosen from total hand count.
        int randomizer = 0;     //Random integer from 0 500 to seed game.
        int playerIndex = 0;    //Random player index to test checkAdventurerCard()
        
        
        //Random total player count from 2 to 4
        totalPlayers = floor(Random() * 3) + 2;
        
        //Random int from 0 to 500
        randomizer = floor(Random() * 500);
        
        //Sets up game state
        initializeGame(totalPlayers, k, randomizer, &GS);
        
        //Choose random player index based on total players
        playerIndex = floor(Random() * totalPlayers);
        
        GS.deckCount[playerIndex] = floor(Random() * 500);     //Random deck Count
        
        
        //Ensure that if the test deck count is below 10 that the discard count is above 10
        if(GS.deckCount[playerIndex] < 10)
        {
            GS.discardCount[playerIndex] = (floor(Random() * (500 - GS.deckCount[playerIndex] - 10))) + 10;
        }
        else
        {
           GS.discardCount[playerIndex] = (floor(Random() * (500 - GS.deckCount[playerIndex])));  //Random discard Count
        }
        
        
        //Booleans for random treasure index generation
        int sameBool1 = 0;
        int sameBool2 = 0;
        int sameBool3 = 0;
        int sameBool4 = 0;
        int sameBool5 = 0;

        //Store treasure indexes
        int copperIndex1 = floor(Random() * GS.deckCount[playerIndex]);
        int copperIndex2 = 0;
        int silverIndex1 = 0;
        int silverIndex2 = 0;
        int goldIndex1 = 0;
        int goldIndex2 = 0;
   
        //Randomly places 2 copper, 2 silver and 2 gold cards in deck.
        if(GS.deckCount[playerIndex] > 6)
        {
            while(sameBool1 == 0)
            {
                copperIndex2 = floor(Random() * GS.deckCount[playerIndex]);
                
                if(copperIndex2 != copperIndex1)
                {
                    sameBool1 = 1;
                }
            }
            while(sameBool2 == 0)
            {
                silverIndex1 = floor(Random() * GS.deckCount[playerIndex]);
                
                if(silverIndex1 != copperIndex1 && silverIndex1 != copperIndex2)
                {
                    sameBool2 = 1;
                }
            }
            while(sameBool3 == 0)
            {
                silverIndex2 = floor(Random() * GS.deckCount[playerIndex]);
                
                if(silverIndex2 != copperIndex1 && silverIndex2 != copperIndex2 && silverIndex2 != silverIndex1)
                {
                    sameBool3 = 1;
                }
            }
            while(sameBool4 == 0)
            {
                goldIndex1 = floor(Random() * GS.deckCount[playerIndex]);
                
                if(goldIndex1 != copperIndex1 && goldIndex1 != copperIndex2 && goldIndex1 != silverIndex1 && goldIndex1 != silverIndex2)
                {
                    sameBool4 = 1;
                }
            }
            while(sameBool5 == 0)
            {
                goldIndex2 = floor(Random() * GS.deckCount[playerIndex]);
                
                if(goldIndex2 != copperIndex1 && goldIndex2 != copperIndex2 && goldIndex2 != silverIndex1 && goldIndex2 != silverIndex2 && goldIndex2 != goldIndex1)
                {
                    sameBool5 = 1;
                }
            }
           
            GS.deck[playerIndex][copperIndex1] = copper;
            GS.deck[playerIndex][copperIndex2] = copper;
            GS.deck[playerIndex][silverIndex1] = silver;
            GS.deck[playerIndex][silverIndex2] = silver;
            GS.deck[playerIndex][goldIndex1] = gold;
            GS.deck[playerIndex][goldIndex2] = gold;
            
        }
        
        GS.handCount[playerIndex] = floor(Random() * MAX_HAND);     //Random hand Count
        
        
        //Conditional to ensure initialized treasure cards in every game are in either the deck or discard
        if(GS.deckCount[playerIndex] < 10)
        {   int index2 = 0;
            for(index2 = 0; index2 < 10; index2++)
            {
                GS.discard[playerIndex][index2] = GS.deck[playerIndex][index2];
            }
        }
        
        //Sets passed handposition to a random position in players current hand
        testHandPos = floor(Random() * GS.handCount[playerIndex]);
        
        printf("Testing Player Index: %d, DeckCount: %d, DiscardCount: %d, HandCount: %d\n", playerIndex, GS.deckCount[playerIndex], GS.discardCount[playerIndex], GS.handCount[playerIndex]);
        
        shuffle(playerIndex, &GS);
        
        GS.playedCardCount = floor(Random() * MAX_HAND);
        
        checkAdventurerCard(playerIndex, testHandPos, &GS);
        
        
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
