/* Problem Statement 10: Car Sales Tracking and Reporting module 
The Car Sales Tracking and Reporting module is a key component for any system designed to 
manage sales, particularly for businesses aiming to streamline their sales operations, monitor 
performance, and make data-driven decisions for different cars. This module allows businesses 
to store sales of different brands (min 3 brands) every month. It must track the maximum and 
minimum sale of products, total cars sold in any brand, specific color or model on demand etc.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "login.c"
int login();
void addsales();
void showsales();
void maxsale();
void minsale();
void totalsales();
void totalbychoice(const char[]);
int strcompare(const char *, const char *);
char tolowerc(char ch);

#define Max 50
typedef struct cars
{ char brand[Max];
  char model[Max];
  char color[Max];
  int qty;
  char month[20];
  int year;

}carsale;
int main()
{  int ch=0,i,j;
    int ans;
    ans=login();
    if(ans==0)
    {
        printf("Invalid User\n");
        return 0;
    }
printf("WELCOME TO THE CAR SALES TRACKING SYSTEM\n");
while(ch!=8)
{  printf("\n");
printf("\nMENU IS AS FOLLOWS, PLEASE SELECT AN OPTION");
 printf("\n 1. Add new sales");
 printf("\n 2. View sales");
printf("\n  3. Find Total sales");
printf("\n  4. Find total sales by brand");

printf("\n  5. Total sales by Model");
printf("\n  6. Total sales by Color");
printf("\n  7. Max and min sale record");
printf("\n  8. Exit\n");
printf("\n  9. Total sales by Month");
printf("\n 10. Total sales by Year");

printf("\nEnter your choice:\n ");
scanf("%d",&ch);
switch(ch)
{
    case 1:
{
    addsales();
    break;
}


case 2:
{
  showsales();
  break;
}
case 3:
{
  totalsales();
  break;
}
case 4:
{
   totalbychoice("brand");

  break;

}
case 5:
{
   totalbychoice("model");
  break;
}
case 6:
{
   totalbychoice("color");
  break;
}
case 7:
{
   maxsale();
   minsale();
  break;
}
case 8:
{
  printf("Exiting the program.\n");
  break;
}

case 9:
{
    totalbychoice("month");
    break;
}
case 10:
{
    totalbychoice("year");
    break;
}

default:
{
  printf("Invalid choice. Please try again.\n");
  break;
}
}
}
return 0;
}

void savesales( const carsale *sale)
{ FILE *fp=fopen("carsdata.txt","a");
if(fp==NULL)
{ printf("error in opening file");
    return;
}
 { fprintf(fp, "%s   %s   %s   %d   %s   %d\n",
            sale->brand   ,sale->model   ,sale->color   ,sale->qty   ,sale->month   ,sale->year   );
  
  printf("Sales record saved successfully.\n");
  }
fclose(fp);
}

void addsales()
{ FILE *fp;
  carsale sale;
  printf("Enter the brand: ");
  scanf("%s",sale.brand);
  printf("Enter the model: ");
  scanf("%s",sale.model);
  printf("Enter the color : ");
  scanf("%s",sale.color);
  printf("Enter the quantity sold: ");
  scanf("%d",&sale.qty);
  printf("Enter the month of sales in words: ");
  scanf("%s",sale.month);
  printf("Enter the year of sales in integers: ");
  scanf("%d",&sale.year);
  savesales(&sale);
  printf("Sales record added successfully.\n");
}


void showsales()
    {
      FILE *fp;

      fp=fopen("carsdata.txt","r");
      if(fp==NULL)
      {printf("error in opening file");
      return;
      }
      carsale sale;
      int found=0;
    printf("         SALES RECORDS         \n");

        while (fscanf(fp, "%s %s %s %d %s %d",
                  sale.brand, sale.model, sale.color, &sale.qty, sale.month, &sale.year) == 6)
      {
        printf("Brand: %s |  Model: %s |  Color: %s |  Quantity: %d |  Month: %s |  Year: %d\n",
               sale.brand, sale.model, sale.color, sale.qty, sale.month, sale.year);
        found = 1;
    } 

    if (found==0) {
        printf("No records in file.\n");
    }

    fclose(fp);
}

    
void maxsale()
    {
        FILE *fp;
        fp=fopen("carsdata.txt","r");
        if(fp==NULL)
        return;
         carsale sale;
            carsale max;
         int found=1;

          while (fscanf(fp, "%s %s %s %d %s %d", 
                  sale.brand, sale.model, sale.color, 
                  &sale.qty, sale.month, &sale.year) == 6)
         { if(found || sale.qty>max.qty)
         {
            max=sale;
             found=0;
         }
        }
    if(found==0)
    printf("maximum sale record is %s %s %s %d %s %d ", max.brand, max.model, max.color, max.qty, max.month, max.year);
        else
        printf("No sales record found");
    
 fclose(fp);
}

    void minsale()
    {
        FILE *fp;
        fp=fopen("carsdata.txt","r");
        if(fp==NULL)
        return;
         carsale sale,min;
         int found=1;

          while (fscanf(fp, "%s %s %s %d %s %d", 
                  sale.brand, sale.model, sale.color, 
                  &sale.qty, sale.month, &sale.year) == 6)
         { if(found || sale.qty< min.qty)
         {
            min=sale;
             found=0;
         }
        }
    if(found==0)
    printf("\nminimum sale record is %s %s %s %d %s %d ",min.brand,min.model,min.color,min.qty,min.month,min.year);
        else
        printf("No sales record found");
    
    fclose(fp); }
  


void totalsales()
{ FILE *fp;
    carsale sale;

    int total =0;
     fp=fopen("carsdata.txt","r");
     if(fp==NULL)
    { printf("\nerror in opening file");
    return ;
    }
     while (fscanf(fp, "%s %s %s %d %s %d", 
                  sale.brand, sale.model, sale.color, 
                  &sale.qty, sale.month, &sale.year) == 6)
    {
        total =total+sale.qty;
    }
    fclose(fp);
    printf("\ntotal cars sold in all=%d",total);
}


void totalbychoice(const char *field)
 {
    char inputchoice[30];
    int yearinput;
    int total = 0;

    printf("DEBUG: field = '%s'\n", field);

    if (strcompare(field,"year") == 1) {
        printf("Enter year in numerals : ");
        scanf("%d", &yearinput);
    } else {
        printf("Enter %s: ", field);
scanf(" %[^\n]s", inputchoice); // Reads strings with spaces

        
    }

    FILE *fp = fopen("carsdata.txt", "r");
    if (fp==NULL) {
        printf("No sales data found.\n");
        return;
    }

    carsale sale;
     while (fscanf(fp, "%s %s %s %d %s %d", 
                  sale.brand, sale.model, sale.color, 
                  &sale.qty, sale.month, &sale.year) == 6)
     {
        if (strcompare(field, "brand") == 1 && strcompare(sale.brand, inputchoice) == 1)
            total = total+ sale.qty;
        else if (strcompare(field, "model") == 1 && strcompare(sale.model, inputchoice) == 1)
           { total = total+ sale.qty;
        }
        else if (strcompare(field, "color") == 1 && strcompare(sale.color, inputchoice) == 1)
           { total = total + sale.qty;
           }
        else if (strcompare(field, "month") == 1 && strcompare(sale.month, inputchoice) == 1)
           { total = total + sale.qty;}
           else if (strcompare(field, "year") == 1 && sale.year == yearinput)
           { total = total + sale.qty;}
    }

    fclose(fp);
    if(strcompare(field,"year") == 1)
        printf("\nTotal cars sold in year %d: %d\n", yearinput, total);
    else
        printf("\nTotal cars sold for %s %s: %d\n", field, inputchoice, total);
}


int strcompare(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (tolowerc(a[i]) != tolowerc(b[i]))
            return 0;
        i++;
    }
    return 1;
}


char tolowerc(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32; // Convert uppercase to lowercase
    else
        return ch;      // Leave other characters unchanged
}


