#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * check_Unique_Item_ID checks if a given long long parameter 
 * exists as an item or product ID in a given item array.
 * @param item_Database - array of item structures
 * @param item_Database_Size - number of item structures 
 *                             in item_Database
 * @param item_ID - a number to be checked if it exists as
 *                  an item or product ID in item_Database
 * @return TRUE if the ID HAS NOT been found in the array, 
 *         and FALSE, if it HAS been found. 
*/
boolean
check_Unique_Item_ID (itemType   item_Database[],
                      int        item_Database_Size,
				      long long  item_ID)
{
    // local variable declaration
	boolean  flag;
	int      index;
	
	flag = TRUE;
	index = 0;
	
    // looping through the array until it reaches the end
    // or an instance has been found
	while (index < item_Database_Size && flag == FALSE)

        // flags an instance of item_ID in the array
		if (item_Database[index].product_ID == item_ID)
			flag = FALSE;

        // increments the index
		else
			index++;
	
	return flag;
}

/**
 * register_Product accepts input from the user to create
 * an item or product instance and appends it to an array
 * of item structures and updates its number. It also 
 * insists upon getting a unique item ID, i.e., one that 
 * does not yet exist in the array.
 * @param item_Database - an array of item structures
 * @param item_Database_Count - a pointer which refers to
 *                              a variable containing the
 *                              number of items in an array
 * @param user_ID - the user ID of the user registering
 *                  a product.
*/
void
register_Product (itemType   item_Database[],
                  int *      item_Database_Count,
                  long long  user_ID)
{
    // local variable declaration
    itemType  item;
    boolean   valid_Response;

    valid_Response = TRUE;

    // insists on attaining a unique item ID
    do
    {
        // displays a message if the user previously gave an 
        // erroneous input
        if (!valid_Response)
            printf("\tItem ID already taken. Please find another.\n");
        
        // asks for item ID
        prompt_Long_Long("ID: ", &item.product_ID);

        // checks if the item ID is unique
        valid_Response = check_Unique_Item_ID (item_Database, 
                                               *item_Database_Count, 
                                               item.product_ID);

    // loop ends when the user gives a unique ID
    } while (!valid_Response);

    // asks for an item name
    prompt_StringN("Name: ", item.name, 20);

    // asks for the item's category
    prompt_StringN("Category: ", item.category, 15);

    // asks for the item's description
    prompt_StringN("Description: ", item.description, 30);

    // asks for how many items there are available
    prompt_Long_Long("Quantity Available: ", &item.quantity);

    // asks for the price the user is selling them at
    prompt_Double("Price: ", &item.unit_Price);

    // tags the ID of the user to as the item's seller ID
    item.seller_ID = user_ID;

    // shows that registration was successful
    new_Line();

    printf("\tItem Registration Successful!\n");

    // adds the item to the database
    item_Database[*item_Database_Count] = item;

    // updates the number of items in the database
    (*item_Database_Count)++;

    // lets the user read
    let_Read();
}

/**
 * find_User_Product searches for a user's products in an 
 * array of items and stores the indices of these products
 * in an integer array and returns the number of products
 * found.
 * @param item_Database - an array of item structures
 * @param item_Database_Size - the number of items inside
 *                             item_Database
 * @param sellerID - the user whose products the function 
 *                   is looking for
 * @param item_Indices_Array - the array where the indices
 *                             of where the user's products
 *                             are stored in item_Database
 *                             are to be stored
 * @return the length of item_Indices_Array
*/
int
find_User_Product (itemType   item_Database[],
                   int        item_Database_Size,
                   long long  sellerID,
                   int        item_Indices_Array[])
{
    // local variable declaration
    int index;
    int i;

    index = 0;

    // loops through the array
    for (i = 0; i < item_Database_Size; i++)
    {
        // records an item's index in item_Indices_Array
        // if its seller ID is the same as the one given.
        if (item_Database[i].seller_ID == sellerID)
        {
            item_Indices_Array[index] = i;

            // increments the index
            index++;
        }
    }

    // returns how many products the seller has
    return index;
}

/**
 * find_User_Product searches for a user's products in an 
 * array of orders and stores the indices of these products
 * in an integer array and returns the number of products
 * found.
 * @param item_Database - an array of item structures
 * @param item_Database_Size - the number of items inside
 *                             item_Database
 * @param sellerID - the user whose products the function 
 *                   is looking for
 * @param item_Indices_Array - the array where the indices
 *                             of where the user's products
 *                             are stored in item_Database
 *                             are to be stored
 * @return the length of item_Indices_Array
*/
int
find_User_Product_In_Cart (orderType  order_Database[],
                           int        order_Database_Size,
                           long long  sellerID,
                           int        order_Indices_Array[])
{
    // local variable declaration
    int index;
    int i;

    index = 0;

    // loops through the array
    for (i = 0; i < order_Database_Size; i++)
    {
        // records an order's index in order_Indices_Array
        // if its seller ID is the same as the one given.
        if (order_Database[i].item.seller_ID == sellerID)
        {
            order_Indices_Array[index] = i;

            // increments the index
            index++;
        }
    }

    // returns how many products the seller has
    return index;
}

/**
 * find_Product_In_List, using an array of indices of
 * item structures from an array, checks if one of the 
 * indices in the array represents an item with a certain
 * item ID.
 * @param item_Database - an array of item structures
 * @param itemID - the ID of an item to be searched
 * @param item_Indices_Array - an array of indices wherein
 *                             the products it represents
 *                             is a searching ground for
 *                             itemID
 * @param item_Indices_Array_Length - the number of indices 
 *                                    in item_indices_Array
 * @return TRUE if the itemID was found; else, FALSE
*/
boolean
find_Product_In_List (itemType    item_Database[],
                      long long   itemID,
                      int         item_Indices_Array[],
                      int         item_Indices_Array_Length)
{
    // local variable declaration
    boolean found;
    int i;

    found = FALSE;
    i = 0;

    // looping through the array until it reaches the end
    // or an instance has been found
    while (i < item_Indices_Array_Length && found == FALSE)
    {
        // flags an instance of item_ID in the array
        if (item_Database[item_Indices_Array[i]].product_ID == itemID)
          found = TRUE;

        // increments an index
        else i++;
    }

    return found;
}

/**
 * give_Item_Index_Via_ID gives the index of an item 
 * structure within an array of such.
 * @param item_Database - an array of item structures
 * @param itemID - the item ID of the item whose index
 *                 is desired to be known
 * @param item_Database_Count - the number of item structures
 *                              in item_Database
 * @return the index of the item; -1 if not found
*/
int
give_Item_Index_Via_ID (itemType   item_Database[],
                        long long  itemID,
                        int        item_Database_Count)
{
    // local variable declaration
    int index;
    int i;

    index = -1;
    i = 0;

    // looping through the array until it reaches the end
    // or an instance has been found
    while (i < item_Database_Count && index == -1)
    {
        // flags an instance of item_ID in the array
        if (item_Database[i].product_ID == itemID)
            index = i;

        // increments an index    
        else i++;
    }
    
    return index;
}

int
give_Item_Index_Via_ID_Ordertype (orderType   item_Database[],
                        long long  itemID,
                        int        item_Database_Count)
{
    // local variable declaration
    int index;
    int i;

    index = -1;
    i = 0;

    // looping through the array until it reaches the end
    // or an instance has been found
    while (i < item_Database_Count && index == -1)
    {
        // flags an instance of item_ID in the array
        if (item_Database[i].item.product_ID == itemID)
            index = i;

        // increments an index    
        else i++;
    }
    
    return index;
}

/**
 * give_Item_Index_Via_ID_In_Cart gives the index of an item 
 * structure within an array of order structures
 * @param item_Database - an array of order structures
 * @param itemID - the item ID of the item whose index
 *                 is desired to be known
 * @param item_Database_Count - the number of order structures
 *                              in order_Database
 * @return the index of the item; -1 if not found
*/
int
give_Item_Index_Via_ID_In_Cart (orderType  order_Database[],
                                long long  itemID,
                                int        order_Database_Count)
{
    // local variable declaration
    int index;
    int i;

    index = -1;
    i = 0;

    // looping through the array until it reaches the end
    // or an instance has been found
    while (i < order_Database_Count && index == -1)
    {
        // flags an instance of item_ID in the array
        if (order_Database[i].item.product_ID == itemID)
            index = i;

        // increments an index    
        else i++;
    }
    
    return index;
}

/**
 * give_User_Item_Index_Via_ID, using an array of indices of
 * item structures from an array, checks if one of the 
 * indices in the array represents an item with a certain
 * item ID; if it does, it returns its index and if it does
 * not, it returns -1.
 * @param item_Database - an array of item structures
 * @param itemID - the ID of an item to be searched
 * @param item_Indices_Array - an array of indices wherein
 *                             the products it represents
 *                             is a searching ground for
 *                             itemID
 * @param item_Indices_Array_Length - the number of indices 
 *                                    in item_indices_Array
 * @return the index of item_ID vis-a-vis item_Database; else,
 *         it returns -1.
*/
int
give_User_Item_Index_Via_ID (itemType   item_Database[],
                             long long  itemID,
                             int        item_Indices_Array[],
                             int        item_Indices_Array_Length)
{
    // local variable declaration
    int index;
    int i;

    index = -1;
    i = 0;

    // looping through the array until it reaches the end
    // or an instance has been found
    while (i < item_Indices_Array_Length && index == -1)
    {
        // flags an instance of item_ID in the array
        if (item_Database[item_Indices_Array[i]].product_ID == itemID)
            index = item_Indices_Array[i];

        // increments an index  
        else i++;
    }
    
    return index;
}

/**
 * count_User_Items counts how many items a user is selling
 * from a given array of item structures.
 * @param item_Database - an array of item structures
 * @param item_Database_Count - the number of items inside
 *                              item_Database
 * @param userID - the user whose number of items being
 *                 sold we wish to know
 * @return the number of items the user represented by userID
 *         is selling
*/
int
count_User_Items (itemType   item_Database[],
                  int        item_Database_Count,
                  long long  userID)
{
    // local variable declaration
    int counter;
    int i;

    counter = 0;

    // loops though the array
    for (i = 0; i < item_Database_Count; i++)
    {
        // increments the counter if the item is being sold
        // by the seller in question
        if (item_Database[i].seller_ID == userID)
            counter++;
    }

    return counter;
}

int
count_User_Items_Ordertype (orderType item_Database[],
                            int        item_Database_Count,
                            long long  userID)
{
    // local variable declaration
    int counter;
    int i;

    counter = 0;

    // loops though the array
    for (i = 0; i < item_Database_Count; i++)
    {
        // increments the counter if the item is being sold
        // by the seller in question
        if (item_Database[i].item.seller_ID == userID)
            counter++;
    }

    return counter;
}

/**
 * sort_Item_Array sorts an array of item indices with respect
 * to the item IDs of the item they represent, in ascending 
 * order.
 * @param item_Database - an array of item structures
 * @param item_Index_Array - an array of array indices
 * @param item_Array_Size - the number of indices in 
 *                          item_Index_Array
*/
void
sort_Item_Array_By_ID (itemType  item_Database[],
                       int       item_Index_Array[],
                       int       item_Array_Size)
{
    // local variable declaration
    int lowest;
    int temp;
    int i;
    int j;

    // loops through all of the indices in item_Idex_Array
    for (i = 0; i < item_Array_Size - 1; i++)
    {
        // assume that the ith element represents the lowest ID
        lowest = i;

        // loops through the rest of the array
        for (j = i + 1; j < item_Array_Size; j++)
        {
            // rewrites the representation of the lowest ID if
            // it finds a smaller one
            if (item_Database[item_Index_Array[lowest]].product_ID > 
                item_Database[item_Index_Array[j]].product_ID)
                lowest = j;
        }

        // switches if the ith element does not represent the
        // item with the lowest ID from range (i, item_Array_Size)
        if (lowest != i)
        {
            temp = item_Index_Array[i];
            item_Index_Array[i] = item_Index_Array[lowest];
            item_Index_Array[lowest] = temp;
        }
    }
}

/**
 * swap_Item swaps the contents of one item structure with
 * another
 * @param a - the address of an item structure
 * @param b - the address of another item structure
*/
void swap_Item (itemType *  a,
                itemType *  b)
{
    // local variable declaration
    itemType temp;

    // switches the contents
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_Item_Ordertype (orderType *  a,
                          orderType *  b)
{
    // local variable declaration
    orderType temp;

    // switches the contents
    temp = *a;
    *a = *b;
    *b = temp;
}
