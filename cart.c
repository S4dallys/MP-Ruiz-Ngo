#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

void 
add_Item_To_Cart (itemType    item_Database[],
                  orderType   user_Cart[],
                  int         item_Database_Count,
                  int *       item_Cart_Count,
                  long long   user_ID)
{
    long long item_ID;
    long long quantity;
    int item_Index;

    prompt_Long_Long ("ID: ", &item_ID);

    if (give_Item_Index_Via_ID_In_Cart(user_Cart, item_ID, *item_Cart_Count) != -1)
    {
        printf("\tERROR: Product already in cart.\n");
        printf("\tPlease go to Edit Cart -> Edit Quantity instead for additional orders.\n");
        let_Read();
    }

    else
    {
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
                if (item_Database[item_Index].quantity >= quantity) 
                {
                    user_Cart[*item_Cart_Count].item = item_Database[item_Index];
                    user_Cart[*item_Cart_Count].quantity_Desired = quantity;
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
}

boolean
compare_Product (itemType item_1, itemType item_2)
{
    return strcmp (item_1.category, item_2.category) == 0 &&
           strcmp (item_1.description, item_2.description) == 0 &&
           strcmp (item_1.name, item_2.name) == 0 &&
           item_1.quantity == item_2.quantity &&
           item_1.unit_Price == item_2.unit_Price; 
}

int
enumerate_Differing_Product (itemType  item_Database[],
                             int       item_Database_Count,
                             orderType user_Cart[],
                             int       user_Cart_Count,
                             int       update_Product_Indices[])
{
    int i;
    int counter;

    counter = 0;

    for (i = 0; i < user_Cart_Count; i++)
    {
        if (!compare_Product (item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                  user_Cart[i].item.product_ID, 
                                                                  item_Database_Count)],
                             user_Cart[i].item))
        {
            update_Product_Indices[counter] = i;
            counter++;
        }
    }

    return counter;
}

boolean
check_Unique_Seller (long long  ID_Array[],
                     int        ID_Database_Size,
				     long long  user_ID)
{
    boolean  flag;
	int      index;
	
	flag = TRUE;
	index = 0;
	
	while (index < ID_Database_Size && flag == FALSE)
    {
		if (ID_Array[index] == user_ID)
			flag = FALSE;
		else
			index++;
    }

	return flag;
}

int
enumerate_Unique_Sellers (orderType order_Array[],
                          int       order_Database_Count,
                          long long unique_Seller_Array[])
{
    int ctr;
    int i;

    ctr = 0;

    for (i = 0; i < order_Database_Count; i++)
    {
        if (check_Unique_Seller(unique_Seller_Array, ctr, order_Array[i].item.seller_ID))
        {
            unique_Seller_Array[ctr] = order_Array[i].item.seller_ID;
            ctr++;
        }
    }

    return ctr;

}