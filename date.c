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

int
give_Max_Days_In_Month (boolean is_Leap,
                        int     month)
{
    int max_Days;

    if (month == 2)
    {
        if (is_Leap)
            max_Days = 29;
        else max_Days = 28;
    }

    else
    {
        switch (month)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                max_Days = 30;
                break;
            default:
                max_Days = 31;
                break;
        }
    }

    return max_Days;
}

int
compare_Date (dateType date_1,
              dateType date_2)
{
    int flag;
    if (date_1.year < date_2.year)
        flag = -1;
    else if (date_1.year > date_2.year)
        flag = 1;
    else
        if (date_1.month < date_2.month)
            flag = -1;
        else if (date_1.month > date_2.month)
            flag = 1;
        else
            if (date_1.day < date_2.day)
                flag = -1;
            else if (date_1.day > date_2.day)
                flag = 1;
            else
                flag = 0;
    return flag;
}
