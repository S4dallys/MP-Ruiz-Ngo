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
    dateType date;
    dateType duration_Date_1;
    dateType duration_Date_2;

    long long user_ID;
    long long seller_ID;
    long long item_ID;
    long long addend;

    int  user_Database_Count;
    int  item_Database_Count;
    int  item_Cart_Count;
    int  update_Product_Count;
    int  seller_Product_Count;

    int  user_Product_Indices[20];
    int  user_Product_Count;
    int  update_Product_Indices[10];
    int  seller_Product_Indices[10];


    orderType  user_Cart[10];
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

    float   sales_Array[MAX_USERS];

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

    String15 low_Name_Copy1;
    String15 low_Name_Copy2;

    char   choice;
    int    item_Index;
    int    i;
    int    j;
    double new_price;
    double sum;
    // int    temp;

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
                                                    &new_price);

                                        if (new_price < 0)
                                            printf("ERROR: Item price cannot be zero.");
                                        else
                                            item_Database[item_Index].unit_Price = new_price;

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

                                memset(low_Category_Copy1, 0, 16);

                                prompt_StringN("Insert category: ", low_Category_Copy1, 15);
                                to_Lowercase(low_Category_Copy1, low_Category_Copy1);

                                choice = '\0';

                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    memset(low_Category_Copy2, 0, 16);

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

                                memset(low_Name_Copy1, 0, 16);

                                prompt_StringN("Insert keyword: ", low_Name_Copy1, 15);
                                to_Lowercase(low_Name_Copy1, low_Name_Copy1);

                                choice = '\0';

                                while (i < item_Database_Count && choice != 'X' && choice != 'x')
                                {
                                    memset(low_Name_Copy2, 0, 16);

                                    to_Lowercase(item_Database[i].name, low_Name_Copy2);

                                    if (substring_Search(low_Name_Copy2, low_Name_Copy1))
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

                                        if (count_User_Items_Ordertype(user_Cart, item_Cart_Count, seller_ID) == 0)
                                        {
                                            printf("\tERROR: Seller not found.\n");
                                            let_Read();
                                        }

                                        else
                                        {
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
                                    case REMOVE_SPECIFIC_ITEM:
                                        prompt_Long_Long("Enter Item ID: ", &item_ID);

                                        if (give_Item_Index_Via_ID_In_Cart(user_Cart, item_ID, item_Cart_Count) == -1)
                                        {
                                            printf("\tERROR: Item not found/\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            for (i = 0; i < item_Cart_Count; i++)
                                            {
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
                                    case EDIT_QUANTITY:
                                        prompt_Long_Long("Enter Item ID: ", &item_ID);

                                        item_Index = give_Item_Index_Via_ID_In_Cart (user_Cart, 
                                                                                     item_ID, 
                                                                                     item_Database_Count);
                                        if (item_Index == -1)
                                        {
                                            printf("\tERROR: Item not found/\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            prompt_Long_Long("Enter new item quantity: ",
                                                             &user_Cart[item_Index].quantity_Desired);
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

                                prompt_Date (&date);

                                update_Product_Count = 0;

                                update_Product_Count = enumerate_Differing_Product (item_Database,
                                                                                    item_Database_Count,
                                                                                    user_Cart,
                                                                                    item_Cart_Count,
                                                                                    update_Product_Indices);
                                
                                if (update_Product_Count > 0)
                                {
                                    printf("\tWARNING: Updates found.\n");
                                    printf("\tUpdating...\n");
                                    new_Line();
                                    printf("\tUpdated Items:\n");
                                    printf("\t-------------------------------------------------\n");
                                    for (int i = 0; i < update_Product_Count; i++)
                                    {
                                        new_Line();
                                        printf("\t%d\n", i+1);
                                        new_Line();
                                        printf("\tOld:\n");
                                        display_Item(user_Cart[update_Product_Indices[i]].item);
                                        new_Line();
                                        printf("\tNew:\n");
                                        display_Item(item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                                          user_Cart[update_Product_Indices[i]].item.product_ID, 
                                                                                          item_Database_Count)]);
                                        new_Line();
                                        printf("\t-------------------------------------------------\n");

                                        user_Cart[update_Product_Indices[i]].item = item_Database[give_Item_Index_Via_ID(item_Database, 
                                                                                                                         user_Cart[update_Product_Indices[i]].item.product_ID, 
                                                                                                                         item_Database_Count)];
                                    }

                                    new_Line();
                                    printf("\tINFO: Cart updated!\n");
                                    printf("\tINFO: You can still go back to Edit Cart.\n");
                                    let_Read();
                                }

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
                                        prompt_Long_Long ("Insert seller ID: ", &seller_ID);

                                        seller_Product_Count = find_User_Product_In_Cart (user_Cart, item_Cart_Count, seller_ID, seller_Product_Indices);

                                        if (seller_Product_Count == 0)
                                        {
                                            printf("\tERROR: Seller not found.\n");
                                            let_Read();
                                        }

                                        else
                                        {                                                
                                            transaction.date = date;
                                            transaction.buyer_ID = user_ID;
                                            transaction.seller_ID = user_Cart[item_Index].item.seller_ID;
                                            transaction.items_Ordered = 0;

                                            for (i = 0; i < seller_Product_Count; i++)
                                            {
                                                if (user_Cart[seller_Product_Indices[i]].quantity_Desired > user_Cart[seller_Product_Indices[i]].item.quantity)
                                                {
                                                    printf("\tERROR: Item %c%s%c (ID#%I64d) is out of stock. Skipping item...\n", 
                                                        '"', user_Cart[seller_Product_Indices[i]].item.name, '"', 
                                                        user_Cart[seller_Product_Indices[i]].item.product_ID);
                                                }

                                                else
                                                {
                                                    transaction.transaction_Log[transaction.items_Ordered] = user_Cart[seller_Product_Indices[i]];
                                                    transaction.items_Ordered++;
                                                }

                                                if (transaction.items_Ordered == 5)
                                                {
                                                    display_Transaction (&transaction, user_Database, user_Database_Count);

                                                    for (j = 0; j < 5; j++)
                                                        item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                    
                                                    transaction_File_Pointer = fopen ("Transactions.dat", "ab");
                                                    fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                                    fclose (transaction_File_Pointer);
                                                }
                                            }

                                            if (transaction.items_Ordered != 0)
                                            {
                                                display_Transaction (&transaction, user_Database, user_Database_Count);

                                                for (j = 0; j < 5; j++)
                                                    item_Database[give_Item_Index_Via_ID(item_Database, transaction.transaction_Log[j].item.product_ID, item_Database_Count)].quantity -= transaction.transaction_Log[j].quantity_Desired;
                                                
                                                transaction_File_Pointer = fopen ("Transactions.dat", "ab");
                                                fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                                fclose (transaction_File_Pointer);
                                            }
                                            new_Line();
                                            let_Read();
                                        }
                                        break;

                                    // -------------------------------------------------------------
                                    case BUY_SPECIFIC_ITEM:
                                        prompt_Long_Long ("Insert item ID: ", &item_ID);

                                        item_Index = give_Item_Index_Via_ID_In_Cart (user_Cart, 
                                                                                     item_ID,
                                                                                     item_Cart_Count);
                                        
                                        if (item_Index == -1)
                                        {
                                            printf("\tERROR: Item not found.\n");
                                            let_Read();
                                        }

                                        else if (user_Cart[item_Index].item.quantity < 
                                                 user_Cart[item_Index].quantity_Desired)
                                        {
                                            printf("\tERROR: Item stocks less than desired.\n");
                                            let_Read();
                                        }

                                        else
                                        {
                                            transaction.date = date;
                                            transaction.buyer_ID = user_ID;
                                            transaction.items_Ordered = 1;
                                            transaction.transaction_Log[0] = user_Cart[item_Index];
                                            transaction.seller_ID = user_Cart[item_Index].item.seller_ID;

                                            display_Transaction (&transaction, user_Database, user_Database_Count);
                                            item_Database[give_Item_Index_Via_ID(item_Database, user_Cart[item_Index].item.product_ID, item_Database_Count)].quantity -= user_Cart[item_Index].quantity_Desired;
                                            let_Read();

                                            transaction_File_Pointer = fopen ("Transactions.dat", "ab");
                                            fwrite(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                            fclose (transaction_File_Pointer);
                                        }

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
                            cart_File_Pointer = fopen (user_Cart_Name, "wb");
                            fwrite(user_Cart, sizeof(orderType), item_Cart_Count, cart_File_Pointer);
                            fclose (cart_File_Pointer);
                        }

                        else
                        {
                            cart_File_Pointer = fopen (user_Cart_Name, "rb");
                            if (cart_File_Pointer != NULL)
                                remove(user_Cart_Name);
                            fclose (cart_File_Pointer);
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
                            sum = 0;
                            transaction_File_Pointer = fopen ("Transactions.dat", "rb");
                            if (transaction_File_Pointer == NULL)
                                printf("\tERROR: Transaction file does not exist.\n");
                            else
                            {
                                printf("\tStarting Date:\n");
                                prompt_Date(&duration_Date_1);
                                new_Line();
                                printf("\tEnd Date:\n");
                                prompt_Date(&duration_Date_2);
                                if (compare_Date(duration_Date_1, duration_Date_2) != -1 ||
                                    compare_Date(duration_Date_1, duration_Date_2) != 0)
                                {
                                    printf("\tERROR: Invalid date bounds.\n");
                                    let_Read();
                                }
                                else
                                {
                                    fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    while (!feof(transaction_File_Pointer))
                                    {
                                        if (!(compare_Date(transaction.date, duration_Date_1) == -1 ||
                                            compare_Date(transaction.date, duration_Date_2) == 1))
                                            sum += transaction.amount;
                                        fread(&transaction, sizeof(transactionType), 1, transaction_File_Pointer);
                                    }
                                    new_Line();
                                    printf("\tTotal Sales from %04d-%02d-%02d to %04d-%02d-%02d: %f",
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
