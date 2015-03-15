#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>



int checkCmd(char *);
void f_cp();

void getPars(char* c, char** p);


int main()
{
/*
  	DIR *directory;
  	struct dirent *de;
	sigset_t mask;
	
	sigemptyset(&mask);
	sigaddset(&mask ,SIGINT);
	sigaddset(&mask , SIGTSTP);
    sigprocmask(SIG_BLOCK , &mask , NULL);*/


	char cmd[256]="0", cmdptr, *par1, *par2, *checkme;
	char **filename;
	printf("Enter a word(quit to terminate shell): ");
	int i = 0, length, isCmd, j = 0,z=0, savetopar1, savetopar2,size=0,z1=0,j1=0,i1=0;
	char *word1,*word2,*word3;
	
		scanf("%s", cmd);
		if(strcmp(cmd, "quit") != 0)
		{
			if(strcmp(cmd, "cp") == 0)
				f_cp();
		}
			

	

	i = 0;
	while(strcmp(cmd, "quit") != 0 )
	{
		isCmd = checkCmd(cmd);
		if(isCmd==1)
		{
			//excute file
			system(strcat("./", cmd));
		}
		else if(isCmd==-1)
		{
			//send to shell
			system(cmd);
		} else
		{
			switch(isCmd)
			{
				case 1:
					//ls

					break;
				case 2:
					//mv

					break;
				case 3:
					//cp
					//cp();
					break;
				case 4:
					//rm

					break;
				case 5:
					//rmrec

					break;
				default:

					break;
			}
		}
		/* Takes next command */
		printf("Enter a word(quit to terminate shell): ");
		while(i <= length)
		{
			cmd[i] = 0;
			i++;
		}
		i = 0;
		while((cmdptr = getchar()) != '\n')
		{
			cmd[i] = cmdptr;
			i++;
		}
	}
	return 0;
}

int checkCmd(char * cmd)
{
	if((strcmp(cmd,"ls")==0))
		return 1;
	if((strcmp(cmd,"mv")==0))
		return 2;
	if((strcmp(cmd,"cp")==0))
		return 3;
	if((strcmp(cmd,"rm")==0))
		return 4;
	if((strcmp(cmd,"rmrec")==0))
		return 5;

	if((*cmd == '.') && (*(cmd+1) == '/'))
		return 0;
	return -1;

}



/*
void getPars(char* c, char** p)
{
	printf("1*");
	char* command = c;
	char** paramaters = p;
	int paramater = 0, i = 0;
	while(*command != '\n')
	{
		if(*command == ' ')
		{
			while(*command != ' ' && *command != '\n')
			{
				paramaters[paramater][i] = *command;
				command++;
				i++;
			}
		}
				command++;

	}
}*/

void f_cp()
{
	printf("\n1\n");
	// open files
	FILE * fptr1, * fptr2;
	char filename[256], copyto[256];
	scanf("%s", filename);
	scanf("%s", copyto);
	printf("\nAfter scanf\n");
	fptr1 = fopen(filename, "r");
	fptr2 = fopen(copyto, "w");

	

	// read filename data
	char filechar;

	while(!feof(fptr1))
	{	
		printf("\nw\n");
		fscanf(fptr1, "%c", &filechar);
		printf("%c\n", filechar);
		
		fprintf(fptr2, "%c", filechar);
	}
	printf("\nout of while\n");

	fclose(fptr1);
	fclose(fptr2);
	printf("\nAfter fclose\n");

	// copy data to copyto
}
