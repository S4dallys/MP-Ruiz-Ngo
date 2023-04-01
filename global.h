// Global Definitions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS  100
#define MAX_ITEMS  MAX_USERS * 20

#define TRUE   1
#define FALSE  0
#define VALID  TRUE

#define ADMIN_PASSWORD  "H3LLo?"

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

typedef struct itemCountTag
{
    itemType item;
    int      amount;

} itemCountType;

typedef struct dateTag
{
    int month;
    int day;
    int year;

} dateType;

typedef struct transactionTag
{
    dateType         date;
    itemCountType    transaction_Log[6];
    long long        buyer_ID;
    long long        seller_ID;
    float            amount;

} transactionType;