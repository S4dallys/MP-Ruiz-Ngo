#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * display_Choices displays an array of strings as choices, 
 * i.e., in the format "[<letter>] <choice><new line>"",
 * in separate lines.
 * @param choices_list - an array containg strings which 
 *                       have 30 non-null byte 
 *                       characters at most.
 * @param choices_list_length - the number of strings 
 *                              inside choices_list.
 * @Precondition: choices_list_length must be greater than 0.
*/
void 
display_Choices (String30  choices_list[],
                 int       choices_list_length)
{
    // local variable declaration
    int i;

    // display header
    printf("\tChoices:\n");

    // iterate through and display the choices in specified
    // format 
    for (i = 0; i < choices_list_length; i++)
        printf("\t\t[%c] %s\n", 'A' + i, choices_list[i]);
}

/**
 * display_Horizontal_Border_Line displays a horizontal
 * border line to be used in tables.
 * @param number_Of_Columns - the number of columns to be 
 *                            that the horizontal border
 *                            should reflect.
 * @param colum_Width_Array - an array which has the width
 *                            of each column from left to
 *                            right.
 * @Precondition: number_Of_Columns must be greater than 0.
*/
void
display_Horizontal_Border_Line (int  number_Of_Columns,
                                int  column_Width_Array[])
{
    // local variable declaration
    int i;
    int j;

    // print a tab character
    printf("\t");
    
    // printing the line itself
    for (i = 0; i < number_Of_Columns; i++)
    {
        // place a '+' to begin
        printf("+");

        // print out some dashes, the number of which is
        // the ith number in column_Width_Array plus 2.
        for (j = 0; j < column_Width_Array[i] + 2; j++)
            printf("-");
    }

    // place a capping '+' and a new line
    printf("+\n");
}

/**
 * display_Menu displays a menu and gets a valid choice from
 * the user. If the user gives an erroneous input, it will
 * ask from the user again until it is valid.
 * @param menu_Name - an at-most 30-character string which
 *                    is the name of the menu
 * @param choices_List - an array of choices, all which are
 *                       strings with at most 30 characters
 * @param choices_List_Length - the number of entries in
 *                              choices_List
 * @return an uppercase letter from 'A' to the choices_List
 * _Length letter of the alphabet
 * @Precondition choices_List_Length must be greater than
 * 0 and less than 27
*/
char 
display_Menu (String30  menu_Name,
              String30  choices_List[],
              int       choices_List_Length)
{
    // local variable declaration
    boolean  error;
    boolean  done;
    char     choice;

    error = FALSE;
    done = FALSE;

    // show menu name and choices
    printf("\t%s Menu:\n", menu_Name);
    display_Choices(choices_List, choices_List_Length);
    
    // insist on getting a valid input
    do
    {
        // display an error message if the user previously inputted erroneously
        if (error)
            printf("\tInvalid Input\n");

        // ask for a choice
        prompt_Char("Insert choice: ", &choice);

        // transforms lowercase input to uppercase, if ever
        if (choice >= 'a' && choice <= 'z')
            choice = choice - ('A' - 'a');

        // check if the input is part of the choices given
        if (choice < 'A' || choice > 'A' + choices_List_Length - 1)
            error = TRUE;
        else
            done = TRUE;
    
    // end the loop once a non-erroneous input is given
    } while (!done);

    return choice;
}

/**
 * display_Table_Ala_Show_My_Products displays the product
 * ID, item name, category, unit price, and quantity available
 * of every item whose index is in a certain array.
 * @param item_Array - an array of items (struct itemTag)
 * @param item_Index_Array - an array of indices of items
 *                           belonging to item_Array
 * @param item_Array_Length - the number of indices in
 *                            item_Index_Array
*/
void
display_Table_Ala_Show_My_Products (itemType  item_Array[],
                                    int       item_Index_Array[],
                                    int       item_Array_Length)
{
    // local variable declaration
    int item_Width_Array[5] = {19, 20, 15, 15, 19};
    int index;
    boolean first;

    first = TRUE;

    // loop through the initialization and the entire array
    for (index = -1; index < item_Array_Length; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, item_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE;

            printf("\t| %-19s | %-20s | %-15s | %-15s | %-19s |\n", 
                    "PRODUCT ID", "ITEM NAME", "CATEGORY", "UNIT PRICE", 
                    "QUANTITY AVAILABLE");
        }

        // print the data in each column
        else
        {
            printf("\t| %19I64d | %-20s | %-15s | %15.2f | %19I64d |\n",
                        item_Array[item_Index_Array[index]].product_ID,
                        item_Array[item_Index_Array[index]].name,
                        item_Array[item_Index_Array[index]].category,
                        item_Array[item_Index_Array[index]].unit_Price,
                        item_Array[item_Index_Array[index]].quantity_Available);
        }
    }

    // cap it off with a final horizontal border line
    display_Horizontal_Border_Line(5, item_Width_Array);
}

/**
 * display_Item displays the product ID, name, category, 
 * quantity available, and price of a given item structure.
 * @param item - an itemType structure whose contents
 *               are wished to display
*/
void
display_Item (itemType  item)
{
  printf("\tProduct ID:         %I64d\n", item.product_ID);
  printf("\tName:               %s\n", item.name);
  printf("\tCategory:           %s\n", item.category);
  printf("\tQuantity Avaliable: %I64d\n", item.quantity_Available);
  printf("\tPrice:              %lf\n", item.unit_Price); 
}

/**
 * display_User_Table displays all the users in an array in
 * a tabular format
 * @param user_Database - an array of users (struct userTag)
 * @param user_Database_Size - the amount of users in the
 *                             array
*/
void
display_User_Table (userType user_Database[], 
                    int      user_Database_Size)
{
    // local variable declaration
    int user_Width_Array[] = {19, 10, 20, 30, 19};
    int index;
    boolean first;

    first = TRUE;

    // loop through the initialization and the entire array
    for (index = -1; index < user_Database_Size; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, user_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE;

            printf("\t| %-19s | %-10s | %-20s | %-30s | %-19s |\n", 
                   "USER ID", "PASSWORD", "NAME", "ADDRESS", 
                   "CONTACT NUMBER");

        }

        // print the data in each column
        else
        {
            printf("| %19lld | %-10s | %-20s | %-30s | %19lld |\n",
                   user_Database[index].user_ID,
                   user_Database[index].password,
                   user_Database[index].name,
                   user_Database[index].address,
                   user_Database[index].contact);
        }
    }

    // cap it off with a final horizontal border line
    display_Horizontal_Border_Line(5, user_Width_Array);
}

/**
 * let_Read lets a user read the previous output and cleans 
 * the input stream up to the next new line character.
*/
void
let_Read ()
{
    // local variable declaration
    char garbage;

    // give the user a prompt
    printf("\tPress Enter to continue...");

    // clean out the input stream until the new line
    // in case the user types in a bunch of characters
    // before it
    do
    {
        scanf("%c", &garbage);
    } while (garbage != '\n');
}

/**
 * new_Line prints a new line to the output stream.
*/
void
new_Line()
{
  printf("\n");
}