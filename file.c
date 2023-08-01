#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include<string.h>


node* head = NULL;
node* tail = NULL;
char *slots[5] = {"2pm->2:30pm","2:30pm->3pm","3pm->3:30pm","4pm->4:30pm","4:30pm->5pm"};
char *temp[5] = {"2pm->2:30pm","2:30pm->3pm","3pm->3:30pm","4pm->4:30pm","4:30pm->5pm"};
int IDs[5];
int PassCheck()
{
	int c = 0; // counter for trials
	int p; //password given by user
	int y = 1234; //password to compare
	do 
	{
		if(c >= 3)
		{
			return 0;
		}	
		printf("Enter the password: ");
		scanf("%d",&p);
		if (p == y)
		{
			return 1;
		}c++;	
	}while(p != y);

}

static node* CreateNode(int id, int age, char *gender[6], char *name[20], char *reservation[15])
{
	/*editor->Age = age;
	editor->Gender = gender;
	editor->Name = name;*/
	
	node *ptr = (node*)malloc(sizeof(node));
	ptr->ID = id;
	ptr->Age = age;
	ptr->Gender = *gender;
	ptr->Name = *name;
	ptr->Reservation = "not reserved";
	return ptr;
}
void user()// switch between 2 fncs 1 to view patient 2 to view the reservation of the day
{
	int p;
	int a;
	printf("\n\n");
	printf("To view patient record Enter 1\nTo view the reservation of the day Enter 2\nTo return to admin mode Enter 3\n");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			printPatient();
			break;
		case 2:
			ViewReservations();
			break;
		case 3:
			p = PassCheck();
			if (p == 1)
			{
				while (1)
				{
					admin();
				}
			}else if (p == 0)
			{
				printf("password doesn't match.");
				user();
			}
			break;	
	}
}



void admin()// switch between 4 fncs 1 to add a new patient 2 to edit existing one 3 to reserve a slot 4 to cancel a reservation
{
	int a;
	printf("\n\n");
	printf("To add a new patient Enter 1\nTo edit a record of an existing patient Enter 2\nTo reserve a slot Enter 3\nTo cancel a reservation Enter 4\nTo go user mode Enter 5\n");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			NewPatient();
			break;
		case 2:
			EditPatient();
			break;
		case 3:
			ReserveSlot();
			break;
		case 4:
			Cancel();
			break;
		case 5:
			user();
			break;	
	}
}

void NewPatient() // creating a new patient
{
	int check = 0;
	int id;
	int age;
	char *name[20];
	char *gender[6];
	char *reservation[15];
	printf("ID: 	Age: 	Gender: 	name: 	\n");
	scanf("%d",&id);
	scanf("%d",&age);
	scanf("%s",gender);
	scanf("%s",name);
	printf("\n\n");
	node* NewNode = CreateNode(id,age,gender,name,reservation);
	check = idchecker(id);
	if(check == 1)
	{
		printf("Error! Invalid ID, can't add this patient"); 
		admin();
	}else if(check == 0)
	{
		if (head == NULL)
		{
			head = NewNode;
			printf("New Patient data added succefully\n");
		}else
		{
			tail->next = NewNode;
			printf("New Patient data added succefully\n");
		}
		tail = NewNode;
		tail->next = NULL;
	}
}

void EditPatient() // editing patient record by id
{
	int check = 0;
	int id;
	printf("Enter ID for the patient you want to edit: ");
	scanf("%d",&id);
	int age;
	char name[20];
	char gender[6];
	node* editor = head;
	check = idchecker(id);
	while(editor != NULL)
	{
		if(check == 0)
		{
			printf("Invalid ID input.");
			admin();
		}
		else if (check == 1)
		{
			if (editor->ID == id)
			{
				printf("Edit age: ");
				scanf("%d",&age);
				printf("Edit gender: ");
				scanf("%s",gender);
				printf("Edit name: ");
				scanf("%s",name);
				editor->Age = age;
				editor->Gender = gender;
				editor->Name = name;
				printf("\n\nPateint record edited succefully.");
				printf("\n\nPatient record after editing: \n");
				printf("Patient ID: %d\t",editor->ID);
				printf("\nPatient Age: %d\t",editor->Age);
				printf("\nPatient Name: %s\t",editor->Name);
				printf("\nPatient Gender: %s\t",editor->Gender);
				admin();
			}
			editor = editor->next;
		}
	}
	printf("\n\n");
}


int idchecker(int id) // checking for the existence of id
{
	node* checker = head;
	if (head == NULL)
	{
		head = checker;
		return 0;
	}else
	{
		while(checker != NULL)
		{
			if(checker->ID == id)
			{
				return 1;
			}
			checker = checker->next;
		}
	}return 0;
}

void ReserveSlot()
{
	int check = 0;
	int id;
	char slot[15];
	printf("the available slots are: \n");
	for (int i = 0; i < 5; i++)
	{
		printf("slot %d: %s\n", i, slots[i]);
	}
	printf("\nEnter patient ID: ");
	scanf("%d", &id);
	node* reserver = head;
	while(reserver != NULL)
	{
		if (reserver->ID == id)
		{
			printf("Enter the slot you want to reserve: ");
			scanf("%s", slot);
			reserver->Reservation = slot;
			printf("\n\nReservation is done succefully");
			for (int i = 0; i < 5; i++)
			{
				if(strcmp(slot,slots[i]) == 0)
				{
					slots[i] = "Reserved";
					IDs[i] = reserver->ID;
				}
			}
		}
		reserver = reserver->next;
		
	}admin();
}

void Cancel() // canceling reservations 
{
	int check = 0;
	int id;
	char *slot;
	printf("\nEnter patient ID: ");
	scanf("%d", &id);
	node* canceler = head;
	while(canceler != NULL)
	{
		if (canceler->ID == id)
		{
			slot = canceler->Reservation;
			canceler->Reservation = "not reserved";
			printf("\n\ncancelation is done succefully on the slot: %s",slot);
			for (int i = 0; i < 5; i++)
			{
				if(strcmp(slot,temp[i]) == 0)
				{
					slots[i] = temp[i];
				}
			}admin();
		}
		canceler = canceler->next;
	}
}


void printPatient()
{
	int id;
	printf("Enter the patient ID: ");
	scanf("%d",&id);
	node* printer = head;
	while(printer != NULL)
	{
		if (printer->ID == id)
		{
			printf("Patient ID: %d\t",printer->ID);
			printf("\nPatient Age: %d\t",printer->Age);
			printf("\nPatient Name: %s\t",&printer->Name);
			printf("\nPatient Gender: %s\t",&printer->Gender);
			user();
		}printer = printer->next;
	}
}

void ViewReservations()
{
	node* printer = head;
	for(int i = 0; i < 5; i++)
	{
		if(slots[i]=="Reserved")
		{
			printf("slot %d: %s\t%d\n",i,temp[i],IDs[i]);
			printer = printer->next;
			if(printer == NULL)
				break;	
		}
	}user();
}




















