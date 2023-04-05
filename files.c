#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

/**
 * initialize_User_Database initializes the user_Database array using the values from Users.txt
 * @param user_File_Pointer - file pointer set to Users.txt using fopen() function
 * @param user_Database - struct array containing users
 * @param user_Database_Count - number of users in user_Database
*/
void
initialize_User_Database (FILE *    user_File_Pointer,
                          userType  user_Database[],
                          int *     user_Database_Count)
{
    // local variable declaration
    userType  user_Instance;
    int       inputs;
    char      white_Space;

    // reads user data from the text file
    do
    {
        inputs = 0;

        inputs += fscanf (user_File_Pointer, "%I64d", &user_Instance.user_ID);

        inputs += fscanf (user_File_Pointer, "%c", &white_Space);

        inputs += fscanf (user_File_Pointer, "%[^\n]s", user_Instance.password);

        inputs += fscanf (user_File_Pointer, "%c", &white_Space);

        inputs += fscanf (user_File_Pointer, "%[^\n]s", user_Instance.name);

        inputs += fscanf (user_File_Pointer, "%c", &white_Space);

        inputs += fscanf (user_File_Pointer, "%[^\n]s", user_Instance.address);

        inputs += fscanf (user_File_Pointer, "%I64d", &user_Instance.contact);

        // if the read is complete, record the read data into the array
        // and increment the slated array length
        if (inputs == 8)
        {
            user_Database[*user_Database_Count] = user_Instance;
            (*user_Database_Count)++;
        }

    // keep on reading while the read data in a set is complete
    } while (inputs == 8);
}

/**
 * initialize_Item_Database initializes the item_Database array using the values from Items.txt
 * @param item_File_Pointer file pointer set to Items.txt using fopen() function
 * @param item_Database struct array containing items
 * @param item_Database_Count number of users in item_Database
*/
void
initialize_Item_Database (FILE *    item_File_Pointer,
                          itemType  item_Database[],
                          int *     item_Database_Count)
{
    // local variable declaration
    itemType  item_Instance;
    int       inputs;
    char      white_Space;

    // reads user data from the text file
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
                          &item_Instance.quantity);

        inputs += fscanf (item_File_Pointer, "%lf", &item_Instance.unit_Price);
        
        // if the read is complete, record the read data into the array
        // and increment the slated array length
        if (inputs == 10)
        {
            item_Database[*item_Database_Count] = item_Instance;
            (*item_Database_Count)++;
        }
    
    // keep on reading while the read data in a set is complete
    } while (inputs == 10);
}

/**
 * upload_User_Database uploads the content of user_Database into the Users.txt file
 * @param user_Database - array of user structures
 * @param user_Database_Count - number of users in user_Database
*/
void
upload_User_Database (userType  user_Database[],
                      int       user_Database_Count)
{
    // local variable declaration
    FILE *user_File_Pointer = fopen("Users.txt", "w");
    int index;

    // print every user in the array to the Users.txt file
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

/**
 * upload_Item_Database uploads the content of item_Database into the Items.txt file
 * @param item_Database - array of item structures
 * @param item_Database_Count - number of items in item_Database
*/
void
upload_Item_Database (itemType  item_Database[],
                      int       item_Database_Count)
{
    // local variable declaration
    FILE *item_File_Pointer = fopen ("Items.txt", "w");
    int index;

    // print every item in the array to the Items.txt file
    for (index = 0; index < item_Database_Count; index++)
    {
        fprintf(item_File_Pointer, "%I64d %I64d\n%s\n%s\n%s\n%I64d %lf\n\n", 
                item_Database[index].product_ID,
                item_Database[index].seller_ID,
                item_Database[index].name,
                item_Database[index].category,
                item_Database[index].description,
                item_Database[index].quantity,
                item_Database[index].unit_Price);
    }
}

/**
 * load_User_Cart loads the data of items from a binary file.
 * @param user_Cart_Name - the name of the binary file to be read.
 * @param user_Cart - an array where the data from the binary file
 *                    is to be stored
 * @param user_Cart_Count - a pointer to an integer variable which 
 *                          stores the number of items in user_Cart  
*/
void
load_User_Cart (char     user_Cart_Name[],
                itemType user_Cart[],
                int*     user_Cart_Count)
{
    // local variable declaration
    FILE* user_Cart_File;

    *user_Cart_Count = 0;

    // access the binary file in read mode
    user_Cart_File = fopen(user_Cart_Name, "rb");

    // activate if the file exists
    if (user_Cart_File != NULL)
    {
        // read all of the available data in it
        fread(&user_Cart[*user_Cart_Count], sizeof(itemType), 1, user_Cart_File);
        
        while (!feof(user_Cart_File))
        {
            (*user_Cart_Count)++;
            fread(&user_Cart[*user_Cart_Count], sizeof(itemType), 1, user_Cart_File);
        }
    }
}
