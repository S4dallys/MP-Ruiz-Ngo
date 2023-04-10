#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

boolean
is_Leap (int year);

int
give_Max_Days_In_Month (boolean is_Leap,
                        int     month);

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
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets an integer input from the input stream
    scanf("%d", address);

    // removes garbage input from stream
    clean_Input_Stream();
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
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a long long input from the input stream
    scanf("%I64d", address);

    // removes garbage input from stream
    clean_Input_Stream();
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
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a double input from the input stream
    scanf("%lf", address);

    // removes garbage input from stream
    clean_Input_Stream();
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
    // shows prompt parameter
    printf("\t%s", prompt);

    // gets a character input from the input stream
    scanf("%c", address);

    // removes garbage input from stream
    clean_Input_Stream();
}

/**
 * prompt_StringN displays a provided prompt and accepts a
 * a number of characters from the users and stores it
 * as a string.
 * @param prompt - a string that contains a message to the
 *                 user
 * @param address - a pointer to where the user input
 *                  will be stored
 * @param limit - the maximum number of characters that the
 *                function will accept
 * Precondition: Limit should be less than string length
*/
void
prompt_StringN (char  prompt[],
                char  address[],
                int   limit)
{
    // local variable declaration
    char  input; // temporary bin for character input
    int   index; // indexing value aiding in string storage

    index = 0; // initialization of indexing value
    
    // shows prompt parameter
    printf("\t%s", prompt);

    // accept characters until it reaches the limit
    // or it encounters a new line and places them
    // in an array
    do
    {
        // gets a character
        scanf("%c", &input);

        // records it into the destination string
        address[index] = input;

        // continues while there is no new line
        if (input != '\n')
            index++;

    // stops after reaching the limit or encountering a new line
    } while (input != '\n' && index < limit);

    // cleans input stream in the case of excess input
    if (index >= limit && address[index] != '\n')
        clean_Input_Stream();

    // replace the new line or the last character in the
    // array with a null byte
    address[index] = 0;
}

/**
 * prompt_Date prompts user for a date and creates a 
 * date structure.
 * @param date dateType pointer to set new dateType to
 * Precondition: Year must be greater than 0 and less than 10000
*/
void
prompt_Date (dateType* date)
{
    // local variable declaration
    boolean gave_Error;   // represents if user has given an error in a  data entry loop
    boolean gave_Valid;   // represents if user has given a valid input
    boolean is_Leap_Year; // represents if the date the user gave is a leap year

    int max_Days; // represents the maximum days a month could have, considering the year

    gave_Error = FALSE; // initialization of error-indicating value
    gave_Valid = FALSE; // initialization of sentinel value

    // loops until a valid year is given
    do 
    {
        // gives an error if user previously gave erroneous input
        if (gave_Error)
            printf("\tERROR: Invalid year.\n");

        // prompt for date year
        printf("\tInsert year (1 AD - 9999 AD): ");
        scanf("%d", &date -> year); // gets year

        // says that an erroneous input was given
        if (date -> year < 1 || date -> year > 9999)
            gave_Error = TRUE;
        
        // exits loop
        else
            gave_Valid = TRUE;

    } while (!gave_Valid);

    // checks if year is leap year
    is_Leap_Year = is_Leap(date -> year);

    gave_Error = FALSE; // initialization of error-indicating value
    gave_Valid = FALSE; // initialization of sentinel value

    // loops until a valid month is given
    do 
    {
        // gives an error if user previously gave erroneous input
        if (gave_Error)
            printf("\tERROR: Invalid month.\n");

        // prompt for date month
        printf("\tInsert month (1-12): ");
        scanf("%d", &date->month); // gets month

        // says that an erroneous input was given
        if (date -> month < 1 || date -> month > 12)
            gave_Error = TRUE;
        
        // exits the loop
        else
            gave_Valid = TRUE;
    } while (!gave_Valid);

    // sets max days in month based on year and month
    max_Days = give_Max_Days_In_Month(is_Leap_Year, date -> month);

    gave_Error = FALSE; // initialization of error-indicating value
    gave_Valid = FALSE; // initialization of sentinel value

    // loops until a valid day is given
    do
    {
        // gives an error if user previously gave erroneous input
        if (gave_Error)
            printf("\tERROR: Invalid date.\n");

        // prompt date day
        printf("\tInsert date (1-%d): ", max_Days);
        scanf("%d", &date->day); // gets day
        
        // says that an erroneous input was given
        if (date -> day < 1 || date -> day > max_Days)
            gave_Error = TRUE;

        // exits the loop
        else
            gave_Valid = TRUE;
            
    } while (!gave_Valid);
    
    // removes garbage input from stream
    clean_Input_Stream();
}
