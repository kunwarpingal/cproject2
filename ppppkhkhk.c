/*cprogramming final project for first sem. Prepared by
BCE Civil C/D
   (group 8)
-Pingal Kunwar
-Prashant Chaudhary
-Prakriti Ranabhat
-Prabin Chaudhary
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Structure definitions
struct items {
    char item[20];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];//arrays
};

// Function prototypes
void generateBillHeader(char name[50], char date[30]);
void generateBillBody(char item[30], int qty, float price);
void generateBillFooter(float *total);

int main() {
    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;   //file handling
    while (contFlag == 'y') {
        system("cls");
        float total = 0;
        int invoiceFound = 0;  
        printf("\t============WRC KHAJA GHAR============");//formatted o
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);//formatted i
        fgetc(stdin);
        
        switch (opt) {
            case 1:
            	system("cls");
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer)-1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nPlease enter the number of items:\t");
                scanf("%d", &n);
                ord.numOfItems = n;

                int i;
                for (i = 0; i < n; i++) {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Please enter the item %d:\t", i + 1);
                    fgets(ord.itm[i].item, 20, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                    printf("Please enter the quantity:\t");
                    scanf("%d", &ord.itm[i].qty);
                    printf("Please enter the unit price:\t");
                    scanf("%f", &ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }

                generateBillHeader(ord.customer, ord.date);
                for (i = 0; i < ord.numOfItems; i++) {
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(&total);

                printf("\nDo you want to save the invoice [y/n]:\t");
                scanf(" %c", &saveBill);

                if (saveBill == 'y') {
                    fp = fopen("RestaurantBill.dat", "a+");
                    fwrite(&ord, sizeof(struct orders), 1, fp);
                    if (fwrite != 0)
                        printf("\nSuccessfully saved");
                    else
                        printf("\nError saving");
                    fclose(fp);
                }
                break;

            case 2:
            	system("cls");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\n  *****Your Previous Invoices*****\n");
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    generateBillHeader(order.customer, order.date);
                    int i;
                    for ( i = 0; i < order.numOfItems; i++) {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(&tot);
                }
                fclose(fp);
                break;

            case 3:
                printf("Enter the name of the customer:\t");
                fgets(name, 50, stdin);
                name[strlen(name) - 1] = 0;
                system("cls");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\t*****Invoice of %s*****", name);
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    if (strcmp(order.customer, name)==0) {
                        generateBillHeader(order.customer, order.date);
                        int i;
                        for ( i = 0; i < order.numOfItems; i++) {
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(&tot);
                        invoiceFound = 1;
                    }
                }
                if (invoiceFound==0) {
                    printf("\nSorry the invoice for %s does not exist", name);
                }
                fclose(fp);
                break;

            case 4:
                printf("\n\t\t THANK YOU!!! :)\n\n");
                exit(0);
                break;

            default:
                printf("Sorry invalid option");
                break;
        }
        
        printf("\n\nDo you want to perform another operation?[y/n]:\t");
        scanf(" %c", &contFlag);
    }

    printf("\n\t\t Bye Bye :)\n\n");

    return 0;
}

// Function definitions

// Function to generate bill header arguments pass by value
void generateBillHeader(char name[50], char date[30]) {
    printf("\n\n");
    printf("\t   WRC KHAJA GHAR");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

// Function to generate bill body for each item
void generateBillBody(char item[30], int qty, float price) {
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

// Function to generate bill footer arguments passed by reference
void generateBillFooter(float *total) {
    printf("\n");
    float dis = 0.1 * (*total);
    float netTotal = *total - dis;
    float cgst = 0.09 * netTotal;
    float sgst = cgst; // Assuming same rate for CGST and SGST
    float grandTotal = netTotal + cgst + sgst; // netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", *total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", sgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

