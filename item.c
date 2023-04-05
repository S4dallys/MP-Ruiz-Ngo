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
 * find_Product_In_List, using an array of indices of
 * item structures from an array, checks if one of the 
 * indices in the array represents an item with a certain
 * item ID.
 * @
*/
boolean
find_Product_In_List (itemType    item_Database[],
                      long long   itemID,
                      int         item_Indices_Array[],
                      int         item_Indices_Array_Length)
{
    boolean found = FALSE;
    int i = 0;

    while (i < item_Indices_Array_Length && found == FALSE)
    {
        if (item_Database[item_Indices_Array[i]].product_ID == itemID)
          found = TRUE;
        else i++;
    }

    return found;
}

int
give_Item_Index_Via_ID (itemType   item_Database[],
                        long long  itemID,
                        int        item_Database_Count)
{
    int index = -1;
    int i = 0;

    while (i < item_Database_Count && index == -1)
    {
        if (item_Database[i].product_ID == itemID)
        index = i;
        else i++;
    }
    
    return index;
}

int
give_User_Item_Index_Via_ID (itemType   item_Database[],
                             long long  itemID,
                             int        item_Indices_Array[],
                             int        item_Indices_Array_Length)
{
    int index = -1;
    int i = 0;

    while (i < item_Indices_Array_Length && index == -1)
    {
        if (item_Database[item_Indices_Array[i]].product_ID == itemID)
        index = item_Indices_Array[i];
        else i++;
    }
    
    return index;
}

int
count_User_Items (itemType   item_Database[],
                  int        item_Database_Count,
                  long long  userID)
{
    int counter = 0;
    int i;

    for (i = 0; i < item_Database_Count; i++)
        if (item_Database[i].seller_ID == userID)
        counter++;

    return counter;
}
/**
 * sort_Item_Array
*/
void
sort_Item_Array_By_ID (itemType  item_Database[],
                       int       item_Index_Array[],
                       int       item_Array_Size)
{
    int lowest;
    int temp;
    int i, j;

    for (i = 0; i < item_Array_Size - 1; i++)
    {
        lowest = i;

        for (j = i + 1; j < item_Array_Size; j++)
        {
            if (item_Database[item_Index_Array[lowest]].product_ID > 
                item_Database[item_Index_Array[j]].product_ID)
                lowest = j;
        }

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
