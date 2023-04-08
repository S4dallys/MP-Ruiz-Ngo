#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * Function used in "Add to cart" option in main program. Contains multiple prompts 
 * that only fits within this context. 
 * @param item_Database Main database of items
 * @param user_Cart User cart array
 * @param item_Database_Count Number of items in user_Cart
 * @param user_ID Current User_ID
*/
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

    // promp for user_ID
    prompt_Long_Long ("ID: ", &item_ID);

    // see if item is already in cart
    if (give_Item_Index_Via_ID_In_Cart(user_Cart, item_ID, *item_Cart_Count) != -1)
    {
        printf("\tERROR: Product already in cart.\n");
        printf("\tPlease go to Edit Cart -> Edit Quantity instead for additional orders.\n");
        let_Read();
    }

    else
    {
        // prompt for quantity
        prompt_Long_Long ("Quantity: ", &quantity);

        // find index of item in item_Database
        item_Index = give_Item_Index_Via_ID (item_Database, item_ID, item_Database_Count);

        if (item_Index != -1)
        {
            // check if user is buying own product
            if (item_Database[item_Index].seller_ID == user_ID)
            {
                printf("\tERROR: Sellers cannot sell to themselves.\n");
                let_Read();
            }

            else
            {
                // product is a valid product to add to cart
                if (item_Database[item_Index].quantity >= quantity) 
                {
                    // copy product into user_Cart as orderType
                    user_Cart[*item_Cart_Count].item = item_Database[item_Index];
                    user_Cart[*item_Cart_Count].quantity_Desired = quantity;
                    *item_Cart_Count = *item_Cart_Count + 1;

                    printf("\tItem added to cart.\n");
                    let_Read();
                }

                else
                {   
                    // in case desired quantity is higher than item_Database quantity
                    printf("\tERROR: Quantity requested exceeds stock.\n");
                    let_Read();
                }
            }
        }
        else 
        {
            // if item not found in database
            printf("\tERROR: Item not found.\n");
            let_Read();
        }
    }
}

/**
 * Compares two itemTypes via each member.
 * @param item_1 First item to compare
 * @param item_2 Second item to compare
 * @return TRUE if both items are the same, FALSE otherwise 
*/
boolean
compare_Product (itemType item_1, itemType item_2)
{
    // compares every itemType member between both items, returns the 
    // results of every expression using (&&)
    return strcmp (item_1.category, item_2.category) == 0 &&
           strcmp (item_1.description, item_2.description) == 0 &&
           strcmp (item_1.name, item_2.name) == 0 &&
           item_1.quantity == item_2.quantity &&
           item_1.unit_Price == item_2.unit_Price; 
}

/**
 * Find total number of items with pending updates in user_Cart and adds their respective
 * indices in passed array.
 * @param item_Database Array of items to compare with
 * @param item_Database_Count Number of items in item_Database
 * @param user_Cart Array of items to check
 * @param user_Cart_Count Number of items in user_Cart
 * @param update_Product_Indices Array to place item indices in
 * @return number of items in user_Cart that differs from their item_Database version
*/
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

    // for each item in cart
    for (i = 0; i < user_Cart_Count; i++)
    {
        // if item in cart is different from item_Database version
        if (!compare_Product (item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                  user_Cart[i].item.product_ID, 
                                                                  item_Database_Count)],
                             user_Cart[i].item))
        {
            // add it's index (user_Cart) in update_Product_Indices
            update_Product_Indices[counter] = i;
            counter++;
        }
    }

    return counter;
}
