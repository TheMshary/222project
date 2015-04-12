#include "shell.h"


int main()
{
	/* 	This block gets the hostname to
		print as the prompt for the shell */
	system("hostname > hostname.txt");
	FILE *hnfile = fopen("hostname.txt", "r");
	char hostname[256];
	fscanf(hnfile, "%s", hostname);
	fclose(hnfile);
	/* END BLOCK */

	/*	This block gets the user's
		preference */
	FILE *filepref = fopen("pref.txt", "r");
	char q;
	fscanf(filepref, "%c", &q);
	int pref = q-'0';
	fclose(filepref);
	/* END BLOCK */

	// this runs the shell
	// by calling this function
	pid_t pid = fork();
	if(pid == 0) shell(hostname, pref);
	else {
		wait(pid);
		printf("Shell terminated.\n");
	}
	return 0;
}