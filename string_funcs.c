#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * to_Lowercase makes all of the uppercase letters
 * in a string to lowercase and stores the result
 * in another string/character array.
 * @param string - the string to turn to lowercase
 * @param lower - the string in which to store
 *                the lowercase version of string
*/
void
to_Lowercase (char string[],
              char lower[])
{
    // local variable declaration
    int string_Length; // the length of the string to lowercase
    int i;             // indexing variable to be used in later looping

    string_Length = (int) strlen (string); // initialization of string length

    // loops through string and stores the lowercase
    // version of each character (if applicable) in 
    // lower
    for (i = 0; i < string_Length; i++)
        if (string[i] >= 'A' && string[i] <= 'Z')
            lower[i] = string[i] - 'A' + 'a';
        else
            lower[i] = string[i];
}
/**
 * substring_Search sees if a string is inside of
 * another string.
 * @param search_Area - string to search in
 * @param find - string to find in search_Area
*/
boolean
substring_Search (char search_Area[], 
                  char find[])
{
    // local variable declarations
    boolean found;       // represents if the substring has been found
    boolean discrepancy; // represents if a discrepancy has been found which makes it
                         // not a substring

    int i;                  // index variable for later looping
    int j;                  // index variable for later looping
    int find_Length;        // length of the substring to find
    int search_Area_Length; // length of the string to search in

    char character_From_Search_Area; // character in the string to search in
    char character_From_Find;        // character in the substring to search for

    find_Length = (int) strlen(find); // initialization of substring length
    search_Area_Length = (int) strlen (search_Area); // initialization of search string length

    // assume the substring has not been found yet
    found = FALSE;

    // proceeds only if the substring is smaller than
    // the string itself
    if (find_Length <= search_Area_Length)
    {
        // loops through the possible places the substring could be within
        // the string; stops when it is found
        for (i = 0; i < search_Area_Length - find_Length + 1 && !found; i++)
        {
            j = 0; // initialization of indexing variable

            // assume there are no discrepancies
            discrepancy = FALSE;

            // checks if the substring and the string slice 
            // is equal; stops when it finds a discrepancy
            while (j < find_Length && discrepancy == FALSE)
            {
                // record the first character of the string slice
                // as an uppercase character
                character_From_Search_Area = search_Area[i+j];
                if (character_From_Search_Area >= 'a' &&
                    character_From_Search_Area <= 'z')
                    character_From_Search_Area = character_From_Search_Area - 'a' + 'A';
                
                // record the first character of the substring
                // as an uppercase character
                character_From_Find = find[j];
                if (character_From_Find >= 'a' &&
                    character_From_Find <= 'z')
                    character_From_Find = character_From_Find - 'a' + 'A';

                // flags discrepancies and continues if there are not any
                if (character_From_Search_Area != character_From_Find)
                    discrepancy = TRUE;
                else j++;
            }

            // says the substring is found if there are no discrepancies
            if (discrepancy == FALSE)
                found = TRUE;
        }
    }
    
    return found;
}
