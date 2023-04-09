#include <stdio.h>
#include "global.h"

#define TEST "test.txt"

void
make_Transaction_txt ()
{
    FILE * transactionFileB;
    FILE * transactionFileT;
    int i;
    transactionType transaction;
    transactionFileB = fopen("Transactions.dat", "rb");
    transactionFileT = fopen("Transactions.txt", "wt");
    fread(&transaction, sizeof(transactionType), 1, transactionFileB);
    while (!feof(transactionFileB))
    {
        fprintf(transactionFileT, "%d-%d-%d\nItems Ordered: %d\n",
                transaction.date.year, transaction.date.month,
                transaction.date.day, transaction.items_Ordered);
        fprintf(transactionFileT, "Buyer: %I64d\nSeller %I64d\n", transaction.buyer_ID, transaction.seller_ID);
        for (i = 0; i < transaction.items_Ordered; i++)
        {
            fprintf(transactionFileT, "\nItem %d:\n", i + 1);
            fprintf(transactionFileT, "\tProduct ID:         %I64d\n", transaction.transaction_Log[i].item.product_ID);
            fprintf(transactionFileT, "\tName:               %s\n", transaction.transaction_Log[i].item.name);
            fprintf(transactionFileT, "\tCategory:           %s\n", transaction.transaction_Log[i].item.category);
            fprintf(transactionFileT, "\tQuantity Avaliable: %I64d\n", transaction.transaction_Log[i].item.quantity);
            fprintf(transactionFileT, "\tPrice:              %lf\n", transaction.transaction_Log[i].item.unit_Price); 
            fprintf(transactionFileT, "\tAmount Ordered: %I64d\n", transaction.transaction_Log[i].quantity_Desired);
        }
        fprintf(transactionFileT, "Total Amount: %f\n\n", transaction.amount);

        fread(&transaction, sizeof(transactionType), 1, transactionFileB);
    }

    fclose(transactionFileB);
    fclose(transactionFileT);
}
                  // fi = input file name (ur .bag file); fo = output file name (smth.txt or what have u)
void make_Bag_Txt (char * fi, char* fo)
{
    FILE * bagFileB;
    FILE * bagFileT;
    itemType item;
    int i;
    i = 0;
    bagFileB = fopen (fi, "rb");
    bagFileT = fopen (fo, "wt");
    fread (&item, sizeof(itemType), 1, bagFileB);
    while (!feof(bagFileB))
    {
        fprintf(bagFileT, "Item %d:\n", i + 1);
        fprintf(bagFileT, "\tProduct ID:         %I64d\n", item.product_ID);
        fprintf(bagFileT, "\tName:               %s\n", item.name);
        fprintf(bagFileT, "\tCategory:           %s\n", item.category);
        fprintf(bagFileT, "\tQuantity Avaliable: %I64d\n", item.quantity);
        fprintf(bagFileT, "\tPrice:              %lf\n\n", item.unit_Price); 
        fread (&item, sizeof(itemType), 1, bagFileB);
        printf("%d ", i++);
    }
    fclose(bagFileB);
    fclose(bagFileT);

}

int main ()
{
    make_Bag_Txt("247.bag", TEST);
}