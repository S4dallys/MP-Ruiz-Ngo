#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

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