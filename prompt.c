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
    char garbage;

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
    char garbage;

    printf("\t%s", prompt);
    scanf("%d", address);
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
    char garbage;
    
    printf("\t%s", prompt);
    scanf("%I64d", address);
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
    char garbage;

    printf("\t%s", prompt);
    scanf("%lf", address);
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
    char garbage;
    
    printf("\t%s", prompt);
    scanf("%c", address);
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
    char  input;
    int   index;

    index = 0;
    
    printf("\t%s", prompt);

    do
    {
        scanf("%c", &input);

        address[index] = input;

        if (input != '\n')
            index++;

    } while (input != '\n' && index < limit);

    if (index >= limit && address[index] != '\n')
        clean_Input_Stream();

    address[index] = 0;
}
