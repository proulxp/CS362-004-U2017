/*********************************************************************
 
 ** Authors: Phillip Proulx
 
 ** Date: 07/21/2017
 
 ** Description: Random tester for Quiz 2.
 
 *********************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <limits.h>


char inputChar()
{
    // TODO: rewrite this function
    
    //Assigns a random character from the range of 0 to 128
    //Referenced: Piazza Post @105
    char randomChar = rand() % (CHAR_MAX + 1);
    
    return randomChar;
}

char *inputString()
{
    // TODO: rewrite this function
    //Holds random return string
    static char returnString[6];
    
    //Assigned a random number from 0 to 27
    int rand1, rand2, rand3, rand4, rand5, rand6;
    
    rand1 = rand2 = rand3 = rand4 = rand5 = rand6 = 0;
    
    //Possible pool of characters
    char pool[] = "rest\0";
    
    //Assign variables random number
    rand1 = rand() % (6);
    rand2 = rand() % (6);
    rand3 = rand() % (6);
    rand4 = rand() % (6);
    rand5 = rand() % (6);
    rand6 = rand() % (6);
    
    
    
    //Assign random characters from pool
    returnString[0] = pool[rand1];
    returnString[1] = pool[rand2];
    returnString[2] = pool[rand3];
    returnString[3] = pool[rand4];
    returnString[4] = pool[rand5];
    returnString[5] = pool[rand6];
    
    return returnString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
