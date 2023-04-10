#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

int
search_User (userType   user_Database[],
             int        user_Database_Size,
             long long  user_ID);

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
    int i; // looping variable for later loop

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
    int i; // looping variable for later loop
    int j; // looping variable for later loop

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
    boolean  error; // represents if an error has occured
    boolean  done;  // represents if the user is done
    char     choice; // holds a user's choice

    error = FALSE; // assumes no error has been made
    done = FALSE;  // assumes the user is not yet done

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
            // says an error if it is not a part
            error = TRUE;
        else
            // ends the loop otherwise
            done = TRUE;
    
    // end the loop once a non-erroneous input is given
    } while (!done);

    return choice;
}

/**
 * display_Product_Array displays the product
 * ID, item name, category, unit price, and quantity available
 * of every item which is in an order array.
 * @param order_Array - an array of orderss (struct orderTag)
 * @param order_Array_Length - the number of items in
 *                             order_Array
*/
void
display_Product_Table (orderType order_Array[],
                       int       order_Array_Length)
{
    // local variable declaration
    int item_Width_Array[5] = {19, 20, 15, 15, 19}; // array of the widths of the values 
                                                    // in the table
    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    first = TRUE; // declares that it is the first run through

    // loop through the initialization and the entire array
    for (index = -1; index < order_Array_Length; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, item_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE; // says that it is no longer the first run through

            printf("\t| %-19s | %-20s | %-15s | %-15s | %-19s |\n", 
                    "PRODUCT ID", "ITEM NAME", "CATEGORY", "UNIT PRICE", 
                    "QUANTITY AVAILABLE"); // prints header
        }

        // print the data in each column
        else
        {
            printf("\t| %19I64d | %-20s | %-15s | %15.2f | %19I64d |\n",
                        order_Array[index].item.product_ID,
                        order_Array[index].item.name,
                        order_Array[index].item.category,
                        order_Array[index].item.unit_Price,
                        order_Array[index].item.quantity);
        }
    }

    // cap it off with a final horizontal border line
    display_Horizontal_Border_Line(5, item_Width_Array);
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
    int item_Width_Array[5] = {19, 20, 15, 15, 19}; // array of the widths of the values 
                                                    // in the table
    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    first = TRUE; // declares that it is the first run through

    // loop through the initialization and the entire array
    for (index = -1; index < item_Array_Length; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, item_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE; // says that it is no longer the first run through

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
                        item_Array[item_Index_Array[index]].quantity);
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
    // prints ID, name, category, quantity available, price in that order
    printf("\tProduct ID:         %I64d\n", item.product_ID);
    printf("\tName:               %s\n", item.name);
    printf("\tCategory:           %s\n", item.category);
    printf("\tQuantity Avaliable: %I64d\n", item.quantity);
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
    int user_Width_Array[] = {19, 10, 20, 30, 19}; // array of the widths of the values 
                                                   // in the table
    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    first = TRUE; // declares that it is the first run through

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
            printf("\t| %19I64d | %-10s | %-20s | %-30s | %19I64d |\n",
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
 * display_User_Table_With_Conditions displays the user structures
 * in an array in a tabular format. Each structure will only be
 * displayed if they are allowed to do so by their corresponding
 * permissions in another array.
 * @param user_Database - array of user tructures
 * @param user_Database_Size - number of users in user_Database
 * @param permissions_Array - an array of boolean values
*/
void
display_User_Table_With_Conditions (userType user_Database[], 
                                    int      user_Database_Size,
                                    boolean  permissions_Array[])
{
    // local variable declaration
    int user_Width_Array[] = {19, 10, 20, 30, 19}; // array of the widths of the values 
                                                   // in the table

    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    first = TRUE; // declares that it is the first run through

    // loop through the initialization and the entire array
    for (index = -1; index < user_Database_Size; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, user_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE; // says that it is no longer the first run through

            printf("\t| %-19s | %-10s | %-20s | %-30s | %-19s |\n", 
                   "USER ID", "PASSWORD", "NAME", "ADDRESS", 
                   "CONTACT NUMBER");

        }

        // print the data in each column, if that is allowed to be
        // printed by the permission in permissions array
        else if (permissions_Array[index] == TRUE)
        {
            printf("\t| %19I64d | %-10s | %-20s | %-30s | %19I64d |\n",
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

/**
 * display_And_Calculate_Order_Table displays the orders inside
 * an array of order structures.
 * @param transaction_Log - an array of orders
 * @param items_Ordered - the amount of orders in transaction_Log
 * @return the total amount of the transaction
*/
double
display_And_Calculate_Order_Table (orderType transaction_Log[],
                                   int       items_Ordered)
{
    // local variable declaration
    int item_Width_Array[5] = {19, 19, 20, 15, 15}; // array of the widths of the values 
                                                    // in the table
    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    double total_Price;    // holds the total price of the transaction
    double price_Of_Items; // holds the price of the items given the quantity

    first = TRUE; // declares that it is the first run through

    total_Price = 0; // initialize the total price

    // loop through the initialization and the entire array
    for (index = -1; index < items_Ordered; index++)
    {
        // display a horizontal border line
        display_Horizontal_Border_Line(5, item_Width_Array);

        // print the header at initialization
        if (first)
        {
            first = FALSE; // says that it is no longer the first run through

            printf("\t| %-19s | %-19s | %-20s | %-15s | %-15s |\n", 
                   "QUANTITY", "PRODUCT ID", "ITEM NAME", "UNIT PRICE", "TOTAL PRICE");
        }

        // print the data in each column
        else
        {
            // calculates the price of all items of given quantity
            price_Of_Items = transaction_Log[index].quantity_Desired *
                             transaction_Log[index].item.unit_Price;

            // displays the data in rows
            printf("\t| %19I64d | %19I64d | %-20s | %15.2f | %15.2f |\n",
                   transaction_Log[index].quantity_Desired,
                   transaction_Log[index].item.product_ID,
                   transaction_Log[index].item.name,
                   transaction_Log[index].item.unit_Price,
                   price_Of_Items);
            
            // adds the price of each item type together
            total_Price += price_Of_Items;
        }
    }

    // cap it off with a final horizontal border line
    display_Horizontal_Border_Line(5, item_Width_Array);

    return total_Price;
}

/**
 * display_Transaction displays a receipt or summary of a given transaction.
 * @param transaction - a pointer to the transaction structure to be displayed
 * @param user_Database - an array of users
 * @param user_Database_Size - the amount of users in user_Database
*/
void
display_Transaction (transactionType *transaction,
                     userType        user_Database[],
                     int             user_Database_Size)
{
    // prints a header
    printf("\t*****************************************SUMMARY OF TRANSACTION*****************************************");
    new_Line();

    // indicates the date of the transaction
    printf("\tDate of Transaction: %04d-%02d-%02d", transaction->date.year, 
                                                    transaction->date.month, 
                                                    transaction->date.day);
    new_Line();

    // shows the table of orders and calculates the total amount of the transaction
    // the latter result is used to initialize the transaction's amount
    transaction->amount = display_And_Calculate_Order_Table (transaction->transaction_Log, transaction->items_Ordered);
    new_Line();

    // shows the total price of the transaction
    printf("\tTotal Price of Transaction: %.2f\n", transaction->amount);
    new_Line();

    // shows who the transaction is payable to, a.k.a. the seller
    printf("\tPayable to: %s, User ID# %-I64d\n", 
           user_Database[search_User(user_Database, user_Database_Size, transaction->seller_ID)].name, 
           transaction->seller_ID);

    new_Line();
}

/**
 * display_User_Based_On_Money displays the user structures
 * in an array in a tabular format. Each structure will only be
 * displayed if they have any sales based on an array which
 * represents their sales
 * @param user_Database - array of user tructures
 * @param user_Database_Size - number of users in user_Database
 * @param sales_Array - an array of doubles which represent each
 *                      user's sales
*/
void
display_Table_Based_On_Money (userType user_Database[], 
                              int      user_Database_Size,
                              float    sales_Array[])
{
    // local variable declaration
    int user_Width_Array[] = {19, 20, 15}; // array of the widths of the values 
                                           // in the table

    int index;      // indexing value for later loop
    boolean first;  // represents if this is the first go through in the loop

    first = TRUE; // declares that it is the first run through

    // loop through the initialization and the entire array
    for (index = -1; index < user_Database_Size; index++)
    {
        // print the header at initialization
        if (first)
        {
            // display a horizontal border line
            display_Horizontal_Border_Line(3, user_Width_Array);

            first = FALSE; // says that it is no longer the first run through

            printf("\t| %-19s | %-20s | %-15s |\n", 
                   "ID", "NAME", "SALES");

        }

        // print the data in each column, if that is allowed to be
        // printed, i.e., if they have any sales
        else if (sales_Array[index] > 0)
        {
            // display a horizontal border line
            display_Horizontal_Border_Line(3, user_Width_Array);

            printf("\t| %19I64d | %-20s | %15.2lf |\n",
                   user_Database[index].user_ID,
                   user_Database[index].name,
                   sales_Array[index]);
        }
    }

    // cap it off with a final horizontal border line
    display_Horizontal_Border_Line(3, user_Width_Array);
}           