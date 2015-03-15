#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>


/*
	commands:
		+ ls	(check)
		+ mv 	(check)
		+ cp	(check)
		+ rm 	(check)
		+ rmrec
*/



int checkCmd(char *);
void f_cp(char*, char*);
void f_mv(char*, char*);
int f_rm(char*);
void f_rmrec(char *);
int main()
{
/* blocking
  	DIR *directory;
  	struct dirent *de;
	sigset_t mask;
	
	sigemptyset(&mask);
	sigaddset(&mask ,SIGINT);
	sigaddset(&mask , SIGTSTP);
    sigprocmask(SIG_BLOCK , &mask , NULL);*/

	char cmd[256]="0", par1[256] = "0", par2[256] = "0";

	printf("Enter a word(quit to terminate shell): ");

	int i = 0, length, isCmd;
	
	scanf("%s", cmd);
	printf("*");
	
	length = strlen(cmd);

	while(strcmp(cmd, "quit") != 0 )
	{
		isCmd = checkCmd(cmd);
		if(isCmd == -1)
			system(cmd);	// send to shell
		else
		{
			switch(isCmd)
			{
				case 0:
					// execute file
					system(cmd);
					break;
				case 1:
					//ls

					break;
				case 2:
					//mv
					scanf("%s", par1);
					scanf("%s", par2);
					f_mv(par1, par2);
					break;
				case 3:
					//cp
					scanf("%s", par1);
					scanf("%s", par2);
					f_cp(par1, par2);
					break;
				case 4:
					//rm
					scanf("%s", par1);
					if(f_rm(par1) == 0)
						printf("File is deleted successfully!!\n");
					else
						printf("Error file is not deleted!!\n");
					break;
				case 5:
					//rmrec
					scanf("%s",par1);
					f_rmrec(par1);
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
		scanf("%s", cmd);
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

void f_cp(char *filename, char *copyto)
{

printf("%s", filename);
printf("%s", copyto);


	// open files
	FILE * fptr1, * fptr2;
	fptr1 = fopen(filename, "r");
	fptr2 = fopen(copyto, "w");

	// read filename data
	char filechar;

	while(!feof(fptr1))
	{	
		fscanf(fptr1, "%c", &filechar);
		fprintf(fptr2, "%c", filechar);
	}

	fclose(fptr1);
	fclose(fptr2);
}

void f_mv(char *par1, char *par2)
{
	// call f_cp()
	f_cp(par1, par2);
	// call f_rm()
	f_rm(par1);
}

int f_rm(char *filename)
{	
	// check status
	int status = remove(filename);
	return status;
}
void f_rmrec(char *dirname)
{

	//system(strcat("cd ", dirname));
	system("ls -F > files.txt");
	// open file
	char **sword, *rd;
	int i = 0;
	FILE *fptr = fopen("files.txt", "r");
	// strtok
	while(!feof(fptr))
	{
		fscanf(fptr, "%c", rd);
	}
	sword[0] = strtok (rd,"\n");
	while (sword[i] != NULL)
	{
		printf("%s\n", sword[i]);
		sword[i+1] = strtok (NULL, "\n");
	}
	/*
	int r = remove(dirname);
	if(r !=0)
		{
			f_rmrec(dirname);
		} */
}






























