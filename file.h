#ifndef FILE_H
#define FILE_H


typedef struct N 
{
	int ID;
	char *Name;
	char *Gender;
	int Age;
	struct N *next;
	char *Reservation;
}node;


int PassCheck();
void admin();
void user();
void NewPatient();
int idchecker(int id);
void EditPatient();
void ReserveSlot();
void Cancel();
static node* CreateNode(int id, int age, char *gender[6], char *name[20], char *reservation[15]); //creating the elemnts(nodes) of the linked list 
void printPatient(); // for the user 
void ViewReservations();

#endif