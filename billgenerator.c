#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
	char item[20];
	float price;
	int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];	
};

//functions to generate bills
void generatebillheader(char name[50],char date[30])
{
	printf("\n\n");
	printf("\t   ADV. Restaurant");
	printf("\n\t ---------------------------------------");
	printf("\nDate:%s",date);
	printf("\nInvoice To: %s",name);
	printf("\n");
	printf("--------------------------------------------\n");
	printf("Items\t\t");
	printf("Qty\t\t");
	printf("Total\t\t");
	printf("\n------------------------------------------");
	printf("\n\n");
}

void generatebillbody(char item[30],int qty, float price)
{
	printf("%s\t\t",item);
	printf("%d\t\t",qty);
	printf("%.2f\t\t",qty*price);
	printf("\n");
}

void generatebillfooter(float total)
{
	printf("\n");
	float dis=0.1*total;
	float nettotal=total-dis;
	float cgst=0.09*nettotal,grandtotal=nettotal+2*cgst;
	printf("------------------------------------------\n");
	printf("Sub total\t\t\t%.2f",total);
	printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
	printf("\n\t\t\t\t---------");
	printf("\nNet Total\t\t\t%.2f",nettotal);
	printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
	printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
	printf("\n----------------------------------------");
	printf("\nGrand Total\t\t\t%.2f",grandtotal);
	printf("\n----------------------------------------");
}
int main()
{
	float total;
	int opt,n,i;
	struct orders ord;
	struct orders order;
	char savebill='y',contflag='y';
	char name[50];
	FILE *fp;
	//dashboard
	while(contflag=='y')
	{
		system("clear");
		float total=0;
		int invoicefound=0;
	printf("\t=============ADV. RESTAURANT=============");
	printf("\n\nPlease select your prefered operation:\t");
	printf("\n\n1.Generate Invoice");
	printf("\n2.Show all Invoices");
	printf("\n3.Search Invoice");
	printf("\n4.Exit");
	printf("\n\nYour Choice:\t");
	
	scanf("%d",&opt);
	fgetc(stdin);
	
	switch(opt)
	{
		case 1:
			system("clear");
			printf("\nPlease Enter the name of the customer:\t");
			fgets(ord.customer,50,stdin);
			ord.customer[strlen(ord.customer)-1]=0;
			//Name 
			strcpy(ord.date,__DATE__);
			printf("Please enter number of items:\t");
			scanf("%d",&n);
			ord.numofitems=n;
			
			for(i=0;i<n;i++)
			{
				fgetc(stdin);
				printf("\n\n");
				printf("Please enter the item %d:\t",i+1);
				fgets(ord.itm[i].item,20,stdin);
				ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
				printf("Please enter the quantity:\t");
				scanf("%d",&ord.itm[i].qty);
				printf("Please enter the unit price:\t");
				scanf("%f",&ord.itm[i].price);
				total += ord.itm[i].qty*ord.itm[i].price;				
			}
			
			generatebillheader(ord.customer,ord.date);
			for(i=0;i<ord.numofitems;i++)
			{
			generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);				
			}
			generatebillfooter(total);
			
			printf("\nDo you want to save the invoice:\t");
			scanf("%s",&savebill);
			
			if(savebill=='y')
			{
				fp=fopen("restaurantbill.dat","a+");
				fwrite(&ord,sizeof(struct orders),1,fp);
				if(fwrite!=0)
				printf("\nSuccessfully saved");
				else
				printf("\nEnter saving");
				fclose(fp);
			}
			break;
			
			case 2:
				system("clear");
				fp=fopen("restaurantbill.dat","r");
				printf("\n *****Your Previous Invoices*****\n");
				while(fread(&order,sizeof(struct orders),1,fp))
				{
					float tot=0;
					generatebillheader(order.customer,order.date);
					for(i=0;i<order.numofitems;i++)
					{
						generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						tot+=order.itm[i].qty*order.itm[i].price;
						
					}
					generatebillfooter(tot);					
				}
				fclose(fp);
				break;
				
				case 3:
					printf("\nEnter name of the customer:\t");
					//fgetc(stdin);
					fgets(name,50,stdin);
					name[strlen(name)-1]=0;
					system("clear");
				fp=fopen("restaurantbill.dat","r");
				printf("\t*****Invoice of %s*****\n",name);
				while(fread(&order,sizeof(struct orders),1,fp))
				{
					float tot=0;
					if(!strcmp(order.customer,name))
					{
						generatebillheader(order.customer,order.date);
					for(i=0;i<order.numofitems;i++)
					{
						generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						tot+=order.itm[i].qty*order.itm[i].price;					
					}
					generatebillfooter(tot);	
					invoicefound=1;
					}
									
				}
				if(!invoicefound)
				{
					printf("Sorry the invoice for %s doesnot exists",name);					
				}
				fclose(fp);
				break;
				
				case 4:
					printf("\n\t\t Bye Bye :)\n\n");
					exit(0);
					break;
					
				default:
					printf("Sorry Invalid Option");
					break;		
											
	}
	printf("\n\nDo you want to perform another operation?[y/n]:\t");
	scanf("%s",&contflag);
}
	printf("\n\t\t Bye Bye :)\n\n");
	printf("\n\n");
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

