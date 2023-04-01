/********** INTRODUCTORY DIVISION **********/ //-------------------------------

/********** HEADER AND DEFINITIONS DIVISION **********/ //---------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_ITEMS 100 * 20

#define TRUE 1
#define FALSE 0
#define VALID TRUE

#define USER_REGISTRATION 'A'
#define USER_MODE         'B'
#define ADMIN_MODE        'C'
#define EXIT_PROGRAM      'D'

#define SELL_MENU 'A'
#define BUY_MENU  'B'
#define EXIT_USER 'C'

#define ADD_NEW_ITEM      'A'
#define EDIT_STOCK        'B'
#define SHOW_MY_PRODUCTS  'C'
#define SHOW_MY_LOW_STOCK 'D'
#define EXIT_SELL         'E'

#define VIEW_ALL_PRODUCTS 'A'
#define USE_SELLER_LENS   'B'
#define USE_CATEGORY_LENS 'C'
#define USE_NAME_LENS     'D'
#define ADD_TO_CART       'E'
#define EDIT_CART         'F'
#define CHECK_OUT         'G'
#define EXIT_BUY          'H'

#define REPLENISH          'A'
#define CHANGE_PRICE       'B'
#define CHANGE_ITEM_NAME   'C'
#define CHANGE_CATEGORY    'D'
#define CHANGE_DESCRIPTION 'E'
#define FINISH_EDITING     'F'

#define REMOVE_ITEMS_OF_SELLER 'A'
#define REMOVE_SPECIFIC_ITEM   'B'
#define EDIT_QUANTITY          'C'
#define FINISH_EDIT_CART       'D'

#define BUY_ALL               'A'
#define BUY_BY_CERTAIN_SELLER 'B'
#define BUY_SPECIFIC_ITEM     'C'
#define EXIT_CHECK_OUT        'D'

#define SHOW_ALL_USERS                     'A'
#define SHOW_ALL_SELLERS                   'B'
#define SHOW_TOTAL_SALES_IN_GIVEN_DURATION 'C'
#define SHOW_SELLERS_SALES                 'D'
#define SHOW_SHOPAHOLICS                   'E'
#define EXIT_ADMIN                         'F'

#define ADMIN_PASSWORD "H3LLo?"
  
typedef char String10 [11];
typedef char String15 [16];
typedef char String20 [21];
typedef char String30 [31];

typedef int boolean;

typedef struct userTag 
{
  long long user_ID;
  String10  password;
  String30  address;
  long long contact;
  String20  name;
} userType;

typedef struct itemTag
{
  long long product_ID;
  String20  name;
  String15  category;
  String30  description;
  long long quantity_Available;
  double    unit_Price;
  long long seller_ID;
} itemType;

typedef struct dateTag
{
  int month;
  int day;
  int year;
} dateType;

typedef struct itemCountTag
{
  itemType item;
  int      amount;
} itemCountType;

typedef struct transactionTag
{
  dateType         date;
  itemCountType    transaction_Log[6];
  long long        buyer_ID;
  long long        seller_ID;
  float            amount;
} transactionType;


/********** GENERAL DIVISION **********/ //------------------------------------

void
prompt_Int (char prompt[],
            int  *address)
{
  char garbage;
  printf("\t%s", prompt);
  scanf("%d", address);
  scanf("%c", &garbage);
}

void
prompt_Double (char    prompt[],
               double  *address)
{
  char garbage;
  printf("\t%s", prompt);
  scanf("%lf", address);
  scanf("%c", &garbage);
}

void
prompt_Long_Long (char prompt[],
                  long long *address)
{
  char garbage;
  printf("\t%s", prompt);
  scanf("%I64d", address);
  scanf("%c", &garbage);
}

void
prompt_Char (char prompt[],
             char *address)
{
  char garbage;
  printf("\t%s", prompt);
  scanf("%c", address);
  scanf("%c", &garbage);
}

void 
clean_Input_Stream ()
{
  char garbage;
  do
  {
    scanf("%c", &garbage);
  } while (garbage != '\n');
}

void
prompt_StringN (char prompt[],
                char address[],
                int  limit)
{
  char input;
  int index;

  index = 0;
  
  printf("\t%s", prompt);
  do
    {
      scanf("%c", &input);
      address[index] = input;
      if (input != '\n')
        index++;
    } while (input != '\n' && index < limit);
  if (index >= limit && address[index] != '\n')
    clean_Input_Stream();
  address[index] = 0;
}

void
let_Read ()
{
  char garbage;

  printf("\tPress Enter to continue...");
  do
  {
    // prompt_Char("\tPress Enter to continue...", &garbage);
    scanf("%c", &garbage);
  }
  while (garbage != '\n');
}

void
new_Line()
{
  printf("\n");
}

/********** DISPLAY DIVISION **********/ //------------------------------------
void 
display_Choices (String30 choices_list[],
                int choices_list_length)
{
  int i;
  printf("\tChoices:\n");
  for (i = 0; i < choices_list_length; i++)
      printf("\t\t[%c] %s\n", 'A' + i, choices_list[i]);
}

//update formal parameters
char 
display_Menu (String30 menu_Name,
              String30 choices_List[],
              int      choices_List_Length)
{
  char choice;
  boolean error;
  boolean done;

  error = FALSE;
  done = FALSE;

  printf("\t%s Menu:\n", menu_Name);
  display_Choices(choices_List, choices_List_Length);
  
  do
  {
    if (error)
      printf("\tInvalid Input\n");

    prompt_Char("Insert choice: ", &choice);

    if (choice >= 'a' && choice <= 'z')
      choice = choice - ('A' - 'a');

    if (choice < 'A' || choice > 'A' + choices_List_Length - 1)
      error = TRUE;
    else
      done = TRUE;
  } while (!done);

  return choice;
}

void
display_Item (itemType item)
{
  printf("\tProduct ID:         %I64d\n", item.product_ID);
  printf("\tName:               %s\n", item.name);
  printf("\tCategory:           %s\n", item.category);
  printf("\tQuantity Avaliable: %I64d\n", item.quantity_Available);
  printf("\tPrice:              %lf\n", item.unit_Price); 
}

void
display_Horizontal_Border_Line (int number_Of_Columns,
                      int column_Width_Array[])
{
  int i, j;
  printf("\t");
  for (i = 0; i < number_Of_Columns; i++)
    {
      printf("+");
      for (j = 0; j < column_Width_Array[i] + 2; j++)
        printf("-");
    }
  printf("+\n");
}

/********** FILE PROCESSING DIVISION **********/ //----------------------------


void
initialize_User_Database (FILE *user_File_Pointer,
                          userType user_Database[],
                          int *user_Database_Count)
{
  int inputs;

  char white_Space;

  userType user_Instance;

  do
  {
    inputs = 0;

    inputs += fscanf (user_File_Pointer, "%I64d", &user_Instance.user_ID);

    inputs += fscanf (user_File_Pointer, "%c", &white_Space);

    inputs += fscanf (user_File_Pointer, "%[^\n]s", user_Instance.name);

    inputs += fscanf (user_File_Pointer, "%c", &white_Space);

    inputs += fscanf (user_File_Pointer, "%[^\n]s", user_Instance.address);

    inputs += fscanf (user_File_Pointer, "%I64d", &user_Instance.contact);

    if (inputs == 8)
    {
      user_Database[*user_Database_Count] = user_Instance;
      (*user_Database_Count)++;
    }
  } while (inputs == 8);
}

void
initialize_Item_Database (FILE     *item_File_Pointer,
                          itemType item_Database[],
                          int      *item_Database_Count)
{
  int inputs;

  char white_Space;

  itemType item_Instance;

  do
    {
      inputs = 0;

      inputs += fscanf (item_File_Pointer, "%I64d", &item_Instance.product_ID);

      inputs += fscanf (item_File_Pointer, "%I64d", &item_Instance.seller_ID);

      inputs += fscanf (item_File_Pointer, "%c", &white_Space);

      inputs += fscanf (item_File_Pointer, "%[^\n]s", item_Instance.name);

      inputs += fscanf (item_File_Pointer, "%c", &white_Space);

      inputs += fscanf (item_File_Pointer, "%[^\n]s", item_Instance.category);
      
      inputs += fscanf (item_File_Pointer, "%c", &white_Space);

      inputs += fscanf (item_File_Pointer, "%[^\n]s", 
                        item_Instance.description);

      inputs += fscanf (item_File_Pointer, "%I64d",         
                        &item_Instance.quantity_Available);

      inputs += fscanf (item_File_Pointer, "%lf", &item_Instance.unit_Price);
      
      if (inputs == 10)
      {
        item_Database[*item_Database_Count] = item_Instance;
        (*item_Database_Count)++;
      }
      
    } while (inputs == 10);
}

void
upload_User_Database (userType user_Database[],
                      int      user_Database_Count)
{
  FILE *user_File_Pointer = fopen("Users.txt", "r");
  int  index;

  for (index = 0; index < user_Database_Count; index++)
    {
      fprintf(user_File_Pointer, "%I64d %s\n%s\n%s\n%I64d\n\n",
              user_Database[index].user_ID,
              user_Database[index].password,
              user_Database[index].name,
              user_Database[index].address,
              user_Database[index].contact);
    }
}

void
upload_Item_Database (itemType item_Database[],
                      int item_Database_Count)
{
  FILE *item_File_Pointer = fopen ("Items.txt", "w");
  
  int index;

  for (index = 0; index < item_Database_Count; index++)
    fprintf(item_File_Pointer, "%I64d %I64d\n%s\n%s\n%s\n%I64d %lf\n\n", 
            item_Database[index].product_ID,
            item_Database[index].seller_ID,
            item_Database[index].name,
            item_Database[index].category,
            item_Database[index].description,
            item_Database[index].quantity_Available,
            item_Database[index].unit_Price);
}

/********** USER REGISTRATION DIVISION **********/ //--------------------------

boolean
check_Unique_User_ID (userType  user_Database[],
                 int       user_Database_Size,
				         long long user_ID)
{
	boolean flag;
	int index;
	
	flag = TRUE;
	index = 0;
	
	while (index < user_Database_Size && flag == FALSE)
		if (user_Database[index].user_ID == user_ID)
			flag = FALSE;
		else
			index++;
	
	return flag;
}

void
register_User (userType user_Database[],
               int      *user_Database_Count)
{
  userType  user;
  boolean   valid_Response;
  //char      white_Space;

  valid_Response = TRUE;

  do
    {
      if (!valid_Response)
        printf("\tUser ID already taken. Please find another.\n");
      
      prompt_Long_Long("ID: ", &user.user_ID);

      valid_Response = check_Unique_User_ID (user_Database, 
                                        *user_Database_Count, 
                                        user.user_ID);
    } while (!valid_Response);

  //white_Space = scanf("%c", &white_Space);

  prompt_StringN("Name: ", user.name, 20);

  prompt_StringN("Password: ", user.password, 10);

  prompt_StringN("Address: ", user.address, 30);

  prompt_Long_Long("Contact Number: ", &user.contact);

  new_Line();

  printf("\tUser Regiistration Successful!");

  user_Database[*user_Database_Count] = user;

  (*user_Database_Count)++;

  let_Read();
}

/********** USER MENU DIVISION **********/ //----------------------------------

int
search_User (userType  user_Database[],
             int       user_Database_Size,
             long long userID)
{
  int index = -1;
  int i = 0;
  while (index == -1 && i < user_Database_Size)
    {
      if(user_Database[i].user_ID == userID) index = i;
      else i++;
    }
  return index;
}

boolean
login_User (userType  user_Database[],
            int       user_Database_Size,
            long long *user_ID_pointer)
{
  long long userID;
  String10 password;
  int user_Index;
  boolean flag;

  printf("\tUSER LOGIN:\n\n");
  
  prompt_Long_Long("Insert User ID: ", &userID);
  new_Line();
  prompt_StringN("Insert Password: ", password, 10);

  user_Index = search_User(user_Database, user_Database_Size, userID);

  if (strcmp(user_Database[user_Index].password, password) != 0)
  {
    printf("\tERROR: Invalid User ID and or Password!\n");
    let_Read();
    flag = FALSE;
  }
  else
  {
    flag = TRUE;
    *user_ID_pointer = userID;
  }
  return flag;
}

/********** SELL MENU DIVISION **********/ //----------------------------------

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

/********** BUY MENU DIVISION **********/ //-----------------------------------

void
sort_Users_By_ID (userType user_Database[],
                  int      user_Database_Size)
{
  int i;
  int j;
  userType temp;
  int lowest;

  for (i = 0; i < user_Database_Size - 1; i++)
    {
      lowest = i;
      for (j = 0; j < user_Database_Size; j++)
          if (user_Database[j].user_ID > user_Database[lowest].user_ID)
              lowest = j;
      if (lowest != i)
      {
        temp = user_Database[i];
        user_Database[i] = user_Database[lowest];
        user_Database[lowest] = temp;
      }
    }
}


/********** MAIN DIVISION **********/ //---------------------------------------
int main() 
{
  userType user_Database [MAX_USERS];
  itemType item_Database [MAX_ITEMS];
  itemType user_Cart[10];

  char choice;

  int user_Database_Count;
  int item_Database_Count;
  int item_Cart_Count;

  int user_Product_Indices[20];
  int user_Product_Count;

  int item_Index;

  int i;

  boolean done;
  boolean user_Done;
  boolean sell_Done;
  boolean buy_Done;
  boolean edit_Stock_Done;
  boolean edit_Cart_Done;
  boolean check_Out_Done;
  boolean admin_Done;
  boolean valid_Input;
  boolean has_Inputted;
  
  FILE *user_File_Pointer;
  FILE *item_File_Pointer;
  FILE *cart_File_Pointer;

  long long user_ID;
  long long item_ID;
  long long addend;

  String30 user_Cart_Name;
  String15 password;

  String30 main_Menu_Choices[4] = {"Register as a User",
                                  "User Menu",
                                  "Admin Menu",
                                  "Exit"};

  String30 user_Menu_Choices[3] = {"Sell Menu", "Buy Menu", "Exit"};

  String30 sell_Menu_Choices[5] = {"Add New Item", 
                                   "Edit Stock",
                                   "Show My Products",
                                   "Show My Low Stock Products",
                                   "Exit Sell Menu"};
  
  String30 buy_Menu_Choices[8] = {"View All Products",
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

  String30 edit_Cart_Choices[4] = {"Remove All Items Of Seller",
                                   "Remove Specific Item",
                                   "Edit Quantity",
                                   "Finish Edit Cart"};

  String30 check_Out_Choices[4] = {"All",
                                   "By a Specific Seller",
                                   "Specific Item",
                                   "Exit Check Out"};

  String30 admin_Menu_Choices[6] = {"Show All Users",
                                    "Show All Sellers",
                                    "Show Total Sales in Period",
                                    "Show Sellers Sales",
                                    "Show Shopaholics",
                                    "Back to Main Menu"};

  user_File_Pointer = fopen ("Users.txt", "r");
  if (user_File_Pointer == NULL)
    user_Database_Count = 0;
  else
    initialize_User_Database(user_File_Pointer, 
                             user_Database, &user_Database_Count);
  fclose (user_File_Pointer);

  item_File_Pointer = fopen ("Items.txt", "r");
  if (item_File_Pointer == NULL)
    item_Database_Count = 0;
  else
    initialize_Item_Database(item_File_Pointer, 
                             item_Database, &item_Database_Count);
  fclose (item_File_Pointer);

  done = FALSE;

  do
    {
      
      sort_Users_By_ID(user_Database, user_Database_Count);
      choice = display_Menu ("Main", main_Menu_Choices, 4);
      switch (choice)
        {
          
          case USER_REGISTRATION: //user registration
            register_User(user_Database, &user_Database_Count);
            break;
          
          case USER_MODE: //user menu

            sprintf(user_Cart_Name, "%I64d.bag", user_ID);
            
            
            if (login_User(user_Database, user_Database_Count, &user_ID) == VALID)
            {
              user_Done = FALSE;
              
              do
              {
                
                choice = display_Menu ("User", user_Menu_Choices, 3);
                
                switch (choice)
                  {
                    
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
                              
                              case EDIT_STOCK:
                                
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
                                          item_Index = give_Item_Index_Via_ID (item_Database, 
                                                                               item_ID, 
                                                                               user_Product_Indices, 
                                                                               user_Product_Count);
                                        }
                                        
                                      } while (!valid_Input && !has_Inputted);
                                    
                                    choice = display_Menu("Edit Stock", edit_Stock_Choices, 6);
                                    
                                    switch (choice)
                                      {
                                        
                                        case REPLENISH:
                                          prompt_Long_Long("\nHow many would you like to add? ", 
                                                           &addend);
                                          if (item_Database[item_Index].quantity_Available + addend >= 0)
                                            item_Database[item_Index].quantity_Available += addend;
                                          else  
                                          {
                                            printf("\tError: Amount leads to value less than zero.\n");
                                            let_Read();
                                          }

                                          break;
                                        
                                        case CHANGE_PRICE:
                                          prompt_Double("\nWhat is the new price? ", 
                                                        &item_Database[item_Index].unit_Price);
                                          break;
                                        
                                        case CHANGE_ITEM_NAME:
                                          prompt_StringN("\nWhat is the new name? ", 
                                                         item_Database[item_Index].name, 
                                                         20);
                                          break;
                                        
                                        case CHANGE_CATEGORY:
                                          prompt_StringN("\nWhat is the new category? ", 
                                                         item_Database[item_Index].category, 
                                                         15);
                                          break;
                                        
                                        case CHANGE_DESCRIPTION:
                                          prompt_StringN("\nWhat is the new description? ", 
                                                         item_Database[item_Index].description, 
                                                         30);
                                          break;
                                        
                                        case FINISH_EDITING:
                                          edit_Stock_Done = TRUE;
                                          break;
                                        
                                      }
                                    
                                  } while (!edit_Stock_Done);
                                
                                break;
                              
                              case SHOW_MY_PRODUCTS:
                                display_Table_Ala_Show_My_Products (item_Database, 
                                                                    user_Product_Indices, 
                                                                    user_Product_Count);
                                new_Line();
                                let_Read();
                                break;
                              
                              case SHOW_MY_LOW_STOCK:
                                i = 0;
                                while ((i < user_Product_Count && choice != 'X') || choice != 'x')
                                  {
                                    if (item_Database[user_Product_Indices[i]].quantity_Available < 5)
                                    {
                                      display_Item(item_Database[user_Product_Indices[i]]);
                                      new_Line();
                                      prompt_Char("Enter 'N' to go to next item, 'B' to go back, and 'X' to exit... ", &choice);
                                      if (choice == 'N' || choice == 'n')
                                      {
                                        if (i + 1 == user_Product_Count)
                                        {
                                          printf("\tError: Index out of bounds\n");
                                          let_Read();
                                        }
                                        else i++;
                                      }
  
                                      else if (choice == 'B' || choice == 'b')
                                      {
                                        if (i - 1 < 0)
                                        {
                                          printf("\tError: Index out of bounds\n");
                                          let_Read();
                                        }
                                        else i--;
                                      }
                                    }

                                    else i++;
                                    
                                  }
                                printf("Nothing follows...\n");
                                let_Read();
                                break;
                              
                              case EXIT_SELL:
                                sell_Done = TRUE;
                                break;
                              
                            }
                          
                        } while (!sell_Done);
                      
                    break;
                    
                    case BUY_MENU:
                      
                      buy_Done = FALSE;
                      
                      do
                        {
                          
                          choice = display_Menu("Buy", buy_Menu_Choices, 7);
                          
                          switch (choice)
                            {
                              
                              case VIEW_ALL_PRODUCTS:
                                sort_Users_By_ID(user_Database, user_Database_Count);
                                break;
                              
                              case USE_SELLER_LENS:
                                // insert code here
                                break;
                              
                              case USE_CATEGORY_LENS:
                                // insert code here
                                break;
                              
                              case USE_NAME_LENS:
                                // insert code here
                                break;
                              
                              case ADD_TO_CART:
                                // insert code here
                                break;

                              case EDIT_CART:
                                
                                edit_Cart_Done = FALSE;
                                
                                do 
                                  {
                                    
                                    choice = display_Menu("Cart Edit", edit_Cart_Choices, 4);
                                    
                                    switch (choice)
                                      {
                                        
                                        case REMOVE_ITEMS_OF_SELLER:
                                          //insert code here
                                          break;
                                        
                                        case REMOVE_SPECIFIC_ITEM:
                                          //insert code here
                                          break;
                                        
                                        case EDIT_QUANTITY:
                                          //insert code here
                                          break;
                                        
                                        case FINISH_EDIT_CART:
                                          edit_Cart_Done = TRUE;
                                          break;
                                        
                                      }
                                    
                                  } while (!edit_Cart_Done);
                                
                                break;
                              
                              case CHECK_OUT:
                                
                                check_Out_Done = FALSE;
                                
                                do
                                  {
                                    
                                    choice = display_Menu("Check Out", check_Out_Choices, 4);
                                    
                                    switch (choice)
                                      {
                                        case BUY_ALL:
                                          //insert code here
                                          break;

                                        case BUY_BY_CERTAIN_SELLER:
                                          //insert code here
                                          break;

                                        case BUY_SPECIFIC_ITEM:
                                          //insert code here
                                          break;

                                        case EXIT_CHECK_OUT:
                                          check_Out_Done = TRUE;
                                          break;
                                      }
                                    
                                  } while (!check_Out_Done);
                                
                                break;
                              
                              case EXIT_BUY:
                                buy_Done = TRUE;
                                break;
                              
                            }
                          
                        } while (!buy_Done);
                      
                    break;
                    
                    case EXIT_SELL:
                      user_Done = TRUE;
                      break;
                    
                  }
                
              } while (!user_Done);
              
            }
            break;
          
          case ADMIN_MODE: //admin menu
            prompt_StringN("Insert password: ", password, 15);
            
            
            admin_Done = FALSE;
            do
              {
                system("cls");
                choice = display_Menu ("Admin", admin_Menu_Choices, 6);
                switch (choice)
                  {
                    case SHOW_ALL_USERS:
                      //insert code here
                      break;
                    case SHOW_ALL_SELLERS:
                      //insert code here
                      break;
                    case SHOW_TOTAL_SALES_IN_GIVEN_DURATION:
                      //insert code here
                      break;
                    case SHOW_SELLERS_SALES:
                      //insert code here
                      break;
                    case SHOW_SHOPAHOLICS:
                      //insert code here
                      break;
                    case EXIT_ADMIN:
                      admin_Done = TRUE;
                      break;
                  }
              } while (!admin_Done);
            break;
          
          case EXIT_PROGRAM:
            upload_Item_Database(item_Database, item_Database_Count);
            upload_User_Database(user_Database, user_Database_Count);
            done = TRUE;
            break;
        }
    } while (!done);
  
  return 0;
}
