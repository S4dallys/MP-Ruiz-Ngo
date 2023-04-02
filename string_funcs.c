#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

void
to_Lowercase (char string[],
              char lower[])
{
    int string_Length;
    int i;
    string_Length = (int) strlen(string);
    for (i = 0; i < string_Length; i++)
        if (string[i]>='A'&&string[i]<='Z')
            lower[i] = string[i] - 'A' + 'a';
        else
            lower[i] = string[i];
}

boolean
substring_Search (char search_area[], 
                  char find[])
{
    boolean found;
    boolean discrepancy;
    int i;
    int j;
    int find_Length = (int) strlen(find);
    int search_Area_Length = (int) strlen (search_area);

    found = FALSE;

    if (find_Length <= search_Area_Length)
    {
        for (i = 0; i < search_Area_Length - find_Length + 1 && !found; i++)
        {
            j = 0;
            discrepancy = FALSE;
            while (j < find_Length && discrepancy == FALSE)
            {
                if (search_area[i+j] != find[j])
                    discrepancy = TRUE;
                else j++;
            }
            if (discrepancy == FALSE)
                found = TRUE;
        }
    }
    return found;
}
