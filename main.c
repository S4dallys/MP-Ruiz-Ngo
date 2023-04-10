/********** INTRODUCTORY DIVISION **********/ 

/*******************************************/

// main header
#include "main.h"

// main
int 
main() 
{
    userType  user_Database [MAX_USERS];  // user array
    itemType  item_Database [MAX_ITEMS];  // item array
  
    transactionType transaction; // transaction instance
    dateType date;               // date instance
    dateType duration_Date_1;    // duration date, earlier than date 2
    dateType duration_Date_2;    // duration date, after date 1

    long long user_ID;   // user ID instance
    long long seller_ID; // seller ID instance
    long long item_ID;   // item ID instance
    long long addend;    // temporary long long variable

    int  user_Database_Count;  // amount of users in user_Database
    int  item_Database_Count;  // amount of users in item_Database
    int  item_Cart_Count;      // amount of orders in the cart
    int  update_Product_Count; // amount of items in the cart which have been updated
    int  seller_Product_Count; 
    int  user_Product_Count;   
    int  unique_Sellers_Count; // amount of unique sellers

    int  user_Product_Indices[20];
    int  update_Product_Indices[10];   // array of indexes of products updated
    int  seller_Product_Indices[10];   
    long long  unique_Sellers_IDs[10]; // array of unique seller IDs


    orderType  user_Cart[10];  // user cart
    String30   user_Cart_Name; // name of the user's cart name
    String15   password;       // bin for password

    // self-explanatory Boolean variables, used either as sentinel values or loop conditions
    boolean  done;             // loop condition for main program
    boolean  user_Done;        // loop condition for user menu
    boolean  sell_Done;        // loop condition for sell menu
    boolean  buy_Done;         // loop condition for buy menu
    boolean  edit_Stock_Done;  // loop condition for edit stock menu
    boolean  edit_Cart_Done;   // loop condition for edit cart menu
    boolean  check_Out_Done;   // loop condition for check out menu
    boolean  admin_Done;       // loop condition for admin menu
    boolean  valid_Input;      // sentinel value for valid inputs
    boolean  has_Inputted;     // sentinel value for inputs

    boolean permissions_Array[MAX_USERS]; // array of Boolean values

    float   sales_Array[MAX_USERS]; // array of user sales
    float   spend_Array[MAX_USERS]; // array of user spending

    FILE *  user_File_Pointer;         // file pointer for user file
    FILE *  item_File_Pointer;         // file pointer for item file
    FILE *  cart_File_Pointer;         // file pointer for cart file
    FILE *  transaction_File_Pointer;  // file pointer for transaction file

    // arrays of menu choices to the indicated menus
    String30 main_Menu_Choices[4] =  {"Register as a User",
                                      "User Menu",
                                      "Admin Menu",
                                      "Exit"};

    String30 user_Menu_Choices[3] =  {"Sell Menu",
                                      "Buy Menu", 
                                      "Exit"};

    String30 sell_Menu_Choices[5] =  {"Add New Item", 
                                      "Edit Stock",
                                      "Show My Products",
                                      "Show My Low Stock Products",
                                      "Exit Sell Menu"};
    
    String30 buy_Menu_Choices[8] =   {"View All Products",
                                      "Show Products by Certain Seller",
                                      "Search Products by Category",
                                      "Search Products by Name",
                                      "Add to Cart",
                                      "Edit Cart",
                                      "Check Out Menu",
                                      "Exit Buy Menu"};

    String30 edit_Stock_Choices[6] = {"Replenish", 
                                      "Change Price",
                                      "Change Item Name",
                                      "Change Category",
                                      "Change Description",
                                      "Finish Editing"};

    String30 edit_Cart_Choices[4] =  {"Remove All Items Of Seller",
                                      "Remove Specific Item",
                                      "Edit Quantity",
                                      "Finish Edit Cart"};

    String30 check_Out_Choices[4] =  {"All",
                                      "By a Specific Seller",
                                      "Specific Item",
                                      "Exit Check Out"};

    String30 admin_Menu_Choices[6] = {"Show All Users",
                                      "Show All Sellers",
                                      "Show Total Sales in Period",
                                      "Show Sellers Sales",
                                      "Show Shopaholics",
                                      "Back to Main Menu"};

    String15 low_Category_Copy1; // will contain a lowercase version of a category
    String15 low_Category_Copy2; // will contain a lowercase version of a category

    String15 low_Name_Copy1; // will contain a lowercase version of a name
    String15 low_Name_Copy2; // will contain a lowercase version of a name

    char   choice; // represents a choice
    int    item_Index; // represents an index of an item structure in an array
    int    i; // looping variable for later loops
    int    j; // looping variable for later loops
    int    k; // looping variable for later loops
    double new_price; // bin for a price
    double sum;       // receptacle for a sum

    // Initialize USER DATABASE
    user_File_Pointer = fopen ("Users.txt", "r"); // open the file pointer on read mode

    // if the file does not exist, set the number of users to zero
    if (user_File_Pointer == NULL)
        user_Database_Count = 0;
    // else, download the users and set the number of users as per the users in the file
    else
        initialize_User_Database (user_File_Pointer, 
                                  user_Database, 
                                  &user_Database_Count);

    fclose (user_File_Pointer); // close the file pointer

    // Initialize ITEM DATABASE
    item_File_Pointer = fopen ("Items.txt", "r"); // open the file pointer on read mode

    // if the file does not exist, set the number of items to zero
    if (item_File_Pointer == NULL)
        item_Database_Count = 0;

    // else, download the items and set the number of items as per the items in the file
    else
        initialize_Item_Database (item_File_Pointer, 
                                  item_Database, &item_Database_Count);

    fclose (item_File_Pointer); // close the file pointer

    done = FALSE; // assumes the user is not done

    // loops while the user is not done
    do
    {
        // sorts the users in the array by their ID
        sort_Users_By_ID(user_Database, user_Database_Count);

        // displays the main menu and asks for a choice
        choice = display_Menu ("Main", main_Menu_Choices, 4);

        // activates certain commands based on the user's choices
        switch (choice)
        {

        //------------------------------------------------------------------------------------------
        case USER_REGISTRATION: 
            // registers the user into the database of users
            if (user_Database_Count < MAX_USERS)
                register_User(user_Database, &user_Database_Count);
            // shows an error if the max amount of users is reached and array cannot handle any more
            else
            {
                printf("\tERROR: Max users reached!\n");
                let_Read(); // lets the user read the error message
            }
            break;
        
        //------------------------------------------------------------------------------------------
        case USER_MODE: 
            // allow to user menu if login is successful (if not, function will display an error)
            if (login_User(user_Database, user_Database_Count, &user_ID) == VALID)
            {
                // create a name for the user's cart file
                sprintf(user_Cart_Name, "%I64d.bag", user_ID);

                // download the contents of the user's cart
                load_User_Cart(user_Cart_Name, user_Cart, &item_Cart_Count);

                // assume the user is not done
                user_Done = FALSE;
                
                do
                {
                    // get a choice from the user
                    choice = display_Menu ("User", user_Menu_Choices, 3);

                    // activate commands based on the user's choice
                    switch (choice)
                    {

                    // -----------------------------------------------------------------------------
                    // activates the sell menu
                    case SELL_MENU:

                        // assumes the user is not yet done
                        sell_Done = FALSE;

                        // loops while user is not yet done
                        do
                        {
                            // gets the users products
                            user_Product_Count = find_User_Product(item_Database, 
                                                                    item_Database_Count, 
                                                                    user_ID, 
                                                                    user_Product_Indices);
                            
                            // arranges the products in the array based on their ID
                            sort_Item_Array_By_ID (item_Database, 
                                                user_Product_Indices, 
                                                user_Product_Count);
                            
                            // displays the sell menu and asks for a choice
                            choice = display_Menu ("Sell", sell_Menu_Choices, 5);

                            // activate commands based on the user's choice
                            switch (choice)
                            {
                            
                            // ---------------------------------------------------------------------
                            // adds a new item
                            case ADD_NEW_ITEM:

                                // counts user's items and checks if item addition is possible
                                if (count_User_Items(item_Database, 
                                                    item_Database_Count, 
                                                    user_ID) >= 20)
                                {
                                    printf("\tERROR: Max capacity for items sold reached.\n");
                                    let_Read();
                                }     
                                else
                                    // registers product if seller has less than 20 products at 
                                    // count
                                    register_Product(item_Database, &item_Database_Count, user_ID);
                                    
                                break;
                            
                            // ---------------------------------------------------------------------
                            // edits stock
                            case EDIT_STOCK:

                              // checks if user does have stock  
                              if (user_Product_Count <= 0)
                              {
                                // error message display
                                printf("\tERROR: No product being sold.\n"); // error message display
                                let_Read();
                              }

                              // activates if user has stock     
                              else
                              {
                                // sentinel value initialization
                                edit_Stock_Done = FALSE;
                                has_Inputted = FALSE;
                                
                                // loops while user is not yet done
                                do
                                {   
                                // shows all of user's products
                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                
                                // assumes a valid input
                                valid_Input = TRUE;
                                    
                                    // asks for a valid item ID from the user
                                    do
                                    {          
                                        // displays error message if user previously gave erroneous
                                        // input
                                        if (!valid_Input)
                                            printf("\tInvalid Input.\n");

                                        // asks for item ID
                                        prompt_Long_Long("Insert product ID: ", &item_ID);
                                    
                                        // checks if ID in list of seller products
                                        valid_Input = find_Product_In_List(item_Database, 
                                                                            item_ID, 
                                                                            user_Product_Indices, 
                                                                            user_Product_Count);
                                    
                                        // activates once valid ID is given
                                        if (valid_Input)
                                        {
                                            // ends the loop this command is in
                                            has_Inputted = TRUE;

                                            // gets the index of the item based on its ID
                                            item_Index = give_User_Item_Index_Via_ID (item_Database, 
                                                                                item_ID, 
                                                                                user_Product_Indices, 
                                                                                user_Product_Count);
                                        }
                                                    
                                    } while (!valid_Input && !has_Inputted);
                                    
                                    // displays edit stock menu and asks for a choice
                                    choice = display_Menu("Edit Stock", edit_Stock_Choices, 6);

                                    // activate commands based on the user's choice      
                                    switch (choice)
                                    {

                                    // -------------------------------------------------------------
                                    // replenishes item based on inputted value
                                    // Precondition: addend must be positive or 0
                                    case REPLENISH:
                                        // asks how much is to be added
                                        prompt_Long_Long("\nHow many would you like to add? ", 
                                                          &addend);
                                                          
                                        // catches erroneous values (inputs less than 0)
                                        if (addend < 0)
                                            // adds if value is valid
                                            item_Database[item_Index].quantity += addend;

                                        // shows an error mesage otherwise
                                        else  
                                        {
                                            printf("\tERROR: Negative amount.\n");
                                            let_Read();
                                        }

                                        break;
                                    
                                    // -------------------------------------------------------------
                                    // changes price
                                    case CHANGE_PRICE:

                                        // asks for new price
                                        prompt_Double("\nWhat is the new price? ", 
                                                    &new_price);

                                        // sees if the price is less than zero
                                        if (new_price < 0)
                                            // gives an error message if so
                                            printf("ERROR: Item price cannot be less than zero.");
                                        else
                                            // changes the price otherwise
                                            item_Database[item_Index].unit_Price = new_price;

                                        break;

                                    // -------------------------------------------------------------  
                                    // changes item's name   
                                    case CHANGE_ITEM_NAME:
                                        // asks for the new name and stores it
                                        prompt_StringN("\nWhat is the new name? ", 
                                                        item_Database[item_Index].name, 20);

                                        break;

                                    // -------------------------------------------------------------    
                                    // changes item's category       
                                    case CHANGE_CATEGORY:
                                        // asks for a new category and stores it
                                        prompt_StringN("\nWhat is the new category? ", 
                                                        item_Database[item_Index].category, 
                                                        15);

                                        break;

                                    // -------------------------------------------------------------    
                                    // changes item's description          
                                    case CHANGE_DESCRIPTION:
                                        // asks for a new description and stores it
                                        prompt_StringN("\nWhat is the new description? ", 
                                                        item_Database[item_Index].description, 
                                                        30);

                                        break;

                                    // ------------------------------------------------------------- 
                                    // finish editing        
                                    case FINISH_EDITING:
                                        // ends the loop this command is in
                                        edit_Stock_Done = TRUE;

                                        break;              
                                    }
                                                
                                } while (!edit_Stock_Done);
                            }              
                            break;
                            
                            // ---------------------------------------------------------------------
                            // shows user's products
                            case SHOW_MY_PRODUCTS:
                                // displays the table of products
                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                
                                new_Line();

                                // lets the user see the table before proceeding
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // shows user's low stock products
                            case SHOW_MY_LOW_STOCK:

                                i = 0; // initializes indexing variable

                                // goes through user's items while the user has not yet 
                                // inputted x
                                while (i < user_Product_Count && (choice != 'X' || choice != 'x'))
                                {
                                    // checks if the quantity of an item is less than 5
                                    if (item_Database[user_Product_Indices[i]].quantity < 5)
                                    {
                                        // displays the item
                                        display_Item(item_Database[user_Product_Indices[i]]);
                                        new_Line();

                                        // asks the user for a choice of exiting or going to the next
                                        // item
                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", 
                                                    &choice);

                                        // goes to the next item if user inputs 'N' or 'n'
                                        if (choice == 'N' || choice == 'n')
                                            i++;
                                    }
                                    // skips the item if its quantity is 5 and above
                                    else i++;   
                                }

                                // says that nothing follows once user has reached end of list
                                printf("Nothing follows...\n");

                                // allows user to read outputs before proceeding
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // exits sell menu
                            case EXIT_SELL:
                                // ends the loop for the sell menu
                                sell_Done = TRUE;

                                break;       
                            }      
                                
                        } while (!sell_Done);
                            
                        break;
                    
                    // -----------------------------------------------------------------------------
                    // initializes buy menu
                    case BUY_MENU:
                        // assumes user is not done with buy menu
                        buy_Done = FALSE;
                        
                        // loops while user is not yet done
                        do
                        {
                            // displays buy menu choices and asks for choice
                            choice = display_Menu("Buy", buy_Menu_Choices, 8);
                            
                            // activate commands based on the user's choice
                            switch (choice)
                            {
                            
                            // ---------------------------------------------------------------------
                            // views all the products in the item array
                            case VIEW_ALL_PRODUCTS:
                                // sorts the user array by their ID
                                sort_Users_By_ID(user_Database, user_Database_Count);

                                i = 0; // indexing variable initialization

                                // loops through the users while user wishes to do so
                                while (i < user_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    // counts the amount of items the user has
                                    user_Product_Count = count_User_Items(item_Database, item_Database_Count,  
                                                                        user_Database[i].user_ID);

                                    // if user has a product
                                    if (user_Product_Count > 0)
                                    {
                                        // record the products and the number of such
                                        find_User_Product(item_Database, item_Database_Count, 
                                                        user_Database[i].user_ID, user_Product_Indices);

                                        // show the seller's ID
                                        printf ("\tUser ID: %I64d\n", user_Database[i].user_ID);
                                        new_Line();

                                        // display the products in a table
                                        display_Table_Ala_Show_My_Products(item_Database, user_Product_Indices, 
                                                                            user_Product_Count);
                                        new_Line();

                                        // ask user if they wish to proceed or exit
                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);
                                        
                                        // proceed to the next user if the user wishes to
                                        if (choice == 'N' || choice == 'n') i++;
                                    }

                                    // skip users which have no products
                                    else i++;     
                                }

                                // show that nothing follows
                                printf("Nothing follows...\n");
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // show products of certain seller
                            case USE_SELLER_LENS:
                                // ask for seller ID
                                prompt_Long_Long("Insert Seller ID: ", &seller_ID);
                                new_Line();

                                // counts the amount of products the user has
                                user_Product_Count = count_User_Items (item_Database, 
                                                                       item_Database_Count, 
                                                                       seller_ID);

                                if (user_Product_Count > 0)
                                {
                                    // finds the sellers products and stores them in an array
                                    find_User_Product(item_Database, item_Database_Count, 
                                                    seller_ID, user_Product_Indices);

                                    // displays the sellers products in a table
                                    display_Table_Ala_Show_My_Products (item_Database, 
                                                                        user_Product_Indices, 
                                                                        user_Product_Count);
                                    new_Line();
                                }

                                // shows an error message if they have no products
                                else
                                    printf ("\tERROR: User has no products.\n");

                                // lets the user read the outputs before proceeding
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // search by category
                            case USE_CATEGORY_LENS:
                                i = 0; // initialize indexing variable

                                // initialize string with null bytes
                                memset(low_Category_Copy1, 0, 16);

                                // ask for category
                                prompt_StringN("Insert category: ", low_Category_Copy1, 15);

                                // set it to lowercase
                                to_Lowercase(low_Category_Copy1, low_Category_Copy1);

                                // initialize choice
                                choice = '\0';

                                // loop through item array until user wants to exit
                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    // initialize bin for category of item
                                    memset(low_Category_Copy2, 0, 16);

                                    // set it to lowercase
                                    to_Lowercase(item_Database[i].category, low_Category_Copy2);

                                    // see if they are the same
                                    if (strcmp(low_Category_Copy1, low_Category_Copy2) == 0)
                                    {
                                        // show the item
                                        display_Item(item_Database[i]);
                                        new_Line();

                                        // ask user if they want to go to the next one or if they 
                                        // want to exit
                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);

                                        // go to the next if they want to go to the next one
                                        if (choice == 'N' || choice == 'n') i++;
                                    }

                                    // skip items with unmatching categories
                                    else i++;
                                }

                                // show that nothing follows
                                printf("Nothing follows...\n");
                                
                                // lets the user read the outputs before proceeding
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // search by item name
                            case USE_NAME_LENS:
                                i = 0; // initialize indexing variable

                                // initialize string with null bytes
                                memset(low_Name_Copy1, 0, 16);

                                // ask for keyword in name
                                prompt_StringN("Insert keyword: ", low_Name_Copy1, 15);

                                // set it to lower case
                                to_Lowercase(low_Name_Copy1, low_Name_Copy1);

                                // initialize choice
                                choice = '\0';

                                // loop through item array until user wants to exit
                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    // initialize bin for name of item
                                    memset(low_Name_Copy2, 0, 16);

                                    // set it to lowercase
                                    to_Lowercase(item_Database[i].name, low_Name_Copy2);

                                    // see if the keyword is a substring to the name
                                    if (substring_Search(low_Name_Copy2, low_Name_Copy1))
                                    {
                                        // display if so
                                        display_Item(item_Database[i]);
                                        new_Line();

                                        // ask user if they want to go to the next one or if they 
                                        // want to exit
                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);

                                        // go to the next if they want to go to the next one
                                        if (choice == 'N' || choice == 'n') i++;
                                    }

                                    // skip items if it does not have the keyword
                                    else i++;
                                }

                                // show that nothing follows
                                printf("Nothing follows...\n");

                                // lets the user read the outputs before proceeding
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            // adds item to cart
                            case ADD_TO_CART:
                                // checks if cart can handle any more items
                                if (item_Cart_Count >= 10)
                                {
                                    // shows error message
                                    printf("\tERROR: Only 10 items allowed in the cart at a time.\n");

                                    // shows advice
                                    printf("\tINFO:Please Edit Cart or Checkout first before adding another item.\n");

                                    // lets the user read the outputs before proceeding
                                    let_Read();
                                }     

                                // adds item to cart if possible
                                else
                                {
                                    add_Item_To_Cart (item_Database, 
                                                      user_Cart, 
                                                      item_Database_Count, 
                                                      &item_Cart_Count, 
                                                      user_ID);
                                }

                                break;

                            // ---------------------------------------------------------------------
                            // lets user edit cart
                            case EDIT_CART:

                                // shows an error message if cart is empty
                                if (item_Cart_Count <= 0)
                                    printf("\tERROR: Cart is empty.\n");
                                
                                else
                                {
                                    // initialization of sentinel values
                                    edit_Cart_Done = FALSE;
                                    valid_Input = TRUE;

                                    do
                                    {   
                                        // shows product table       
                                        display_Product_Table (user_Cart, item_Cart_Count);

                                        // shows edit cart menu and asks for a choice
                                        choice = display_Menu("Cart Edit", edit_Cart_Choices, 4);
                                        
                                        // activate commands based on the user's choice
                                        switch (choice)
                                        {
                                        
                                        // -------------------------------------------------------------
                                        // removes products of seller from cart
                                        case REMOVE_ITEMS_OF_SELLER:
                                            // asks for seller ID
                                            prompt_Long_Long ("Enter Seller ID:", &seller_ID);

                                            // shows error message if seller is not found
                                            if (find_User_Product_In_Cart(user_Cart, 
                                                                        item_Cart_Count, 
                                                                        seller_ID,
                                                                        seller_Product_Indices) == 0)
                                            {
                                                printf("\tERROR: Seller not found.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            else
                                            {
                                                // loops through the array
                                                for (i = 0; i < item_Cart_Count; i++)
                                                {
                                                    // swaps the item to the last element,
                                                    // decrementing the size of the readable array,
                                                    // "deleting" it
                                                    if (user_Cart[i].item.seller_ID == seller_ID)
                                                    {
                                                        for (j = i; j < item_Cart_Count; j++)
                                                        {
                                                            swap_Order(&user_Cart[j], &user_Cart[j+1]);
                                                        }
                                                        i--;
                                                        item_Cart_Count--;
                                                    }
                                                }

                                                // shows that operation is done
                                                printf("\tINFO: Items removed.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            break;
                                        
                                        // -------------------------------------------------------------
                                        // removes a specific item
                                        case REMOVE_SPECIFIC_ITEM:

                                            // asks for an item ID
                                            prompt_Long_Long("Enter Item ID: ", &item_ID);

                                            // shows error message if item is not found
                                            if (give_Item_Index_Via_ID_In_Cart(user_Cart, item_ID, item_Cart_Count) == -1)
                                            {
                                                printf("\tERROR: Item not found/\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            else
                                            {
                                                // loops through the array
                                                for (i = 0; i < item_Cart_Count; i++)
                                                {
                                                    // swaps the item to the last element,
                                                    // decrementing the size of the readable array,
                                                    // "deleting" it
                                                    if (user_Cart[i].item.product_ID == item_ID)
                                                    {
                                                        for (j = i; j < item_Cart_Count; j++)
                                                        {
                                                            swap_Order(&user_Cart[j], &user_Cart[j+1]);
                                                        }
                                                        i--;
                                                        item_Cart_Count--;
                                                    }
                                                }
                                            }

                                            break;
                                
                                        // -------------------------------------------------------------
                                        // edits quantity wanted
                                        case EDIT_QUANTITY:
                                            // asks for item ID
                                            prompt_Long_Long("Enter Item ID: ", &item_ID);

                                            // gets the index of item in cart
                                            item_Index = give_Item_Index_Via_ID_In_Cart (user_Cart, 
                                                                                        item_ID, 
                                                                                        item_Database_Count);

                                            // shows an error if the item is not found
                                            if (item_Index == -1)
                                            {
                                                printf("\tERROR: Item not found.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            // enters a new item quantity
                                            else
                                            {
                                                // assumes valid input is given
                                                valid_Input = TRUE;

                                                do  
                                                {
                                                    // shows an error message if invalid input is given
                                                    if (!valid_Input)
                                                        printf("\tERROR: Invalid input (must be greater than 0).\n");

                                                    // asks for a new quantity
                                                    prompt_Long_Long("Enter new item quantity: ",
                                                                &user_Cart[item_Index].quantity_Desired);

                                                    // if the input is invalid, it is marked so
                                                    if (user_Cart[item_Index].quantity_Desired <= 0)
                                                        valid_Input = FALSE;

                                                // continues until input is invalid
                                                } while (!valid_Input);
                                            }

                                            break;
                                        
                                        // -------------------------------------------------------------
                                        // finish editing cart
                                        case FINISH_EDIT_CART:
                                            edit_Cart_Done = TRUE; // exits loop

                                            break; 
                                        }
                                        
                                    } while (!edit_Cart_Done);
                                }
                                    
                                break;

                            
                            // ---------------------------------------------------------------------
                            // check out menu
                            case CHECK_OUT:

                                if (item_Cart_Count <= 0)
                                    printf ("\tERROR: Cart is empty.\n");
                                else
                                {
                                    // assumes user is not done checking out
                                    check_Out_Done = FALSE;

                                    // asks for date
                                    prompt_Date (&date);

                                    // assumes there are no updated products
                                    update_Product_Count = 0;

                                    // counts and gets updated products
                                    update_Product_Count = enumerate_Differing_Product (item_Database,
                                                                                        item_Database_Count,
                                                                                        user_Cart,
                                                                                        item_Cart_Count,
                                                                                        update_Product_Indices);
                                    
                                    // activated if there are any updated products
                                    if (update_Product_Count > 0)
                                    {
                                        // shows a warning
                                        printf("\tWARNING: Updates found.\n");

                                        // indicates that the program is updating the items
                                        printf("\tUpdating...\n");
                                        new_Line();

                                        // shows updated items
                                        printf("\tUpdated Items:\n");

                                        // shows border
                                        printf("\t-------------------------------------------------\n");
                                        for (int i = 0; i < update_Product_Count; i++)
                                        {
                                            new_Line();
                                            printf("\t%d\n", i+1); // shows a number for indexing and
                                                                // orderliness
                                                
                                            new_Line();

                                            // shows old item details
                                            printf("\tOld:\n");
                                            display_Item(user_Cart[update_Product_Indices[i]].item);
                                            new_Line();

                                            // shows new item details
                                            printf("\tNew:\n");
                                            display_Item(item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                                            user_Cart[update_Product_Indices[i]].item.product_ID, 
                                                                                            item_Database_Count)]);
                                            new_Line();

                                            // shows border
                                            printf("\t-------------------------------------------------\n");

                                            // updates item
                                            user_Cart[update_Product_Indices[i]].item = item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                                                                            user_Cart[update_Product_Indices[i]].item.product_ID, 
                                                                                                                            item_Database_Count)];
                                        }

                                        new_Line();

                                        // says the cart has been updated
                                        printf("\tINFO: Cart updated!\n");

                                        // says user can still edit cart
                                        printf("\tINFO: You can still go back to Edit Cart.\n");

                                        // lets the user read the outputs before proceeding
                                        let_Read();
                                    }

                                    // loops while user is not done
                                    do
                                    {    
                                        // shows check out menu choices and asks for choice
                                        choice = display_Menu("Check Out", check_Out_Choices, 4);
                                        
                                        // activate commands based on the user's choice
                                        switch (choice)
                                        {

                                        // -------------------------------------------------------------
                                        // buy all contents of cart
                                        case BUY_ALL:
                                            // counts and enumerates the unique sellers in user cart
                                            unique_Sellers_Count = enumerate_Unique_Sellers (user_Cart, item_Cart_Count, unique_Sellers_IDs);

                                            // goes through every unique seller
                                            for (k = 0; k < unique_Sellers_Count; k++)
                                            {
                                                // counts and enumerates the items that seller is selling
                                                // in the cart
                                                seller_Product_Count = find_User_Product_In_Cart (user_Cart, item_Cart_Count, unique_Sellers_IDs[k], seller_Product_Indices);

                                                // initialize transaction data                       
                                                transaction.date = date;
                                                transaction.buyer_ID = user_ID;
                                                transaction.seller_ID = seller_ID;
                                                transaction.items_Ordered = 0;

                                                // goes through the products of the seller
                                                for (i = 0; i < seller_Product_Count; i++)
                                                {
                                                    // skips items which cannot be fulfilled by the
                                                    // slated quantity
                                                    if (user_Cart[seller_Product_Indices[i]].quantity_Desired > user_Cart[seller_Product_Indices[i]].item.quantity)
                                                    {
                                                        // shows error message and declaration that it
                                                        // will skip that item
                                                        printf("\tERROR: Item %c%s%c (ID#%I64d) is out of stock. Skipping item...\n", 
                                                            '"', user_Cart[seller_Product_Indices[i]].item.name, '"', 
                                                            user_Cart[seller_Product_Indices[i]].item.product_ID);
                                                    }

                                                    // logs the item into the transaction, otherwise
                                                    else
                                                    {
                                                        transaction.transaction_Log[transaction.items_Ordered] = user_Cart[seller_Product_Indices[i]];
                                                        transaction.items_Ordered++;
                                                    }

                                                    if (transaction.items_Ordered == 5)
                                                    {
                                                        // displays the transaction
                                                        display_Transaction (&transaction, user_Database, user_Database_Count);

                                                        // updates the quantities of the items in the
                                                        // array to reflect the transaction
                                                        for (j = 0; j < 5; j++)
                                                            item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                        
                                                        // opens transaction file pointer
                                                        transaction_File_Pointer = fopen ("Transactions.dat", "ab");

                                                        // writes down transaction
                                                        fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                                        // closes file pointer
                                                        fclose (transaction_File_Pointer);

                                                        // resets the amount of items ordered
                                                        transaction.items_Ordered = 0;
                                                    }
                                                }

                                                // deals with the other items not dealt with the earlier
                                                // transaction round up
                                                if (transaction.items_Ordered != 0)
                                                {
                                                    // displays the transaction
                                                    display_Transaction (&transaction, user_Database, user_Database_Count);

                                                    // updates the quantities of the items in the
                                                    // array to reflect the transaction
                                                    for (j = 0; j < transaction.items_Ordered; j++)
                                                        item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                    
                                                    // opens transaction file pointer
                                                    transaction_File_Pointer = fopen ("Transactions.dat", "ab");

                                                    // writes down transaction
                                                    fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                                    // closes file pointer
                                                    fclose (transaction_File_Pointer);
                                                }
                                                new_Line();

                                                // lets the user read the outputs before proceeding
                                                let_Read();

                                                // swaps the item to the last element,
                                                // decrementing the size of the readable array,
                                                // "deleting" it, for all items of specified seller
                                                for (i = 0; i < item_Cart_Count; i++)
                                                {
                                                    if (user_Cart[i].item.seller_ID == unique_Sellers_IDs[k])
                                                    {
                                                        for (j = i; j < item_Cart_Count; j++)
                                                        {
                                                            swap_Order(&user_Cart[j], &user_Cart[j+1]);
                                                        }
                                                        i--;
                                                        item_Cart_Count--;
                                                    }
                                                }
                                            }

                                            break;

                                        // -------------------------------------------------------------
                                        // buy specific items from a seller
                                        case BUY_BY_CERTAIN_SELLER:

                                            // ask for seller ID
                                            prompt_Long_Long ("Insert seller ID: ", &seller_ID);

                                            // counts and enumerates the items that seller is selling
                                            // in the cart
                                            seller_Product_Count = find_User_Product_In_Cart (user_Cart, item_Cart_Count, seller_ID, seller_Product_Indices);

                                            // shows an error message if none of the items are being
                                            // offered by the seller
                                            if (seller_Product_Count == 0)
                                            {
                                                printf("\tERROR: Seller not found.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }


                                            else
                                            {                      
                                                // initializes transaction data                          
                                                transaction.date = date;
                                                transaction.buyer_ID = user_ID;
                                                transaction.seller_ID = seller_ID;
                                                transaction.items_Ordered = 0;

                                                // goes through the products of the seller
                                                for (i = 0; i < seller_Product_Count; i++)
                                                {
                                                    // skips items which cannot be fulfilled by the
                                                    // slated quantity
                                                    if (user_Cart[seller_Product_Indices[i]].quantity_Desired > user_Cart[seller_Product_Indices[i]].item.quantity)
                                                    {
                                                        // shows error message and declaration that it
                                                        // will skip that item
                                                        printf("\tERROR: Item %c%s%c (ID#%I64d) is out of stock. Skipping item...\n", 
                                                            '"', user_Cart[seller_Product_Indices[i]].item.name, '"', 
                                                            user_Cart[seller_Product_Indices[i]].item.product_ID);
                                                    }

                                                    // logs the item into the transaction, otherwise
                                                    else
                                                    {
                                                        transaction.transaction_Log[transaction.items_Ordered] = user_Cart[seller_Product_Indices[i]];
                                                        transaction.items_Ordered++;
                                                    }

                                                    // activates once theres enough items in a 
                                                    // transaction
                                                    if (transaction.items_Ordered == 5)
                                                    {
                                                        // displays the transaction
                                                        display_Transaction (&transaction, user_Database, user_Database_Count);

                                                        // updates the quantities of the items in the
                                                        // array to reflect the transaction
                                                        for (j = 0; j < 5; j++)
                                                            item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                        
                                                        // opens transaction file pointer
                                                        transaction_File_Pointer = fopen ("Transactions.dat", "ab");

                                                        // writes down transaction
                                                        fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                                        // closes file pointer
                                                        fclose (transaction_File_Pointer);

                                                        // resets the amount of items ordered
                                                        transaction.items_Ordered = 0;
                                                    }
                                                }

                                                // deals with the other items not dealt with the earlier
                                                // transaction round up
                                                if (transaction.items_Ordered != 0)
                                                {
                                                    // displays the transaction
                                                    display_Transaction (&transaction, user_Database, user_Database_Count);

                                                    // updates the quantities of the items in the
                                                    // array to reflect the transaction
                                                    for (j = 0; j < transaction.items_Ordered; j++)
                                                        item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                    
                                                    // opens transaction file pointer
                                                    transaction_File_Pointer = fopen ("Transactions.dat", "ab");

                                                    // writes down transaction
                                                    fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                                    // closes file pointer
                                                    fclose (transaction_File_Pointer);
                                                }
                                                new_Line();

                                                // lets the user read the outputs before proceeding
                                                let_Read();

                                                // swaps the item to the last element,
                                                // decrementing the size of the readable array,
                                                // "deleting" it, for all items of specified seller
                                                for (i = 0; i < item_Cart_Count; i++)
                                                {
                                                    if (user_Cart[i].item.seller_ID == seller_ID)
                                                    {
                                                        for (j = i; j < item_Cart_Count; j++)
                                                        {
                                                            swap_Order(&user_Cart[j], &user_Cart[j+1]);
                                                        }
                                                        i--;
                                                        item_Cart_Count--;
                                                    }
                                                }
                                            }
                                            break;

                                        // -------------------------------------------------------------
                                        // buy only a specific item
                                        case BUY_SPECIFIC_ITEM:
                                            // asks for item ID
                                            prompt_Long_Long ("Insert item ID: ", &item_ID);

                                            // gets the index of item in cart
                                            item_Index = give_Item_Index_Via_ID_In_Cart (user_Cart, 
                                                                                        item_ID,
                                                                                        item_Cart_Count);

                                            // shows an error if the item is not found
                                            if (item_Index == -1)
                                            {
                                                printf("\tERROR: Item not found.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            // shows an error if the item stocks cannot accomodate the
                                            // request
                                            else if (user_Cart[item_Index].item.quantity < 
                                                    user_Cart[item_Index].quantity_Desired)
                                            {
                                                printf("\tERROR: Item stocks less than desired.\n");

                                                // lets the user read the outputs before proceeding
                                                let_Read();
                                            }

                                            else
                                            {
                                                // initializes transaction data
                                                transaction.date = date;
                                                transaction.buyer_ID = user_ID;
                                                transaction.items_Ordered = 1;
                                                transaction.transaction_Log[0] = user_Cart[item_Index];
                                                transaction.seller_ID = user_Cart[item_Index].item.seller_ID;

                                                // displays the transaction
                                                display_Transaction (&transaction, user_Database, user_Database_Count);

                                                // updates the quantities of the item in the database
                                                // to reflect the user buying it
                                                item_Database[give_Item_Index_Via_ID(item_Database, user_Cart[item_Index].item.product_ID, item_Database_Count)].quantity -= user_Cart[item_Index].quantity_Desired;
                                                
                                                // lets the user read the outputs before proceeding
                                                let_Read();

                                                // swaps the item to the last element,
                                                // decrementing the size of the readable array,
                                                // "deleting" it
                                                for (i = 0; i < item_Cart_Count; i++)
                                                {
                                                    if (user_Cart[i].item.product_ID == transaction.transaction_Log[0].item.product_ID)
                                                    {
                                                        for (j = i; j < item_Cart_Count; j++)
                                                        {
                                                            swap_Order(&user_Cart[j], &user_Cart[j+1]);
                                                        }
                                                        i--;
                                                        item_Cart_Count
                                                        --;
                                                    }
                                                }

                                                // open transaction file pointer
                                                transaction_File_Pointer = fopen ("Transactions.dat", "ab");

                                                // writes down transaction
                                                fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                                // closes file pointer
                                                fclose (transaction_File_Pointer);
                                            }

                                            break;

                                        // -------------------------------------------------------------
                                        // exits user from check out menu
                                        case EXIT_CHECK_OUT:
                                            check_Out_Done = TRUE; // stops the loop

                                            break;
                                        }
                                        
                                    } while (!check_Out_Done);
                                }

                                break;
                            
                            // ---------------------------------------------------------------------
                            // exits the user from buy menu
                            case EXIT_BUY:
                                buy_Done = TRUE; // stops the loop

                                break;
                            }
                            
                        } while (!buy_Done);
                        
                        break;
                    
                    // -----------------------------------------------------------------------------
                    // exits user
                    case EXIT_USER:
                        user_Done = TRUE; // stops the loop

                        // activates if there are still items in the user's cart
                        if (item_Cart_Count > 0)
                        {
                            // open cart file pointer
                            cart_File_Pointer = fopen (user_Cart_Name, "wb");

                            // records the cart contents into the binary file
                            for (i = 0; i < item_Cart_Count; i++)
                                fwrite(&user_Cart[i], sizeof(orderType), 1, cart_File_Pointer);

                            // closes file pointer
                            fclose (cart_File_Pointer);
                        }

                        else
                        {
                            // open cart file pointer
                            cart_File_Pointer = fopen (user_Cart_Name, "rb");

                            // checks if user cart exists
                            if (cart_File_Pointer != NULL)
                                remove(user_Cart_Name); // removes it if so

                            // closes file pointer
                            fclose (cart_File_Pointer);
                        }
                        break;
                    }
                        
                } while (!user_Done);
                
            }

            break;
            
            // -------------------------------------------------------------------------------------
            // enters into the admin menu
            case ADMIN_MODE: 
                //asks for the admin's password
                prompt_StringN("Insert password: ", password, 15);

                // shows an error message if the admin password is incorrect
                if (strcmp(ADMIN_PASSWORD, password) != 0)
                {
                    printf("\tError: Invalid Password!\n");
                    let_Read();
                }

                // activates the admin menu if correct
                else
                {
                    // assumes the admin is not yet done with the menu
                    admin_Done = FALSE;

                    // loops while the admin is not yet done
                    do
                    {
                        // displays the choices from the admin menu and asks for a choice from the
                        // user
                        choice = display_Menu ("Admin", admin_Menu_Choices, 6);

                        // activates certain commands based on user input
                        switch (choice)
                        {

                        // -------------------------------------------------------------------------
                        // shows all of the users in tabular format, arranged in ascending order by
                        // their IDs
                        case SHOW_ALL_USERS:
                            display_User_Table(user_Database, user_Database_Count); // shows table
                            new_Line(); // shows new line
                            let_Read(); // lets the user read the table before proceeding
                            break;

                        // -------------------------------------------------------------------------
                        // shows all users which have items registered in the item array in tabular
                        // format
                        case SHOW_ALL_SELLERS:
                            // generates an array for all users which states if they have items or not
                            for (i = 0; i < user_Database_Count; i++)
                              permissions_Array[i] = count_User_Items (item_Database, 
                                                                       item_Database_Count, 
                                                                       user_Database[i].user_ID) > 0;
                            
                            // displays sellers based on the array made previously
                            display_User_Table_With_Conditions (user_Database, user_Database_Count,
                                                                permissions_Array);
                            new_Line();

                            // lets user see the output
                            let_Read();
                            break;

                        // -------------------------------------------------------------------------
                        // shows total sales in the duration
                        case SHOW_TOTAL_SALES_IN_GIVEN_DURATION:

                            sum = 0; // initializes bin for adding

                            // initializes file pointer
                            transaction_File_Pointer = fopen ("Transactions.dat", "rb");

                            // gives an error if the file is not found
                            if (transaction_File_Pointer == NULL)
                                printf("\tERROR: Transaction file does not exist.\n");

                            // proceeds if it is found
                            else
                            {
                                // asks for a startinf date
                                printf("\tStarting Date:\n");
                                prompt_Date(&duration_Date_1);
                                new_Line();

                                // asks for an ending date
                                printf("\tEnd Date:\n");
                                prompt_Date(&duration_Date_2);

                                // says date bounds given are invalid if user entered a later
                                // starting date than the former, gives an error
                                if (compare_Date(duration_Date_1, duration_Date_2) != -1 ||
                                    compare_Date(duration_Date_1, duration_Date_2) != 0)
                                {
                                    printf("\tERROR: Invalid date bounds.\n");
                                    let_Read();
                                }

                                else
                                {
                                    // reads transaction data from the file
                                    fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);

                                    // continues to read while not EOF
                                    while (!feof(transaction_File_Pointer))
                                    {
                                        // sees if the date is within the range
                                        if (!(compare_Date(transaction.date, duration_Date_1) == -1 ||
                                            compare_Date(transaction.date, duration_Date_2) == 1))
                                            sum += transaction.amount; // adds if so

                                        // reads more data
                                        fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    }

                                    // close file pointer
                                    fclose (transaction_File_Pointer);
                                    new_Line();

                                    // shows the total sales
                                    printf("\tTotal Sales from %04d-%02d-%02d to %04d-%02d-%02d: %.2f\n",
                                           duration_Date_1.year, duration_Date_1.month, duration_Date_1.day,
                                           duration_Date_2.year, duration_Date_2.month, duration_Date_2.day,
                                           sum);
                                    new_Line();
                                    let_Read();
                                }
                            }
                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_SELLERS_SALES:
                            // initializes sales array to be bin for addition
                            for (i = 0; i < MAX_USERS; i++)
                                sales_Array[i] = 0;

                            // initializes transaction file pointer
                            transaction_File_Pointer = fopen ("Transactions.dat", "rb");

                            // gives an error if the file is not found
                            if (transaction_File_Pointer == NULL)
                                printf("\tERROR: Transaction file does not exist.\n");

                            // proceeds if found
                            else
                                {
                                    // reads transaction
                                    fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    // continues to read while not end of line
                                    while (!feof(transaction_File_Pointer)) 
                                    {
                                        // adds sellers sales to the proper sales receptacle
                                        sales_Array[search_User(user_Database, 
                                                                user_Database_Count, 
                                                                transaction.seller_ID)] += transaction.amount;
                                        
                                        // continues to read data
                                        fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    }

                                    // closes transaction file pointer
                                    fclose (transaction_File_Pointer);
                                    new_Line();

                                    // displays table of sellers and their sales
                                    display_Table_Based_On_Money (user_Database, user_Database_Count, sales_Array);
                                    new_Line();

                                    // lets user read the table before proceeding
                                    let_Read();
                                }
                            
                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_SHOPAHOLICS:
                            // initializes spending array to be bin for addition
                            for (i = 0; i < MAX_USERS; i++)
                                spend_Array[i] = 0;
                            
                            // initializes transaction file pointer
                            transaction_File_Pointer = fopen ("Transactions.dat", "rb");
                            if (transaction_File_Pointer == NULL)
                                printf("\tERROR: Transaction file does not exist.\n");
                            
                            // proceeds if found
                            else
                                {
                                    // reads transaction
                                    fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    // continues to read while not end of line
                                    while (!feof(transaction_File_Pointer))
                                    {
                                        // adds buyer sales to the proper spend receptacle
                                        sales_Array[search_User (user_Database, 
                                                                 user_Database_Count, 
                                                                 transaction.buyer_ID)] += transaction.amount;

                                        // continues to read data
                                        fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    }

                                    // closes transaction file pointer
                                    fclose (transaction_File_Pointer);
                                    new_Line();

                                    // displays table of buyers and their spending
                                    display_Table_Based_On_Money (user_Database, user_Database_Count, sales_Array);
                                    new_Line();

                                    // lets user read the table before proceeding
                                    let_Read();
                                }

                            break;
                        
                        // -------------------------------------------------------------------------
                        case EXIT_ADMIN:
                            // exits the admin menu loop
                            admin_Done = TRUE;

                            break;
                        }
                    } while (!admin_Done);
                }

                break;
            
            // -------------------------------------------------------------------------------------
            // ends the loop
            case EXIT_PROGRAM:
                // displays an exit message
                printf("\tThank you for shopping with us! (uwu)\n");

                // uploads the items to Items.txt
                upload_Item_Database(item_Database, item_Database_Count);

                // uploads the users to Users.txt
                upload_User_Database(user_Database, user_Database_Count);

                // ends the main program loop
                done = TRUE;

                break;
            }

        } while (!done);
    
    return 0;
}
