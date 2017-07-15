/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/15/2017
 
 ** Description: Unit tests for the function int isGameOver(struct gameState *state)
 
 ** Referenced: Provided previous student cardtest4.c code
 
 *********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

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
    int gameOver = 0;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    struct gameState GS;        //Original Game State
    struct gameState testGS;    //Modified Test Game State for comparision
    
    //Initialize original game for comparision
    initializeGame(playerNum, k, randomizer, &GS);
    
    printf("----------------- Testing Function (isGameOver) ----------------\n");
    printf("Note: Please see note in report regarding return value testing versus state testing. \n\n");
    
    //TEST 1 - Only Province Cards are Used Up
    
    printf("TEST 1 - All Province Cards are Used Up\n");
    
    //Copies fresh game state to test game state
    memcpy(&testGS, &GS, sizeof(struct gameState));
    
    testGS.supplyCount[province] = 0;
    gameOver = isGameOver(&testGS);
    
    printf("Province count set to 0 isGameOver should return 1\n");
    asserttrue(1, gameOver);
    
    gameOver = 0; //Resets gameOver
    
    //Test 2 - Two Supply Decks and all but 1 province card are used up
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 2 - Only 1 province card is left and only 2 supply decks are at 0\n");
    
    testGS.supplyCount[province] = 1;
    testGS.supplyCount[1] = 0;
    testGS.supplyCount[2] = 0;
    
    printf("isGameOver should return 0\n");
    
    gameOver = isGameOver(&testGS);
    asserttrue(0, gameOver);
    
    gameOver = 0; //Resets gameOver
    
    //Test 3 - Three supply decks are used up
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 3 - 3 random supply decks are set to 0\n");
    
    //Referenced: https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm
    time_t rTime;
    srand((unsigned) time(&rTime));
    
    int ran1, ran2, ran3;
    
    ran1 = ran2 = ran3 = 30;
    
    ran1 = rand() % 25;
    
    while(ran2 == ran1 || ran2 == ran3)
    {
      ran2 = rand() % 25;
    }
    
    do{
        ran3 = rand() % 25;
    }while(ran3 == ran1 || ran3 == ran2);

    
    testGS.supplyCount[ran1] = 0;
    testGS.supplyCount[ran2] = 0;
    testGS.supplyCount[ran3] = 0;
    
    printf("isGameOver should return 1\n");
    
    gameOver = isGameOver(&testGS);
    asserttrue(1, gameOver);
    
    gameOver = 0; //Resets gameOver
    
    //Test 4 - Province has 0 count and 3 random supply decks are set to 0
    memcpy(&testGS, &GS, sizeof(struct gameState));
    printf("TEST 4 - Province has 0 count and 3 random supply decks are set to 0\n");
    
    testGS.supplyCount[province] = 0;
    
    //Resets 3 random numbers
    ran1 = ran2 = ran3 = 30;
    
    ran1 = rand() % 25;
    
    while(ran2 == ran1 || ran2 == ran3)
    {
        ran2 = rand() % 25;
    }
    
    do{
        ran3 = rand() % 25;
    }while(ran3 == ran1 || ran3 == ran2);
    
    
    testGS.supplyCount[ran1] = 0;
    testGS.supplyCount[ran2] = 0;
    testGS.supplyCount[ran3] = 0;
    
    printf("isGameOver should return 1\n");
    
    gameOver = isGameOver(&testGS);
    asserttrue(1, gameOver);
    
    return 0;
}











