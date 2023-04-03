#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

// *---prototypes---*

boolean check_Unique_Item_ID (itemType item_Database[], int item_Database_Size, long long item_ID);

// *----------------*

void
register_Product (itemType   item_Database[],
                  int *      item_Database_Count,
                  long long  user_ID)
{
    itemType  item;
    boolean   valid_Response;
    //char    white_Space;

    valid_Response = TRUE;
    
    do
    {
        if (!valid_Response)
            printf("\tItem ID already taken. Please find another.\n");
        
        prompt_Long_Long("ID: ", &item.product_ID);

        valid_Response = check_Unique_Item_ID (item_Database, 
                                               *item_Database_Count, 
                                               item.product_ID);
    } while (!valid_Response);

    //white_Space = scanf("%c", &white_Space);

    prompt_StringN("Name: ", item.name, 20);

    prompt_StringN("Category: ", item.category, 15);

    prompt_StringN("Description: ", item.description, 30);

    prompt_Long_Long("Quantity Available: ", &item.quantity_Available);

    prompt_Double("Price: ", &item.unit_Price);

    item.seller_ID = user_ID;

    new_Line();

    printf("\tItem Registration Successful!\n");

    item_Database[*item_Database_Count] = item;

    (*item_Database_Count)++;

    let_Read();
}

boolean
check_Unique_Item_ID (itemType   item_Database[],
                      int        item_Database_Size,
				      long long  item_ID)
{
	boolean  flag;
	int      index;
	
	flag = TRUE;
	index = 0;
	
	while (index < item_Database_Size && flag == FALSE)
		if (item_Database[index].product_ID == item_ID)
			flag = FALSE;
		else
			index++;
	
	return flag;
}

int
find_User_Product (itemType   item_Database[],
                   int        item_Database_Size,
                   long long  sellerID,
                   int        item_Indices_Array[])
{
    int index = 0;
    int i;

    for (i = 0; i < item_Database_Size; i++)
    {
        if (item_Database[i].seller_ID == sellerID)
        {
            item_Indices_Array[index] = i;
            index++;
        }
    }

    return index;
}

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

void swap_Item (itemType *  a,
                itemType *  b)
{
    itemType temp = *a;
    *a = *b;
    *b = temp;
}