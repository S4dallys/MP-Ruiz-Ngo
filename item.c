#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

int
count_User_Items (itemType  item_Database[],
                  int       item_Database_Count,
                  long long userID)
{
  int counter = 0;
  int i;
  for (i = 0; i < item_Database_Count; i++)
    if (item_Database[i].seller_ID == userID)
      counter++;
  return counter;
}

boolean
check_Unique_Item_ID (itemType  item_Database[],
                      int       item_Database_Size,
				              long long item_ID)
{
	boolean flag;
	int index;
	
	flag = TRUE;
	index = 0;
	
	while (index < item_Database_Size && flag == FALSE)
		if (item_Database[index].product_ID == item_ID)
			flag = FALSE;
		else
			index++;
	
	return flag;
}

void
register_Product (itemType item_Database[],
                  int      *item_Database_Count,
                  long long user_ID)
{
  itemType  item;
  boolean   valid_Response;
  //char      white_Space;

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

int
find_User_Product (itemType    item_Database[],
                   int         item_Database_Size,
                   long long   sellerID,
                   int         item_Indices_Array[])
{
    int index = 0;
    int i;
    for (i = 0; i < item_Database_Size; i++)
        if (item_Database[i].seller_ID == sellerID)
        {
            item_Indices_Array[index] = i;
            index++;
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
        if (item_Database[item_Indices_Array[i]].product_ID == itemID)
          found = TRUE;
        else i++;
    return found;
}

int
give_Item_Index_Via_ID (itemType    item_Database[],
                        long long   itemID,
                        int         item_Indices_Array[],
                        int         item_Indices_Array_Length)
{
  int index = -1;
  int i = 0;
  while (i < item_Indices_Array_Length && index == -1)
    if (item_Database[item_Indices_Array[i]].product_ID == itemID)
      index = item_Indices_Array[i];
    else i++;
  return index;
}

void
sort_Item_Array_By_ID (itemType item_Database[],
                       int      item_Index_Array[],
                       int      item_Array_Size)
{
    int i;
    int j;
    int lowest;
    int temp;

    for (i = 0; i < item_Array_Size - 1; i++)
    {
        lowest = i;
        for (j = i + 1; j < item_Array_Size; j++)
            if (item_Database[item_Index_Array[lowest]].product_ID > 
                item_Database[item_Index_Array[j]].product_ID)
                lowest = j;
        if (lowest != i)
        {
            temp = item_Index_Array[i];
            item_Index_Array[i] = item_Index_Array[lowest];
            item_Index_Array[lowest] = temp;
        }
    }
}


void
display_Table_Ala_Show_My_Products (itemType item_Array[],
                                    int      item_Index_Array[],
                                    int      item_Array_Length)
{
  boolean first = TRUE;
  int index;
  int item_Width_Array[5] = {19, 20, 15, 15, 19};

  for (index = -1; index < item_Array_Length; index++)
    {
      display_Horizontal_Border_Line(5, item_Width_Array);
      if (first)
      {
        printf("\t| %-19s | %-20s | %-15s | %-15s | %-19s |\n", 
               "PRODUCT ID", "ITEM NAME", "CATEGORY", "UNIT PRICE", 
               "QUANTITY AVAILABLE");
        first = FALSE;
      }
      else
        printf("\t| %19I64d | %-20s | %-15s | %15.2f | %19I64d |\n",
                   item_Array[item_Index_Array[index]].product_ID,
                   item_Array[item_Index_Array[index]].name,
                   item_Array[item_Index_Array[index]].category,
                   item_Array[item_Index_Array[index]].unit_Price,
                   item_Array[item_Index_Array[index]].quantity_Available);
      }
  display_Horizontal_Border_Line(5, item_Width_Array);
}