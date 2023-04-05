#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

boolean
is_Leap (int year)
{
    boolean flag;

    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                flag = TRUE;
            else
                flag = FALSE;
        }

        else
            flag = TRUE;
    }

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
