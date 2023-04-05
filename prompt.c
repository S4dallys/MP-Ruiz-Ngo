#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * clean_Input_Stream removes all characters that exist
 * in the input stream up to and including the first new
 * line it encounters.
*/
void 
clean_Input_Stream ()
{
    // local variable declaration
    char garbage;

    // accepts characters up to and including the first
    // end line it sees
    do
    {
        scanf("%c", &garbage);

    } while (garbage != '\n');
}

/**
 * prompt_Int displays a provided prompt and accepts an
 * integer from the user.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
*/
void
prompt_Int (char   prompt[],
            int *  address)
{
    // local variable declaration
    char garbage;

    // shows prompt parameter
    printf("\t%s", prompt);

    // gets an integer input from the input stream
    scanf("%d", address);

    // removes new line character from stream
    scanf("%c", &garbage);
}

/**
 * prompt_Long_Long displays a provided prompt and accepts 
 * a number of data type long long from the user.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
*/
void
prompt_Long_Long (char         prompt[],
                  long long *  address)
{
    // local variable declaration
    char garbage;
    
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a long long input from the input stream
    scanf("%I64d", address);

    // removes new line character from stream
    scanf("%c", &garbage);
}

/**
 * prompt_Double displays a provided prompt and accepts a
 * double from the user.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
*/
void
prompt_Double (char      prompt[],
               double *  address)
{
    // local variable declaration
    char garbage;

    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a double input from the input stream
    scanf("%lf", address);

    // removes new line character from input stream
    scanf("%c", &garbage);
}

/**
 * prompt_Char displays a provided prompt and accepts a
 * character from the user.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
*/
void
prompt_Char (char    prompt[],
             char *  address)
{
    // local variable declaration
    char garbage;
    
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a character input from the input stream
    scanf("%c", address);

    // removes new line character from input stream
    scanf("%c", &garbage);
}

/**
 * prompt_Int displays a provided prompt and accepts a
 * a number of characters from the users and stores it
 * as a string.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
 * @param limit - the maximum number of characters that the
 *                function will accept
*/
void
prompt_StringN (char  prompt[],
                char  address[],
                int   limit)
{
    // local variable declaration
    char  input;
    int   index;

    index = 0;
    
    // shows prompt parameter
    printf("\t%s", prompt);

    // accept characters until it reaches the limit
    // or it encounters a new line and places them
    // in an array
    do
    {
        scanf("%c", &input);

        address[index] = input;

        if (input != '\n')
            index++;

    } while (input != '\n' && index < limit);

    // cleans input stream in the case of excess input
    if (index >= limit && address[index] != '\n')
        clean_Input_Stream();

    // replace the new line or the last character in the
    // array with a null byte
    address[index] = 0;
}
