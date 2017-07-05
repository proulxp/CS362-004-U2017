#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h> //Added to silence warnings
#include <stdlib.h> //Added to silence warnings

#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *post) {
  int r;
    
  r = drawCard (p, post);
    
    assert(r == 0); //Added to silence warnings
    
    return 0;
}

int main () {
    
    //Removed r, deskCount, discardCount, and handCount to silence warnings.
  int i, n, p;
    

    //Removed to silene warnings
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
    p = floor(Random() * 1000);
    checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  exit(0);
}
