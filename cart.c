#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

// *---prototypes---*

// none

// *----------------*

void add_Item_To_Cart (itemType    item_Database[],
                       itemType    user_Cart[],
                       int         item_Database_Count,
                       int *       item_Cart_Count)
{
    long long item_ID;
    long long quantity;
    int item_index;

    prompt_Long_Long ("ID: ", &item_ID);
    prompt_Long_Long ("Quantity: ", &quantity);

    item_index = give_Item_Index_Via_ID (item_Database, item_ID, item_Database_Count);

    if (item_index != -1)
    {
        user_Cart[*item_Cart_Count] = item_Database[item_index];
        user_Cart[*item_Cart_Count].quantity_Available = quantity;
        *item_Cart_Count = *item_Cart_Count + 1;

        printf("\tItem added to cart.\n");
        let_Read();
    }
    else 
    {
        printf("\tERROR: Item not found.\n");
        let_Read();
    }
}
