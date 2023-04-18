#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct product{
	char name[20];
	char barcode[9];
	int quantity;
	float price;
}ptr[100];

void manager();
void cashier();
void addnew();
void view();
void viewprod();
void deleteprod();
void bill();

int i,j,count=0;

int main ()
{
	system("cls");
	system("COLOR F0");
	int choice;
	printf ("You have entered Supermarket Inventory Database\n");
	printf ("\n\nTo enter the Manager mode (Press 1)\nTo enter the Cashier mode (Press 2)\nTo exit (Press 3)\n\nChoice: ");
	scanf ("%d",&choice);
	switch (choice){
		case 1:
			manager();
			main();
			break;
			
		case 2:
			cashier();
			break;
			
		case 3:
			exit (0);
			break;
			
		default:
			printf ("\n\nEnter a valid response.\n");
			main();
			break;
	}
	printf ("Press any key to continue.\n");
	getch();
	main();
}

void manager()
{
	system("cls");
	int c;
	printf ("To view all items in Inventory (Press 1)\nTo add a new item in Inventory (Press 2)\nTo delete an item from the inventory (Press 3)\n\nChoice: ");
	scanf ("%d",&c);
	switch (c){
		case 1:
			view();
			break;
			
		case 2:
			addnew();
			break;
			
		case 3:
			deleteprod();
			break;
			
		default:
			printf ("\n\nEnter a valid response.\n");
			main();
			break;
	}
	printf ("Press any key to continue.\n");
	getch();
	main();
}

void addnew()
{
	system("cls");
	int n;
	printf ("Enter how many items do you want to add in the inventory: ");
	scanf ("%d",&n);
	printf ("To add the products in the inventory. Input the following data.\n");
	for (i=0;i<n;i++)
	{
		printf ("\nProduct No. %d\n\n",i+1);
		printf ("Enter the barcode of the product: ");
		fflush(stdin);
		gets (ptr[i].barcode);
		Beep(740,300);
		printf ("Enter the name of the product: ");
		fflush(stdin);
		gets (ptr[i].name);
		printf ("Enter the quantity of the product: ");
		scanf ("%d",&ptr[i].quantity);
		printf ("Enter the price of the product: Rs ");
		scanf ("%f",&ptr[i].price);
		printf ("\n_____________\n\n");
		count++;
	}
	printf ("Press any key to continue.\n");
	getch();
	main();
}

void view()
{
	system("cls");
	printf("\t\t\t\tINVENTORY\n");
	printf("\t\t\t\t_____\n");
	for (i=0;i<count;i++)
	{
		printf ("\nProduct No. %d\n\nBarcode: %s\nName: %s\nPrice: Rs %.2f\nQuantity: %d\n\n",i+1,ptr[i].barcode,ptr[i].name,ptr[i].price,ptr[i].quantity);
	}
	printf ("Press any key to continue.\n");
	getch();
	main();
}

void deleteprod()
{
	char barcode[9];
	int flag=0;
	printf("Enter the Barcode of the product you want to delete: ");
	fflush(stdin);
	gets(barcode);
	Beep(740,300);
	for (i=0;i<=count;i++)
	{
		if (!strcmp(barcode,ptr[i].barcode))
		{
			flag=1;
			for (j=i;j<count;j++)
			{
				strcpy(ptr[j].name,ptr[j+1].name);
				strcpy(ptr[j].barcode,ptr[j+1].barcode);
                ptr[j].price=ptr[j+1].price;
                ptr[j].quantity=ptr[j+1].quantity;
			}
		}
	}
	if (flag){
		count--;
		printf ("\n\nProduct deleted succesfully!\n\n");
	}
	else{
		printf ("\n\nProduct not found!\n\n");
	}
	printf ("Press any key to continue.\n");
	getch();
	main();
}

void cashier()
{
	system("cls");
	int c;
	printf ("To view an item and it's information in stock (Press 1)\nTo create a bill (Press 2)\n\nChoice: ");
	scanf ("%d",&c);
	switch (c){
		case 1:
			viewprod();
			break;
		case 2:
			bill();
			break;
		default:
			printf ("Invalid choice.\n");
			getch();
			break;
 	}
 	printf ("\nPress any key to continue.\n");
	getch();
	main();
}

void viewprod()
{
	system("cls");
	char barcode[9];
	printf("Enter the Barcode of the product you want to view: ");
	fflush(stdin);
	gets(barcode);
	Beep(740,300);
	for (i=0;i<=count;i++)
	{
		if (!strcmp(barcode,ptr[i].barcode))
		{
			printf ("\nBarcode found!\n");
			printf ("Barcode: %s\nName: %s\nPrice: Rs %.2f\nQuantity: %d\n",ptr[i].barcode,ptr[i].name,ptr[i].price,ptr[i].quantity);
		}
	}
	printf ("\nPress any key to continue.\n");
	getch();
	main();
}

void bill()
{
	int n,flag=0;
	printf ("Enter the number of products customer wants to purchase: ");
	scanf ("%d",&n);
	char barcode[n][9];
	char name[n][20];
	int quantity[n];
	float *total;
	total=(float *)calloc(n,sizeof(float));
	
	for (i=0;i<n;i++)
	{
		total[i]=0;
		flag=0;
		printf ("\n\nEnter the Barcode of the product, customer wants to purchase: ");
		fflush(stdin);
		gets(barcode[i]);
		Beep(740,300);
		printf ("\nEnter the quantity of the product: ");
		scanf ("%d",&quantity[i]);
		for (j=0;j<count;j++)
		{
			if (!strcmp(barcode[i],ptr[j].barcode))
			{
				flag=1;
				if (quantity[i] <= ptr[j].quantity)
				{
					printf ("Barcode found!\n");	
					total[i]+=ptr[j].price*quantity[i];
					ptr[j].quantity-=quantity[i];
					strcpy(name[i],ptr[j].name);
				}
				else
				{
					printf ("Please re-enter the product with a quantity less than %d.",ptr[i].quantity);
					j--;
				}
			}
		}
		if (flag==0){
			printf ("\nProduct with the corresponding barcode not found.\nPlease re-enter the product.");
			i--;
		}
	}
	printf ("\nPress any key to view the bill.");
	getch();
	system("cls");
	float Price=0,Price1;
	printf("\t\t\t\tBILL\n");
	printf("\t\t\t\t____\n\n");
	printf ("S.No\t\tName\t\tQuantity\t\tPrice\n\n");
	for (i=0;i<n;i++){
		printf ("%d\t\t%s\t\t%d\t\t\t%.2f\n",i+1,name[i],quantity[i],total[i]);
		Price+=total[i];
	}
	Price1=Price+Price*(0.05);
	printf ("\nGross Total = Rs %.2f\nGST APPLICABLE = 5% \nTotal Price = Rs %.2f.\n",Price,Price1);
	printf ("____________\n\n");
	printf ("Thank you for shopping with us.\n");
	time_t t;
	time (&t);
	printf ("%s",ctime(&t));
	printf ("\n____________\n");
	printf ("\n\nPress any key to continue.\n");
	getch();
	main();
}















