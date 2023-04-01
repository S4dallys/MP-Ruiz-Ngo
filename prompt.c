#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

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