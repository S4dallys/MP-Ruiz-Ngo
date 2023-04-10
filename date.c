#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * is_Leap checks if a year is a leap year or not.
 * @param year - the year we wish to know is a leap year or not
 * @return TRUE if it is a leap year; FALSE otherwise
*/
boolean
is_Leap (int year)
{
    // local variable declaration
    boolean flag; // shows if the year is a leap year or not

    // activates if the year is divisible by 4
    if (year % 4 == 0)
    {
        // activates if the year is divisible by 100
        if (year % 100 == 0)
        {
            // activates if the year is divisible by 400
            if (year % 400 == 0)
                flag = TRUE;

            // activates if the year is not divisible by 400
            else
                flag = FALSE;
        }

        // activates if the year is not divisible by 100
        else
            flag = TRUE;
    }

    // activates if the year is not divisible by 4
    else
        flag = FALSE;

    return flag;
}

/**
 * give_Max_Days_In_Month gives the maximum days in a month 
 * given a month and if it is a leap year.
 * @param is_Leap - boolean if the year is a leap year
 * @param month - integer representation of the month e.g. 
 *                1 for January
 * @return the maximum days of a given month and if its a 
 *         leap year or not
 * Precondition: Only months (1-12) are allowed.
*/
int
give_Max_Days_In_Month (boolean is_Leap,
                        int     month)
{
    // local variable declaration
    int max_Days;

    // does the maximum days of February
    if (month == 2)
    {
        // says the maximum days of February is 29 in a leap year
        if (is_Leap)
            max_Days = 29;
        // says the max days of February is 28 if not a leap year
        else max_Days = 28;
    }

    // does the maximums of other months
    else
    {
        switch (month)
        {
            case 4: // for April
            case 6: // for June
            case 9: // for September
            case 11: // for November
                max_Days = 30; // all have a maximum of 30 days
                break;
            default:
                max_Days = 31; // the rest unmentioned have 31
                break;
        }
    }

    return max_Days;
}

/**
 * compare_Date compares the dates of two date structures.
 * @param date_1 - the first date
 * @param date_2 - the second date
 * @return -1 if date_1 occurs before date_2; 0 if they are
 *         the same; 1 if date_1 occurs after date_2
*/
int
compare_Date (dateType date_1,
              dateType date_2)
{
    // local variable declaration
    int flag; // if date_1 is before, the same, or after as date_2

    // if the first date occurs before the second as per year
    if (date_1.year < date_2.year)
        flag = -1;

    // if the first date occurs after the second as per year
    else if (date_1.year > date_2.year)
        flag = 1;

    // activates if they have the same year
    else
        // if the first date occurs before the second as per month
        if (date_1.month < date_2.month)
            flag = -1;

        // if the first date occurs after the second as per month
        else if (date_1.month > date_2.month)
            flag = 1;

        // activates if they have the same month
        else

            // if the first date occurs before the second as per day
            if (date_1.day < date_2.day)
                flag = -1;
            
            // if the first date after before the second as per day
            else if (date_1.day > date_2.day)
                flag = 1;

            // if they are really the same
            else
                flag = 0;
    return flag;
}
