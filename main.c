/********** INTRODUCTORY DIVISION **********/ 

/*******************************************/

// main header
#include "main.h"

// main
int 
main() 
{
    userType  user_Database [MAX_USERS];
    itemType  item_Database [MAX_ITEMS];

    transactionType transaction;

    long long user_ID;
    long long seller_ID;
    long long item_ID;
    long long addend;

    int  user_Database_Count;
    int  item_Database_Count;
    int  item_Cart_Count;
    int  update_Product_Count;

    int  user_Product_Indices[20];
    int  user_Product_Count;
    int  update_Product_Indices[10];

    itemType   user_Cart[10];
    String30   user_Cart_Name;
    String15   password;

    boolean  done;
    boolean  user_Done;
    boolean  sell_Done;
    boolean  buy_Done;
    boolean  edit_Stock_Done;
    boolean  edit_Cart_Done;
    boolean  check_Out_Done;
    boolean  admin_Done;
    boolean  valid_Input;
    boolean  has_Inputted;

    boolean permissions_Array[MAX_USERS];

    FILE *  user_File_Pointer;
    FILE *  item_File_Pointer;
    FILE *  cart_File_Pointer;
    FILE *  transaction_File_Pointer;

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

    String15 low_Category_Copy1;
    String15 low_Category_Copy2;

    char  choice;
    int   item_Index;
    int   i;

    // Initialize USER DATABASE
    user_File_Pointer = fopen ("Users.txt", "r");

    if (user_File_Pointer == NULL)
        user_Database_Count = 0;
    else
        initialize_User_Database (user_File_Pointer, 
                                  user_Database, 
                                  &user_Database_Count);

    fclose (user_File_Pointer);

    // Initialize ITEM DATABASE
    item_File_Pointer = fopen ("Items.txt", "r");

    if (item_File_Pointer == NULL)
        item_Database_Count = 0;
    else
        initialize_Item_Database (item_File_Pointer, 
                                  item_Database, &item_Database_Count);

    fclose (item_File_Pointer);

    done = FALSE;

    do
    {
        
        sort_Users_By_ID(user_Database, user_Database_Count);
        choice = display_Menu ("Main", main_Menu_Choices, 4);

        switch (choice)
        {

        //------------------------------------------------------------------------------------------
        case USER_REGISTRATION: 
            register_User(user_Database, &user_Database_Count);
            break;
        
        //------------------------------------------------------------------------------------------
        case USER_MODE: 

            if (login_User(user_Database, user_Database_Count, &user_ID) == VALID)
            {
                sprintf(user_Cart_Name, "%I64d.bag", user_ID);
                load_User_Cart(user_Cart_Name, user_Cart, &item_Cart_Count);

                user_Done = FALSE;
                
                do
                {
                    choice = display_Menu ("User", user_Menu_Choices, 3);
                        
                    switch (choice)
                    {

                    // -----------------------------------------------------------------------------
                    case SELL_MENU:
                        sell_Done = FALSE;

                        do
                        {
                            user_Product_Count = find_User_Product(item_Database, 
                                                                    item_Database_Count, 
                                                                    user_ID, 
                                                                    user_Product_Indices);
                            
                            sort_Item_Array_By_ID (item_Database, 
                                                user_Product_Indices, 
                                                user_Product_Count);
                            
                            choice = display_Menu ("Sell", sell_Menu_Choices, 5);
                            
                            switch(choice)
                            {
                            
                            // ---------------------------------------------------------------------
                            case ADD_NEW_ITEM:
                                if (count_User_Items(item_Database, 
                                                    item_Database_Count, 
                                                    user_ID) > 20)
                                {
                                    printf("\tERROR: Max capacity for items sold reached.\n");
                                    let_Read();
                                }     
                                else
                                    register_Product(item_Database, &item_Database_Count, user_ID);
                                    
                                break;
                            
                            // ---------------------------------------------------------------------
                            case EDIT_STOCK:  
                              if (user_Product_Count <= 0)
                              {
                                printf("\tERROR: No product being sold.\n");
                                let_Read();
                              }     
                              else
                              {
                                edit_Stock_Done = FALSE;
                                has_Inputted = FALSE;
                                        
                                do
                                {   
                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                            
                                valid_Input = TRUE;
                                            
                                    do
                                    {          
                                        if (!valid_Input)
                                            printf("\tInvalid Input.\n");
                                    
                                        prompt_Long_Long("Insert product ID: ", &item_ID);
                                    
                                        valid_Input = find_Product_In_List(item_Database, 
                                                                            item_ID, 
                                                                            user_Product_Indices, 
                                                                            user_Product_Count);
                                    
                                        if (valid_Input)
                                        {
                                            has_Inputted = TRUE;
                                            item_Index = give_User_Item_Index_Via_ID (item_Database, 
                                                                                item_ID, 
                                                                                user_Product_Indices, 
                                                                                user_Product_Count);
                                        }
                                                    
                                    } while (!valid_Input && !has_Inputted);
                                                
                                    choice = display_Menu("Edit Stock", edit_Stock_Choices, 6);
                                                
                                    switch (choice)
                                    {

                                    // -------------------------------------------------------------
                                    case REPLENISH:
                                        prompt_Long_Long("\nHow many would you like to add? ", 
                                                          &addend);

                                        if (item_Database[item_Index].quantity + addend >= 0)
                                            item_Database[item_Index].quantity += addend;
                                        else  
                                        {
                                            printf("\t");
                                            printf("Error: Amount leads to value less than zero.");
                                            new_Line();
                                            let_Read();
                                        }

                                        break;
                                    
                                    // -------------------------------------------------------------
                                    case CHANGE_PRICE:
                                        prompt_Double("\nWhat is the new price? ", 
                                                    &item_Database[item_Index].unit_Price);

                                        break;

                                    // -------------------------------------------------------------     
                                    case CHANGE_ITEM_NAME:
                                        prompt_StringN("\nWhat is the new name? ", 
                                                        item_Database[item_Index].name, 20);

                                        break;

                                    // -------------------------------------------------------------           
                                    case CHANGE_CATEGORY:
                                        prompt_StringN("\nWhat is the new category? ", 
                                                        item_Database[item_Index].category, 
                                                        15);

                                        break;

                                    // -------------------------------------------------------------              
                                    case CHANGE_DESCRIPTION:
                                        prompt_StringN("\nWhat is the new description? ", 
                                                        item_Database[item_Index].description, 
                                                        30);

                                        break;

                                    // -------------------------------------------------------------         
                                    case FINISH_EDITING:
                                        edit_Stock_Done = TRUE;

                                        break;              
                                    }
                                                
                            } while (!edit_Stock_Done);
                            }              
                            break;
                            
                            // ---------------------------------------------------------------------
                            case SHOW_MY_PRODUCTS:
                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                new_Line();
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case SHOW_MY_LOW_STOCK:
                                i = 0;

                                while (i < user_Product_Count && (choice != 'X' || choice != 'x'))
                                {
                                    if (item_Database[user_Product_Indices[i]]
                                        .quantity < 5)
                                    {
                                        display_Item(item_Database[user_Product_Indices[i]]);
                                        new_Line();

                                        prompt_Char("Enter 'N' to go to next item, 'B' to go back, and 'X' to exit... ", 
                                                    &choice);

                                        if (choice == 'N' || choice == 'n')
                                        {
                                            i++;
                                        }
                                        else if (choice == 'B' || choice == 'b')
                                        {
                                            if (--i < 0)
                                            {
                                                printf("Nothing follows...\n");
                                                let_Read();
                                                i = 0;
                                            }
                                        }
                                    }
                                    else i++;   
                                }

                                printf("Nothing follows...\n");
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case EXIT_SELL:
                                sell_Done = TRUE;

                                break;       
                            }      
                                
                        } while (!sell_Done);
                            
                        break;
                    
                    // -----------------------------------------------------------------------------
                    case BUY_MENU:
                        buy_Done = FALSE;
                        
                        do
                        {
                            
                            choice = display_Menu("Buy", buy_Menu_Choices, 8);
                            
                            switch (choice)
                            {
                            
                            // ---------------------------------------------------------------------
                            case VIEW_ALL_PRODUCTS:
                                sort_Users_By_ID(user_Database, user_Database_Count);

                                i = 0;
                                while (i < user_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    user_Product_Count = count_User_Items(item_Database, item_Database_Count,  
                                                                        user_Database[i].user_ID);

                                    if (user_Product_Count > 0)
                                    {
                                        find_User_Product(item_Database, item_Database_Count, 
                                                        user_Database[i].user_ID, user_Product_Indices);

                                        printf ("\tUser ID: %I64d\n", user_Database[i].user_ID);
                                        new_Line();

                                        display_Table_Ala_Show_My_Products(item_Database, user_Product_Indices, 
                                                                            user_Product_Count);
                                        new_Line();

                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);
                                        
                                        if (choice == 'N' || choice == 'n') i++;
                                    }
                                    else i++;     
                                }

                                printf("Nothing follows...\n");
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case USE_SELLER_LENS:
                                prompt_Long_Long("Insert Seller ID: ", &user_ID);
                                new_Line();

                                user_Product_Count = count_User_Items (item_Database, 
                                                                       item_Database_Count, 
                                                                       user_ID);

                                find_User_Product(item_Database, item_Database_Count, 
                                                user_ID, user_Product_Indices);

                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                new_Line();
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case USE_CATEGORY_LENS:
                                i = 0;

                                prompt_StringN("Insert category: ", low_Category_Copy1, 15);
                                to_Lowercase(low_Category_Copy1, low_Category_Copy1);

                                choice = '\0';

                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    to_Lowercase(item_Database[i].category, low_Category_Copy2);

                                    if (strcmp(low_Category_Copy1, low_Category_Copy2) == 0)
                                    {
                                        display_Item(item_Database[i]);
                                        new_Line();

                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);

                                        if (choice == 'N' || choice == 'n') i++;
                                    }
                                    else i++;
                                }
                                printf("Nothing follows...\n");
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case USE_NAME_LENS:
                                i = 0;

                                prompt_StringN("Insert keyword: ", low_Category_Copy1, 15);
                                to_Lowercase(low_Category_Copy1, low_Category_Copy1);

                                choice = '\0';

                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    to_Lowercase(item_Database[i].category, low_Category_Copy2);

                                    if (substring_Search(low_Category_Copy2, low_Category_Copy1))
                                    {
                                        display_Item(item_Database[i]);
                                        new_Line();

                                        prompt_Char("Enter 'N' to go to next item, and 'X' to exit... ", &choice);

                                        if (choice == 'N' || choice == 'n') i++;
                                    }
                                    else i++;
                                }

                                printf("Nothing follows...\n");
                                let_Read();

                                break;
                            
                            // ---------------------------------------------------------------------
                            case ADD_TO_CART:
                                if (item_Cart_Count >= 10)
                                {
                                    printf("\tOnly 10 items allowed in the cart at a time.\n");
                                    printf("\tPlease Edit Cart or Checkout first before adding another item.\n");
                                    let_Read();
                                }     

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
                            case EDIT_CART:
                                edit_Cart_Done = FALSE;
                                valid_Input = TRUE;

                                do
                                {          
                                    display_Product_Table (user_Cart, item_Cart_Count);

                                    choice = display_Menu("Cart Edit", edit_Cart_Choices, 4);
                                    
                                    switch (choice)
                                    {
                                    
                                    // -------------------------------------------------------------
                                    case REMOVE_ITEMS_OF_SELLER:
                                        prompt_Long_Long ("Enter Seller ID:", &seller_ID);

                                        if (count_User_Items(user_Cart, item_Cart_Count, seller_ID) == 0)
                                        {
                                            printf("\tERROR: Seller not found.\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            for (i = 0; i < item_Cart_Count; i++)
                                            {
                                                if (user_Cart[i].seller_ID == seller_ID)
                                                {
                                                    swap_Item(&user_Cart[i], &user_Cart[item_Cart_Count-1]);
                                                    item_Cart_Count--;
                                                }
                                            }
                                        }

                                        break;
                                    
                                    // -------------------------------------------------------------
                                    case REMOVE_SPECIFIC_ITEM:
                                        prompt_Long_Long("Enter Item ID: ", &item_ID);

                                        if (give_Item_Index_Via_ID(user_Cart, item_ID, item_Database_Count) == -1)
                                        {
                                            printf("\tERROR: Item not found/\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            for (i = 0; i < item_Cart_Count; i++)
                                            {
                                                if (user_Cart[i].product_ID == item_ID)
                                                {
                                                    swap_Item(&user_Cart[i], &user_Cart[item_Cart_Count-1]);
                                                    item_Cart_Count--;
                                                }
                                            }
                                        }

                                        break;
                            
                                    // -------------------------------------------------------------
                                    case EDIT_QUANTITY:
                                        prompt_Long_Long("Enter Item ID: ", &item_ID);

                                        item_Index = give_Item_Index_Via_ID(user_Cart, item_ID, item_Database_Count);
                                        if ( item_Index == -1)
                                        {
                                            printf("\tERROR: Item not found/\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            prompt_Long_Long("Enter new item quantity: ",
                                                             &user_Cart[item_Index].quantity);
                                        }

                                        break;
                                    
                                    // -------------------------------------------------------------
                                    case FINISH_EDIT_CART:
                                        edit_Cart_Done = TRUE;

                                        break; 
                                    }
                                    
                                } while (!edit_Cart_Done);
                                    
                                break;
                            
                            // ---------------------------------------------------------------------
                            case CHECK_OUT:
                                check_Out_Done = FALSE;

                                // smt smh

                                do
                                {    
                                    choice = display_Menu("Check Out", check_Out_Choices, 4);
                                    
                                    switch (choice)
                                    {

                                    // -------------------------------------------------------------
                                    case BUY_ALL:
                                        //insert code here

                                        break;

                                    // -------------------------------------------------------------
                                    case BUY_BY_CERTAIN_SELLER:
                                        //insert code here

                                        break;

                                    // -------------------------------------------------------------
                                    case BUY_SPECIFIC_ITEM:
                                        //insert code here

                                        break;

                                    // -------------------------------------------------------------
                                    case EXIT_CHECK_OUT:
                                        check_Out_Done = TRUE;

                                        break;
                                    }
                                    
                                } while (!check_Out_Done);
                                    
                                break;
                            
                            // ---------------------------------------------------------------------
                            case EXIT_BUY:
                                buy_Done = TRUE;

                                break;
                            }
                            
                        } while (!buy_Done);
                        
                        break;
                    
                    // -----------------------------------------------------------------------------
                    case EXIT_USER:
                        user_Done = TRUE;
                        if (item_Cart_Count > 0)
                        {
                            //put stuff into cart
                        }

                        else
                        {
                            remove(user_Cart_Name);
                        }
                        break;
                    }
                        
                } while (!user_Done);
                
            }

            break;
            
            // -------------------------------------------------------------------------------------
            case ADMIN_MODE: 
                prompt_StringN("Insert password: ", password, 15);

                if (strcmp(ADMIN_PASSWORD, password) != 0)
                {
                    printf("\tError: Invalid Password!\n");
                    let_Read();
                }
                else
                {
                    admin_Done = FALSE;
                    do
                    {
                        system("cls");
                        choice = display_Menu ("Admin", admin_Menu_Choices, 6);
                        switch (choice)
                        {

                        // -------------------------------------------------------------------------
                        case SHOW_ALL_USERS:
                            display_User_Table(user_Database, user_Database_Count);
                            new_Line();
                            let_Read();
                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_ALL_SELLERS:
                            for (i = 0; i < user_Database_Count; i++)
                              permissions_Array[i] = count_User_Items (item_Database, 
                                                                       item_Database_Count, 
                                                                       user_Database[i].user_ID) > 0;
                            display_User_Table_With_Conditions (user_Database, user_Database_Count,
                                                                permissions_Array);
                            new_Line();
                            let_Read();
                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_TOTAL_SALES_IN_GIVEN_DURATION:
                            //insert code here

                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_SELLERS_SALES:
                            //insert code here

                            break;

                        // -------------------------------------------------------------------------
                        case SHOW_SHOPAHOLICS:
                            //insert code here

                            break;
                        
                        // -------------------------------------------------------------------------
                        case EXIT_ADMIN:
                            admin_Done = TRUE;

                            break;
                        }
                    } while (!admin_Done);
                }

                break;
            
            // -------------------------------------------------------------------------------------
            case EXIT_PROGRAM:
                upload_Item_Database(item_Database, item_Database_Count);
                upload_User_Database(user_Database, user_Database_Count);

                done = TRUE;

                break;
            }

        } while (!done);
    
    return 0;
}
