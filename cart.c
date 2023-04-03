#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

void add_Item_To_Cart (itemType    item_Database[],
                       itemType    user_Cart[],
                       int         item_Database_Count,
                       int *       item_Cart_Count,
                       long long   user_ID)
{
    long long item_ID;
    long long quantity;
    int item_Index;

    prompt_Long_Long ("ID: ", &item_ID);
    prompt_Long_Long ("Quantity: ", &quantity);

    item_Index = give_Item_Index_Via_ID (item_Database, item_ID, item_Database_Count);

    if (item_Index != -1)
    {
        if (item_Database[item_Index].seller_ID == user_ID)
        {
            printf("\tERROR: Sellers cannot sell to themselves.\n");
            let_Read();
        }

        else
        {
            if (item_Database[item_Index].quantity_Available >= quantity) 
            {
                user_Cart[*item_Cart_Count] = item_Database[item_Index];
                user_Cart[*item_Cart_Count].quantity_Available = quantity;
                item_Database[item_Index].quantity_Available -= quantity;
                *item_Cart_Count = *item_Cart_Count + 1;

                printf("\tItem added to cart.\n");
                let_Read();
            }
            
            else
            {
                printf("\tERROR: Quantity requested exceeds stock.\n");
                let_Read();
            }
        }
    }
    else 
    {
        printf("\tERROR: Item not found.\n");
        let_Read();
    }
}
