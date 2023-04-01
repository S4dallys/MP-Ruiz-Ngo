#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

// *---prototypes---*

boolean check_Unique_User_ID (userType user_Database[], int user_Database_Size, long long user_ID);
int search_User (userType user_Database[], int user_Database_Size, long long user_ID);

// *----------------*

void
register_User (userType  user_Database[],
               int *     user_Database_Count)
{
    userType  user;
    boolean   valid_Response;
    //char    white_Space;

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

    printf("\tUser Registration Successful!");

    user_Database[*user_Database_Count] = user;

    (*user_Database_Count)++;

    let_Read();
}

boolean
login_User (userType     user_Database[],
            int          user_Database_Size,
            long long *  user_ID_pointer)
{
    long long  userID;
    String10   password;
    int        user_Index;
    boolean    flag;

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

boolean
check_Unique_User_ID (userType   user_Database[],
                      int        user_Database_Size,
				      long long  user_ID)
{
    boolean  flag;
	int      index;
	
	flag = TRUE;
	index = 0;
	
	while (index < user_Database_Size && flag == FALSE)
    {
		if (user_Database[index].user_ID == user_ID)
			flag = FALSE;
		else
			index++;
    }

	return flag;
}

int
search_User (userType   user_Database[],
             int        user_Database_Size,
             long long  user_ID)
{
    int index = -1;
    int i = 0;

    while (index == -1 && i < user_Database_Size)
    {
        if (user_Database[i].user_ID == user_ID) index = i;
        else i++;
    }

    return index;
}

void
sort_Users_By_ID (userType  user_Database[],
                  int       user_Database_Size)
{
    userType  temp;
    int       lowest;
    int       i, j;

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