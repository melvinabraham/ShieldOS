#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define GAP "\n\n\n\n\n\n\t\t\t"
#define TAB "\t\t\t\t"
#define clear "clear"

struct users
{
	char username[20];
	char password[20];
	int isadmin;

}adminpass;


void header()
{
	system("clear");
	printf("\n\t\t\t\t\t\t   ____   __    _         __     __       ____    ____\n");
	printf("\t\t\t\t\t\t  / __/  / /   (_) ___   / / ___/ /      / __ \\  / __/\n");
	printf("\t\t\t\t\t\t _\\ \\   / _ \\ / / / -_) / / / _  /      / /_/ / _\\ \\  \n");
	printf("\t\t\t\t\t\t/___/  /_//_//_/  \\__/ /_/  \\_,_/       \\____/ /___/  \n");
	printf("\t\t\t\t\t\t_____________________________________________________\n");
	printf("\t\t\t\t\t\t\t\tThe simplest OS,ever.");
	//for(i=0; i<3; i++)
	////{
		//printf("Please wait for ")
                                                      
}
//This function welcomes the user.
void welcome(char username[20])
{
	char note[100];
	sprintf(note,"espeak \"Welcome to SHIELD OS, , %s. Please Select an Option.\"",username);
	system(note);
}




//This function authenticates the admin credentials and creates an admin user if it is the first time run.
int admin(void)
{
	
	FILE *fr, *fw;
	char confirmpass[20],confirmuser[20],systemvar[20];
	int attempts=3;
	if(fopen("admin/secure.dat", "r")==NULL)
	{
		system("clear");
		printf(GAP);
		printf("\b\b\b\b\b\b\bAdmin not present. Please create a new password");
		fw=fopen("admin/secure.dat", "w+");
		printf(GAP);
		printf("\b\b\b\b\b\bEnter the new Admin password : ");
		scanf("%s",adminpass.password);
		printf(GAP);
		printf("\b\b\bConfirm the new password : ");
		scanf("%s",confirmpass);
		strcpy(adminpass.username,"admin");
		adminpass.isadmin=1;
		if(!strcmp(adminpass.password,confirmpass))
		{
			system("clear");
			printf(GAP);
			printf("Passwords Matching.");
			printf(GAP);
			fwrite(&adminpass,sizeof(adminpass),1,fw);
			rewind(fw);
			fcloseall();
			return 1;
		}			
	}
	else
	{
		system("clear");header();
		
		printf(GAP);

		printf("\t\t\tEnter your username : ");
		scanf("%s",confirmuser);
		sprintf(systemvar,"%s/secure.dat",confirmuser);

		fr=fopen(systemvar,"r");
		if(fopen(systemvar,"r")==NULL)
		{
			system("clear");header();
			printf(GAP);
			printf("\n\n\nNo such User exists! ");
			return 0;
		}
		else
		{
			fread(&adminpass,sizeof(adminpass),1,fr);
			if(!adminpass.isadmin)
			{
				system("clear");header();
				printf(GAP);
				printf("\t\t\t\t\tYou do not have Administrative privileges.");
				return 0;
			}
			tryagain:
			system("clear");header();
			printf(GAP);
			printf("\t\t\tEnter your password : ");
			scanf("%s",confirmpass);
			if(!strcmp(confirmpass,adminpass.password))
			{
				system("clear");header();
				printf(GAP);
				printf("\a\t\t\t\t    Successfully authenticated!");
				welcome(adminpass.username);
				return 1;
			}
			else
			{
					
				--attempts;
				if(attempts)
				{
					printf("\t\t\t\t\t\tSorry! Wrong password Entered! %d attempts left ",attempts);
					system("clear");
					goto tryagain;
				}

				else
				return 0;
			}
		}
	}
}	



//This function is responsible for handling new users. Requires Admin privilege.
void makeuser()
{
	
	FILE *fp;
	char *confirm;
	int i=0;
	system("clear");
	if(!admin())
	{
		printf(GAP);
		printf("Sorry. You could not be authenticated!");	
	}
	
	else
	{
		header();
		printf(GAP);
		printf("\t\t\t\t     |||||||||||||||||||||||||||||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   1. Add User\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   2. View Users\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   3. Modify A User\t||");
		printf("\n\t\t\t\t\t\t\t     ||   4. Delete A User\t||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t||");
		printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||");

	}	
}
		

void main()
{
	//welcome();
	makeuser();
	
}
