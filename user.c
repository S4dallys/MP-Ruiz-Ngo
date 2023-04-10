#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

// *---prototypes---*

boolean check_Unique_User_ID (userType user_Database[], int user_Database_Size, long long user_ID);
int search_User (userType user_Database[], int user_Database_Size, long long user_ID);

// *----------------*

/**
 * register_User registers a user and stores the information
 * into an array of users and updates the count.
 * @param user_Database - an array of users
 * @param user_Database_Size - pointer to the number of 
 *                             users in user_Database
 * Precondition: There is space in the array for the user
 *               instance to be recorded in.
*/
void
register_User (userType  user_Database[],
               int *     user_Database_Count)
{
    // local variable declaration
    userType  user;            // a temporary bin for user instances
    boolean   valid_Response;  // checks if a response is valid or not

    valid_Response = TRUE; // initialization of error checking variable

    // loops while a valid response is not given (i.e., a unique ID)
    do
    {
        // shows an error message for erroneous input
        if (!valid_Response)
            printf("\tUser ID already taken. Please find another.\n");
        
        // asks for an ID
        prompt_Long_Long("ID: ", &user.user_ID);

        // checks if the ID is unique or not to the array
        valid_Response = check_Unique_User_ID (user_Database, 
                                               *user_Database_Count, 
                                               user.user_ID);

    // ends once the user has given a unique ID
    } while (!valid_Response);

    // asks for a name
    prompt_StringN("Name: ", user.name, 20);

    // asks for a password
    prompt_StringN("Password: ", user.password, 10);

    // asks for an address
    prompt_StringN("Address: ", user.address, 30);

    // asks for a contact number
    prompt_Long_Long("Contact Number: ", &user.contact);

    new_Line(); // displays a new line

    // records the user into the database
    user_Database[*user_Database_Count] = user;

    // updates the count
    (*user_Database_Count)++;

    // says the registration is successful
    printf("\tUser Registration Successful!");

    // lets the user read the screen outputs
    let_Read();
}

/**
 * login_User simulates a user logging in.
 * @param user_Database - an array of users
 * @param user_Database_Size - the number of users in 
 *                             user_Database
 * @param user_ID_Pointer - pointer to which the user's ID
 *                          will be stored
 * @return TRUE for a successful login; FALSE, otherwise
*/
boolean
login_User (userType     user_Database[],
            int          user_Database_Size,
            long long *  user_ID_Pointer)
{
    // local variable declaration
    long long  userID;      // temporarily stores a user's inputted ID
    String10   password;    // temporarily stores a user' password
    int        user_Index;  // index of the user in the database
    boolean    flag;        // represents if the user successfully logged in

    // displays header
    printf("\tUSER LOGIN:\n\n");

    // asks for a user ID and stores it
    prompt_Long_Long("Insert User ID: ", &userID);
    new_Line();

    // asks for their password and stores it
    prompt_StringN("Insert Password: ", password, 10);

    // search for the user in the database
    user_Index = search_User(user_Database, user_Database_Size, userID);

    // activates if the user was not found in the database
    if (user_Index == -1)
    {
        printf("\tERROR: Invalid User ID and or Password!\n");
        let_Read();
        flag = FALSE; // marks an unsuccessful login
    }

    // activates if the user inputted the wrong password for the given user ID
    else if (strcmp(user_Database[user_Index].password, password) != 0)
    {
        printf("\tERROR: Invalid User ID and or Password!\n");
        let_Read();
        flag = FALSE; // marks an unsuccessful login
    }

    // activates if the user inputted correct credentials
    else
    {
        flag = TRUE; // marks a successful login
        *user_ID_Pointer = userID; // assigns the user ID inputted to the pointer
    }

    return flag;
}

/**
 * check_Unique_User_ID checks if a given user ID is unique 
 * in an array of users,
 * @param user_Database - an array of users
 * @param user_Database_Size - the number of users in 
 *                             user_Database
 * @param user_ID - the ID whose uniqueness needs to be
 *                  checked
 * @return TRUE if ID is unique, FALSE otherwise
*/
boolean
check_Unique_User_ID (userType   user_Database[],
                      int        user_Database_Size,
				      long long  user_ID)
{
    // local variable declaration
    boolean  flag;  // represents if an ID is unique to the array
	int      index; // index variable to be used in the coming loop
	
    // assume the ID to be unique
	flag = TRUE; 

    // initialize the indexing variable
	index = 0;
	
    // loop through the entire array except when the ID is found in the array
	while (index < user_Database_Size && flag == TRUE)
    {
        // stops the loop when it finds the ID in the array
		if (user_Database[index].user_ID == user_ID)
			flag = FALSE;

        // continues looping otherwise
		else
			index++;
    }

	return flag;
}

/**
 * search_User searches for a user in an array of users 
 * based on an ID and returns the index it was found in.
 * @param user_Database - an array of users
 * @param user_Database_Size - the number of users in 
 *                             user_Database
 * @param user_ID - the ID whose index is desired to be
 *                  known
 * @return the index in which user_ID could be found; -1, 
 *         otherwise
*/
int
search_User (userType   user_Database[],
             int        user_Database_Size,
             long long  user_ID)
{
    // local variable declaration
    int index;  // will hold the ID's index in the array (if it exists)
    int i;      // looping variable for the use in the coming loop

    index = -1; // initialize the receptacle for the ID's index
    i = 0; // initialize the indexing variable

    // loop through the entire array except when the ID is found in the array
    while (index == -1 && i < user_Database_Size)
    {
        // stops the loop when it finds the ID in the array
        if (user_Database[i].user_ID == user_ID) 
            index = i; //records the index the ID was found in

        // continues looping otherwise
        else i++;
    }

    return index;
}

/**
 * swap_Item swaps the contents of one user structure with
 * another
 * @param a - the address of a user structure
 * @param b - the address of another user structure
*/
void
swap_Users (userType * a,
            userType * b)
{
    // local variable declaration
    userType temp;

    // switches the contents
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * sort_Users_By_ID sorts the users in an array of such
 * by their IDS.
 * @param user_Database - an array of users
 * @param user_Database_Size - the number of users in 
 *                             user_Database
*/
void
sort_Users_By_ID (userType  user_Database[],
                  int       user_Database_Size)
{
    // local variable declaration
    int       lowest; // represents the index of the user with the lowest ID
    int       i;      // indexing value used for a later loop
    int       j;      // indexing value used for a later loop

    // loops through the entire array, except for the last element
    for (i = 0; i < user_Database_Size - 1; i++)
    {
        // assumes the lowest element is the ith element
        lowest = i;

        // checks succeeding elements if they are not the lowest
        for (j = i + 1; j < user_Database_Size; j++)
            // changest lowest to reflect the real lowest value, if it encounters such a value
            if (user_Database[j].user_ID < user_Database[lowest].user_ID)
                lowest = j;

        // changes swaps the users if the ith element is not the one with the lowest ID
        if (lowest != i)
            swap_Users(&user_Database[i], &user_Database[lowest]);
    }
}
