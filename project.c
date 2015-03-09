#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int checkCmd(char *);

int main()
{
	char *cmd, cmdptr;
	printf("Enter a word(quit to terminate shell): ");
	int i = 0, isCmd;

	while((cmdptr = getchar()) != '\n')
	{
		cmd[i] = cmdptr;
		i++;
	}
	
	while(strcmp(cmd, "quit") != 0 )
	{
		isCmd = checkCmd(cmd);
		//system(cmd);
		if(isCmd == 0)
		{
			//run command
		} 
		else if(isCmd==1)
		{
			//excute file
			system(strcat("./", cmd))
		}
		else if(isCmd==-1)
		{
			//send to shell
			system(cmd);
		}
		/* Takes next command */
		printf("Enter a word(quit to terminate shell): ");
		while(i >= 0)
		{
			cmd[i] = 0;
			i--;
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
	if((strcmp(cmd,"ls")==0)||(strcmp(cmd,"mv")==0)||(strcmp(cmd,"cp")==0)||(strcmp(cmd,"rm")==0)||(strcmp(cmd,"rmrec")==0))
		return 0;
	else if((*cmd == '.') && (*(cmd+1) == '/'))
			return 1;
	return -1;

}

