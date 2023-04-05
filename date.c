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