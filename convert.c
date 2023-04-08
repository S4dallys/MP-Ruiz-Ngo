#include <stdio.h>
#include "global.h"

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

int main ()
{
    make_Transaction_txt();
}