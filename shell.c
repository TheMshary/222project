#include "shell.h"

int rmrec_running = 0;	// this variable is checked when about to run rmrec

void shell(char *hostname, int pref)
{
	// gets the maximum number of processes allowed by this shell
	max_proc = getmaxproc();
	
	f_rm("pid_max");
	char c[1024];

/* 	This block of code handles 
	the blocking of signals from
	CTRL+C and CTRL+Z			*/
	DIR *directory;
  	struct dirent *de;
	sigset_t mask;
	
	sigemptyset(&mask);
	sigaddset(&mask ,SIGINT);
	sigaddset(&mask , SIGTSTP);
    sigprocmask(SIG_BLOCK , &mask , NULL);



	char cmd[256]="0", par1[256]="0", par2[256]="0";
	int i = 0, length, isCmd;
	char *s[256];
	printf("%s: ", hostname);
	scanf("%s", cmd);
	
	length = strlen(cmd);
    
	while(strcmp(cmd, "quit") != 0 )
	{
		isCmd = checkCmd(cmd);
	
		
		switch(isCmd)
		{
			case 0:
                f_exe(cmd, pref);
				break;

			case 1:
				//ls
				f_ls();
				break;

			case 2:
				//mv
				scanf("%s", par1);	// from this
				scanf("%s", par2);	// to this
				f_mv(par1, par2);
				break;

			case 3:
				//cp
				scanf("%s", par1);	// copy this
				scanf("%s", par2);	// to this
				f_cp(par1, par2);
				break;

			case 4:
				//rm
				scanf("%s", par1);	// remove this
				if(f_rm(par1) == 0)
					printf("File deleted successfully\n");
				else
					printf("Error: file was not deleted\n");
				break;

			case 5:
				//rmrec
				scanf("%s",par1);	// remove this directory
				rmrec_running = 1;
				f_rmrec(par1);
				break;

			default:
                // not a built-in command
				// or file to execute
				getl(c, 1024);
				strcat(cmd, c);
				printf("%s\n", c);
				system(cmd);
				break;
			}
		
		/* nullifies current command */
		while(i <= length)
		{
			cmd[i] = 0;
			i++;
		}
		
		i = 0;
		
		/* gets next command */
		printf("%s: ", hostname);
		scanf("%s", cmd);
	}
}
