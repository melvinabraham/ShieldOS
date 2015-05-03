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

}adminpass,newuser;


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
		sprintf(systemvar,"mkdir admin");
		system(systemvar);
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
	
	FILE *fp; char systemvar[20];
	char *fcontent;
        long size;

    char dname[20],dpass[20],filename[20],deleteuser[20];
    int dadmin;
    int webchoice,webchoice1;	
    char websites[10][20]={"www.google.co.in","www.facebook.com","www.wikipedia.org","www.yahoo.co.in","www.flipkart.com","www.youtube.com","www.redbus.in","www.toi.in","www.reddit.com","www.amazon.in"};


//printf("\n\t\t\t\t1.Google \n\t\t\t\t2.Facebook \n\t\t\t\t3.Wikipedia \n\t\t\t\t4.Yahoo! \n\t\t\t\t5.Flipkart \n\t\t\t6.YouTube \n\t\t\t\t7.Redbus \n\t\t\t\t8.The Times Of India \n\t\t\t\t9.Reddit \n\t\t\t\t10.Amazon"};

	char *confirm;
	int i=0,choice;
	system("clear");
	if(!admin())
	{
		printf(GAP);
		printf("Sorry. You could not be authenticated!");	
	}

   
			
	else
	{	
		goback:header();
		header();

		printf(GAP);
		printf("\t\t\t\t     |||||||||||||||||||||||||||||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   1. Add User\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   2. View Users\t\t||");
		printf("\n\t\t\t\t\t\t\t     ||   3. Modify A User\t||");
		printf("\n\t\t\t\t\t\t\t     ||   4. Delete A User\t||");
		printf("\n\t\t\t\t\t\t\t     ||   5. Web Utilities\t||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t||");
		printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||");
		printf("\n\n\n\n\t\t\t\t\t\t Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
			{
				system("clear");header();
				printf(GAP);
				printf("\t\t\t\tEnter the Username : ");
				scanf("%s",newuser.username);
				sprintf(systemvar, "%s,secure.dat",newuser.username);
				if(fopen(systemvar,"r")!=NULL)
				{
					//add voice later
					system("clear");header();
					printf(GAP);
					printf("\t\t\t\tThe username already exists. Try again.");
					goto goback;
				}
				printf("\n\n\t\t\t\t\t\t\t Enter Password : ");
				scanf("%s",newuser.password);
				printf("\n\n\t\t\t\t\tDo you want to provide Administration rights to this user? (1/0) : ");
				scanf("%d",&newuser.isadmin);

				
				sprintf(systemvar,"mkdir %s",newuser.username);
				system(systemvar);
				sprintf(systemvar,"%s/secure.dat",newuser.username);
				fp=fopen(systemvar,"w+");
                fwrite(&newuser, sizeof(newuser), 1, fp);
                fcloseall();
                goto goback;
				//if(fopen(systemvar,"w+")==NULL)
            }

           case 2:
           {
           		system("clear");
                header();
                printf(GAP);
                printf("\t\t\t\t\t");
                system("ls -d */");
                system("sleep 5");
                goto goback;
           }

           case 3:
            {
                system("clear");
                header();
                printf(GAP);
                printf("\t\t\t\tEnter username:   ");
                scanf("%s",filename);
                if(!strcmp(filename,"admin"))
                {
                	//Add voice later
                	system("clear");
                	header();
                	printf(GAP);
                	printf("\t\t\t\tSorry! This user cannot be modified!");
                	goto goback;

                }
                sprintf(systemvar,"%s/secure.dat",filename);
                if (fopen(systemvar,"r")==NULL)
                {
                    system("clear");
                    header();
                    printf(GAP);
                    printf("\n\n\nNo such user exists");
                    goto goback;
                }
                fp=fopen(systemvar,"r");
                fread(&newuser,sizeof(newuser),1,fp);
                printf("\t\t\t\tEnter new username or enter 'same' to retain the original : ");
                scanf("%s",dname);
  
                if(strcmp(dname,"same"))
                 strcpy(newuser.username,dname);
                printf("\n\t\t\t\tEnter new password or enter 'same' to retain the original : ");
                scanf("%s",dpass);
                if(strcmp(dpass,"same"))
                 strcpy(newuser.password,dpass);

                printf("\n\t\t\t\tEnter new administrative right or '9' to retain the original : ");
                scanf("%d",&dadmin);
                if(dadmin!=9)
                 	newuser.isadmin=dadmin;

                sprintf(systemvar,"rm -rf %s",filename);
                system(systemvar);
                sprintf(systemvar,"mkdir %s",newuser.username);
				system(systemvar);
				sprintf(systemvar,"%s/secure.dat",newuser.username);      
                fp=fopen(systemvar,"w+");
                fwrite(&newuser,sizeof(newuser),1,fp);
                fflush(fp);
                fclose(fp); 
                goto goback;
          
                
                }

            case 4 :
            {
            	 system("clear");
                header();
                printf(GAP);
                printf("\t\t\t\tEnter username:   ");
                scanf("%s",filename);
                
                if(!strcmp(filename,"admin"))
                {
                	//Add voice later
                	system("clear");
                	header();
                	printf(GAP);
                	printf("\t\t\t\tSorry! This user cannot be deleted!");
                	system("sleep 3");
                	goto goback;

                }
                else
                {
                sprintf(systemvar,"%s/secure.dat",filename);
                if (fopen(systemvar,"r")==NULL)
                {
                    system("clear");
                    header();
                    printf(GAP);
                    printf("\n\n\nNo such user exists");
                    goto goback;
                }

                sprintf(systemvar,"rm -rf %s",filename);
                system(systemvar);
                system("clear");
                header();
                printf(GAP);
                printf("\t\t\t\tUser Successfully Deleted!");
                //Add voice later
                system("sleep 3");
                goto goback;
                break;
            }
	
	  case 5:
	    {
		header();
		printf(GAP);
		gotoweb:printf("\n\t\t\t\t Welcome to Web Utilities. You have the following choices:");
		printf("\n\t\t\t\t1.Speed Link \n\t\t\t\t2.View Internet Protocol(IP) Details \n\t\t\t\t3.Go back");
		scanf("%d",&webchoice);
		switch(webchoice)
		{


	
			case 1:
			{
				header();
				printf(GAP);
				printf("\n\t\t\t\tChoose one of the following speed links to get instant access to that website.");
				printf("\n\t\t\t\t1.Google \n\t\t\t\t2.Facebook \n\t\t\t\t3.Wikipedia \n\t\t\t\t4.Yahoo! \n\t\t\t\t5.Flipkart");
				printf("\n\t\t\t\t6.YouTube \n\t\t\t\t7.Redbus \n\t\t\t\t8.The Times Of India ");
				printf("\n\t\t\t\t9.Reddit \n\t\t\t\t10.Amazon");
				printf("\n\t\tEnter your choice");
				scanf("%d",&webchoice1);
				switch(webchoice1)
				{
					case 1: {sprintf(systemvar,"firefox %s",websites[0]);
						system(systemvar);
						break;	}
					
					case 2: {sprintf(systemvar,"firefox %s",websites[1]);
						system(systemvar);
						break;}
					
					case 3: {sprintf(systemvar,"firefox %s",websites[2]);
						system(systemvar);
						break;}
					
					case 4: {sprintf(systemvar,"firefox %s",websites[3]);
						system(systemvar);
						break;}
					
					case 5: {sprintf(systemvar,"firefox %s",websites[4]);
						system(systemvar);
						break;}
					
					case 6: {sprintf(systemvar,"firefox %s",websites[5]);
						system(systemvar);
						break;}
					
					case 7: {sprintf(systemvar,"firefox %s",websites[6]);
						system(systemvar);
						break;}
					
					case 8: {sprintf(systemvar,"firefox %s",websites[7]);
						system(systemvar);
						break;}
					
					case 9: {sprintf(systemvar,"firefox %s",websites[8]);
						system(systemvar);
						break;}
					
					case 10: {sprintf(systemvar,"firefox %s",websites[9]);
						system(systemvar);
						break;}
					default: goto gotoweb;
                		    }
				break;
				}

  			case 2:
			{
			header();
			printf(GAP);
			printf("\n");
			sprintf(systemvar,"ifconfig > IP.txt");
			system(systemvar);
			fp=fopen("IP.txt","r");
			fseek(fp, 0L, SEEK_END);
			size = ftell(fp);
			fseek(fp, 0L, SEEK_SET);
			fcontent=malloc(size);
			fread(fcontent,1,size,fp);
			printf("%s \n",fcontent);
			system("sleep 5");
			goto gotoweb;
			break;




               		}
			case 3: { goto goback;}
			default: goto goback;
		  



		}

            } 

	
        default:
        goto goback;
        }
    }
}               
                     

}
void main()
{
	//welcome();
	makeuser();
	
}
