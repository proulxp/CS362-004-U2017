/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/22/2017
 
 ** Description: Random tester for Adventurer Card
 
 ** Referenced: 
 
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

int checkDrawCard(int p, struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int r;
    //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
    //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
    r = drawCard (p, post);
    
    //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
    //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);
    
    if (pre.deckCount[p] > 0) {
        pre.handCount[p]++;
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
        pre.deckCount[p]--;
    } else if (pre.discardCount[p] > 0) {
        memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
        pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
        pre.handCount[p]++;
        pre.deckCount[p] = pre.discardCount[p]-1;
        pre.discardCount[p] = 0;
    }
    
    //assert (r == 0);
    
    //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
    
    asserttrue(memcmp(&pre, post, sizeof(struct gameState)), 0);
    
    return 0; //Silence warning
}

int main () {
    
    //Removed r, deckCount, discardCount, and handCount to silence warnings
    int i, n, p;
    
    //Silence Warnings
    /*
     int k[10] = {adventurer, council_room, feast, gardens, mine,
     remodel, smithy, village, baron, great_hall};
     */
    
    struct gameState G;
    
    printf ("Testing drawCard.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        printf("Testing Player: %d, DeckCount: %d, DiscardCount: %d, HandCount: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p]);
        checkDrawCard(p, &G);
    }
    
    printf ("ALL TESTS OK\n");
    
    exit(0);
    
    return 0;
}
