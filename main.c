#include <stdio.h>
#include <stdlib.h>
#include "file.h"


int main ()
{
	while(1)
	{
		int input;
		int pass;
		printf("For User Enter 0\n");
		printf("For Admin Enter 1\n");
		printf("To exit Enter 2\n");
		scanf("%d",&input);
		if (input == 0)
		{
			user();
		}else if (input == 1)
		{
			pass = PassCheck();
			if (pass == 1)
			{
				while (1)
				{
					admin();
				}
			}else if (pass == 0)
			{
				printf("password doesn't match.");
				exit(1);
			}
			
		}else if (input == 2)
		{
			exit(1);
		}	
	}
}


