#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define GAP "\n\n\n\n\n\n\t\t\t"
#define TAB "\t\t\t\t"
#define clear "clear"


#define BLACK        0
#define BLUE         1
#define GREEN        2
#define CYAN         3
#define RED          4
#define MAGENTA      5
#define BROWN        6
#define LIGHTGRAY    7
#define DARKGRAY     8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15
#define BLINK        128

      
    int bgc=40;  
    void clreol(){
      printf("\033[K");
      }
      
    void insline(){
      printf( "\x1b[1L");
      }
  
    void delline(){
      printf( "\033[1M");
      }

    void gotoxy(int x,int y){
      printf("\033[%d;%df",y,x);
      }
      
    void clrscr(){
      printf( "\033[%dm\033[2J\033[1;1f",bgc);
      }
      
    void textbackground(int color){
      switch(color%16){
	  case BLACK:          bgc=40;break;
	  case BLUE:           bgc=44;break;
	  case GREEN:          bgc=42;break;
	  case CYAN:           bgc=46;break;
	  case RED:            bgc=41;break;
	  case MAGENTA:        bgc=45;break;
	  case BROWN:          bgc=43;break;
	  case LIGHTGRAY:      bgc=47;break;
	  case DARKGRAY:       bgc=40;break;
	  case LIGHTBLUE:      bgc=44;break;
	  case LIGHTGREEN:     bgc=42;break;
	  case LIGHTCYAN:      bgc=46;break;
	  case LIGHTRED:       bgc=41;break;
	  case LIGHTMAGENTA:   bgc=45;break;
	  case YELLOW:         bgc=43;break;
	  case WHITE:          bgc=47;break;
	}
      }

    void textcolor(short color){  
      switch(color%16){
	  case BLACK:          printf("\033[0;%d;%dm",30,bgc);break;
	  case BLUE:           printf("\033[0;%d;%dm",34,bgc);break;
	  case GREEN:          printf("\033[0;%d;%dm",32,bgc);break;
	  case CYAN:           printf("\033[0;%d;%dm",36,bgc);break;
	  case RED:            printf("\033[0;%d;%dm",31,bgc);break;
	  case MAGENTA:        printf("\033[0;%d;%dm",35,bgc);break;
	  case BROWN:          printf("\033[0;%d;%dm",33,bgc);break;
	  case LIGHTGRAY:      printf("\033[0;%d;%dm",37,bgc);break;
	  case DARKGRAY:       printf("\033[1;%d;%dm",30,bgc);break;
	  case LIGHTBLUE:      printf("\033[1;%d;%dm",34,bgc);break;
	  case LIGHTGREEN:     printf("\033[1;%d;%dm",32,bgc);break;
	  case LIGHTCYAN:      printf("\033[1;%d;%dm",36,bgc);break;
	  case LIGHTRED:       printf("\033[1;%d;%dm",31,bgc);break;
	  case LIGHTMAGENTA:   printf("\033[1;%d;%dm",35,bgc);break;
	  case YELLOW:         printf("\033[1;%d;%dm",33,bgc);break;
	  case WHITE:          printf("\033[1;%d;%dm",37,bgc);break;
	}
      }
    
    int ungetch(int ch){
      return ungetc(ch, stdin);
      }
    
    int getch_echo(int i){
      struct termios oldt, newt;
      int ch;
      tcgetattr( STDIN_FILENO, &oldt );
      newt = oldt;
      newt.c_lflag &= ~ICANON;
      if(i)
	newt.c_lflag &=  ECHO;
      else
	newt.c_lflag &= ~ECHO;
      tcsetattr( STDIN_FILENO, TCSANOW, &newt );
      ch = getchar();
      tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
      return ch;
      }
      
    int getch(){
      getch_echo(0);
      }
      
    int getche(){
      getch_echo(1);
      }
    int kbhit(){
      struct termios oldt, newt;
      int ch;
      int oldf;    
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
      fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
      ch = getchar();    
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      fcntl(STDIN_FILENO, F_SETFL, oldf);    
      if(ch != EOF){
	ungetc(ch, stdin);
	return 1;
	}    
      return 0;
      }

struct users
{
	char username[20];
	char password[20];
	int isadmin;

}adminpass,newuser,authuser;

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

void showip(char loggeduser[])
{
	FILE *fp; char systemvar[20];
	char *fcontent;
    long size;
	header();
	printf(GAP);
	printf("\n");
	sprintf(systemvar,"ifconfig > %s/IP.txt",loggeduser);
	system(systemvar);
	fp=fopen("IP.txt","r");
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	fcontent=malloc(size);
	fread(fcontent,1,size,fp);
	printf("%s \n",fcontent);
	system("sleep 5");
}


//This function welcomes the user.
void welcome(char username[20])
{
	char note[100];
	sprintf(note,"espeak \"Welcome to SHIELD OS, , %s. Please Select an Option.\"",username);
	system(note);
}

int webutilities(char loggeduser[])
{
	gotoweb:
	header();
	int choice;
	int webchoice,webchoice1;	
	FILE *fp; char systemvar[20];
	char *fcontent,url[100];
    long size;
    char websites[10][20]={"www.google.co.in","www.facebook.com","www.wikipedia.org","www.yahoo.co.in","www.flipkart.com","www.youtube.com","www.redbus.in","www.toi.in","www.reddit.com","www.amazon.in"};

				printf(GAP);
				printf("\n\t\t\t\t\t\t   Welcome to Web Utilities. You have the following choices:\n\n");
				printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
				printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
				printf("\n\t\t\t\t\t\t\t     ||   1. Speed links\t  ||");
				printf("\n\t\t\t\t\t\t\t     ||   2. View IP Details\t  ||");
				printf("\n\t\t\t\t\t\t\t     ||   3. Open URL \t\t  ||");
				printf("\n\t\t\t\t\t\t\t     ||   4. DuckDuckGo Search \t  ||");
				printf("\n\t\t\t\t\t\t\t     ||   5. Go Back\t\t  ||");
				printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
				printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
				printf("\n\n\n\n\t\t\t\t\t\t Enter your choice : ");

				scanf("%d",&webchoice);
				switch(webchoice)
				{
					case 1:
						header();
						printf(GAP);
						printf("\n\t\t\t\tChoose one of the following speed links to get instant access to that website.\n\n");
						printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
						printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
						printf("\n\t\t\t\t\t\t\t     ||  1.Google \n\t\t\t\t\t\t\t     ||  2.Facebook \n\t\t\t\t\t\t\t     ||  3.Wikipedia \n\t\t\t\t\t\t\t     ||  4.Yahoo! \n\t\t\t\t\t\t\t     ||  5.Flipkart");
						printf("\n\t\t\t\t\t\t\t     ||  6.YouTube \n\t\t\t\t\t\t\t     ||  7.Redbus \n\t\t\t\t\t\t\t     ||  8.The Times Of India ");
						printf("\n\t\t\t\t\t\t\t     ||  9.Reddit \n\t\t\t\t\t\t\t     ||  10.Amazon \n\t\t\t\t\t\t\t     ||  0.Go Back");
						printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
						printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
						printf("\n\n\n\n\t\t\t\t\t\t\t\tEnter your choice : ");
						scanf("%d",&webchoice1);
						switch(webchoice1)
							{
							case 1: 
								sprintf(systemvar,"firefox %s",websites[0]);
								system(systemvar);
								break;	
							
							case 2: 
								sprintf(systemvar,"firefox %s",websites[1]);
								system(systemvar);
								break;
							
							case 3: 
								sprintf(systemvar,"firefox %s",websites[2]);
								system(systemvar);
								break;
							
							case 4: 
								sprintf(systemvar,"firefox %s",websites[3]);
								system(systemvar);
								break;
							
							case 5: 
								sprintf(systemvar,"firefox %s",websites[4]);
								system(systemvar);
								break;
							
							case 6: 
								sprintf(systemvar,"firefox %s",websites[5]);
								system(systemvar);
								break;
							
							case 7: 
								sprintf(systemvar,"firefox %s",websites[6]);
								system(systemvar);
								break;
							
							case 8:
								sprintf(systemvar,"firefox %s",websites[7]);
								system(systemvar);
								break;
							
							case 9: 
								sprintf(systemvar,"firefox %s",websites[8]);
								system(systemvar);
								break;
							
							case 10: 
								sprintf(systemvar,"firefox %s",websites[9]);
								system(systemvar);
								break;
							
							case 11:
								goto gotoweb;
							default: 
								goto gotoweb;
	                		}
					break;

	  				case 2:
			
						showip(loggeduser);
						goto gotoweb;
					
				case 3:
					
					header();
					printf(GAP);
					printf("\t\t\t\t\tEnter the Web URL : ");
					scanf("%s",url);
					sprintf(systemvar,"firefox %s ",url);
					system(systemvar);
					goto gotoweb;

				case 4:
					
					header();
					printf(GAP);
					printf("Enter the search term : ");
					scanf("%s",url);
					sprintf(systemvar,"firefox https://duckduckgo.com/?q=%s",url);
					system(systemvar);
					goto gotoweb;

				case 5: 
					return ;
				
				default: 
					goto gotoweb;
			
				}
}

int shieldchat(char loggeduser[])
{
	char systemvar[100],ip[15];
	int choice,port;
	goback:
	header();
	printf(GAP);
	sprintf(systemvar,"notify-send \"Hello %s \" \"Welcome  to  ShieldChat  Beta. \"",loggeduser);
	system(systemvar);
	printf("\n\n\t\t\t\t\t\t\t\t Shield Chat Beta v.0.1\n");
	printf("\t\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	printf("\n\t\t\t\t\t\t\t    ||||||||||||||||||||||||||||||||");
	printf("\n\t\t\t\t\t\t\t    ||\t\t\t\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||   1. Host Connection\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||   2. Connect To Host\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||   3. View IP address\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||   4. ShieldChat Help\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||\t\t\t\t  ||");
	printf("\n\t\t\t\t\t\t\t    ||||||||||||||||||||||||||||||||");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t Enter your choice : ");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
			header();
			printf(GAP);
			printf("\n\n\t\t\t\t\t\t\t\t Shield Chat Beta Host\n");
			printf("\t\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~\n\n\n");
			printf(GAP"\n\n");
			printf(TAB);
			printf("\t\t\tEnter your secret 4 digit number : ");
			scanf("%d",&port);
			header();
			printf(GAP"\n\n");
			printf(TAB);
			printf("\t\t    Establishing connectivity using your key %d ...",port);
			sprintf(systemvar,"nc -l -p %d",port);
			printf("\n\n\n\t\t\t\tYou are now listening for any incoming connection on your IP address");
			printf("Y\n\n\n\t\t\t\tConnected!. Press Ctrl+C to exit anytime " );
			system(systemvar);
		goto goback;
		
		case 2:
			header();
			printf("\n\n\t\t\t\t\t\t\t\t Shield Chat Beta Client\n");
			printf("\t\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~\n\n\n");
			printf(GAP"\n\n");
			printf(TAB);
			printf("Enter the host IP Address : ");
			scanf("%s",ip);
			printf("\n\n\n\n");
			printf("\t\t\t\t\tEnter the secret 4 digit number of host : ");
			scanf("%d",&port);
			header();
			printf(GAP"\n\n");
			printf(TAB);
			printf("\t\t    Establishing connectivity to the host %s with key %d ...",ip,port);
			sprintf(systemvar,"nc %s %d",ip,port,);
			printf("\n\n\n\t\t\t\tYou are now looking for the host with the secret key..");
			printf("Y\n\n\n\t\t\t\tConnected!. Press Ctrl+C to exit anytime " );
			system(systemvar);
		goto goback;

		case 3:

			showip(loggeduser);
		goto goback;

		case 4 :

			header();
			printf(GAP"\n\n");
			printf("\t\t\t\t\t\t _______         _______           _______ _________\n");
			printf("\t\t\t\t\t\t   ____ \\       (  ____ \\|\\     /|(  ___  )\\__   __/\n");
			printf("\t\t\t\t\t\t| (    \\/       | (    \\/| )   ( || (   ) |   ) (  \n"); 
			printf("\t\t\t\t\t\t| (_____  _____ | |      | (___) || (___) |   | |   \n");
			printf("\t\t\t\t\t\t(_____  )(_____)| |      |  ___  ||  ___  |   | |   \n");
			printf("\t\t\t\t\t\t      ) |       | |      | (   ) || (   ) |   | |   \n");
			printf("\t\t\t\t\t\t/\\____) |       | (____/\\| )   ( || )   ( |   | |   \n");
			printf("\t\t\t\t\t\t\\_______)       (_______/|/     \\||/     \\|   )_(   \n");
					                                                    
			printf("\n\n\t\t\t\t\t   ShieldChat. An open source chat platform made for Shield OS.\n\n\n\n\n");
			system("sleep 5");
		goto goback;

		default :
		goto goback;


	}
}

void core(char loggeduser[])
{
	int choice;
	int webchoice,webchoice1;	
	FILE *fp; char systemvar[20];
	char *fcontent;
    long size;
    char websites[10][20]={"www.google.co.in","www.facebook.com","www.wikipedia.org","www.yahoo.co.in","www.flipkart.com","www.youtube.com","www.redbus.in","www.toi.in","www.reddit.com","www.amazon.in"};
	goback:
	header();
	printf(GAP);
	printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
		printf("\n\t\t\t\t\t\t\t     ||   1. Web Utilities\t  ||");
		printf("\n\t\t\t\t\t\t\t     ||   2. Shield Chat (Beta)\t  ||");
		printf("\n\t\t\t\t\t\t\t     ||   3. Shield Term (Beta)\t  ||");
		printf("\n\t\t\t\t\t\t\t     ||   4. Application Launcher ||");
		printf("\n\t\t\t\t\t\t\t     ||   5. File Manager\t  ||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t  ||");
		printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||||");
		printf("\n\n\n\n\t\t\t\t\t\t Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				gotoweb:
				webutilities(loggeduser);
			goto goback;

			case 2:
				shieldchat(loggeduser);
			goto goback;




		}
}
void authenticate()
{
	FILE *fp;
	int choice;
	char confirmuser[20],confirmpass[20],systemvar[20];
	goback:
	header();
	printf(GAP);
	printf("\t\t\t\tWelcome to Shield Authentication System.\n\n\n");
	printf("\t\t\t\t\t\t\t     ||||||||||||||||||||||||||||||||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t   ||");
		printf("\n\t\t\t\t\t\t\t     || 1. Authenticate As Admin   ||");
		printf("\n\t\t\t\t\t\t\t     || 2. Authenticate As User\t   ||");
		printf("\n\t\t\t\t\t\t\t     || 3. Continue As Guest\t   ||");
		printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t   ||");
		printf("\n\t\t\t\t\t\t\t     ||||||||||||||||||||||||||||||||");
		printf("\n\n\n\n\t\t\t\t\t\t\t Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				admin();
				break;
			case 2:
				header();
				printf(GAP);
				printf("\t\t\tEnter your username : ");
				scanf("%s",confirmuser);
				sprintf(systemvar,"%s/secure.dat",confirmuser);

				fp=fopen(systemvar,"r");
				if(fopen(systemvar,"r")==NULL)
				{
					system("clear");header();
					printf(GAP);
					printf("\n\n\n\t\t\t\t\t\t\t\tNo such User exists! ");
					while(1)
					{
						if(kbhit())
						{
							kbhit();
							break;
						}
					}
					goto goback;
				}

				fread(&authuser, sizeof(authuser),1,fp);
				header();
				printf(GAP);
				printf("\t\t\t\tEnter the password for user %s : ",confirmuser);
				scanf("%s",confirmpass);

				if(!strcmp(authuser.password,confirmpass))
				{
					core(confirmuser);
				}
			break;

			case 3:
				header();
				printf("\n\n\t\t\t");
				printf("You have chosen to use the Guest Account.Any files you store will be deleted after you logout.");
				system("rm -rf guest/");
				system("mkdir guest");
				core("guest");
			break;

		}


}

//This function authenticates the admin credentials and creates an admin user if it is the first time run.
int admin(void)
{
	void makeuser(void);
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
				makeuser();
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
	char *confirm;
	int i=0,choice;
	system("clear");
	if(!admin())
	{
		printf(GAP);
		printf("Sorry. You could not be authenticated!");
		authenticate();	
	}

   
			
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
	printf("\n\t\t\t\t\t\t\t     ||   6. Chat Client\t||");
	printf("\n\t\t\t\t\t\t\t     ||   7. Logout\t||");
	printf("\n\t\t\t\t\t\t\t     ||\t\t\t\t||");
	printf("\n\t\t\t\t\t\t\t     |||||||||||||||||||||||||||||");
	printf("\n\n\n\n\t\t\t\t\t\t Enter your choice : ");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:

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
            

        case 2:
           	system("clear");
            header();
            printf(GAP);
            printf("\t\t\t\t\t");
            system("ls -d */");
            system("sleep 5");
            goto goback;

        case 3:
            system("clear");
            header();
            printf(GAP);
            printf("\t\t\t\tEnter username:   ");
            scanf("%s",filename);
            if(!strcmp(filename,"admin")|| !strcmp(filename,"guest"))
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
          
                
            case 4 :
            
            	system("clear");
                header();
                printf(GAP);
                printf("\t\t\t\tEnter username:   ");
                scanf("%s",filename);
                
                if(!strcmp(filename,"admin")|| !strcmp(filename,"guest"))
                {
                	//Add voice later
                	system("clear");
                	header();
                	printf(GAP);
                	printf("\t\t\t\tSorry! This user cannot be deleted!");
                	system("sleep 3");
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
            	 

	
        	default:
        	goto goback;
        }
}
	              
                     


void main()
{
	authenticate();
	
}
