#include "commands.h"

int ter = 0;

//	returns an indicator to which command was typed
int checkCmd(char * cmd)
{
	if((strcmp(cmd,"ls")==0)) //(0 = true , 1 = false)
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
/*----------------------------------- F_LS -----------------------------------*/

void f_ls ()
{
	DIR *directory;
	int i = 0;
    struct dirent *de;
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		if (!(directory = opendir(cwd)))
				printf("Error: cannot open directory\n");
		else
			while (0 != ( de = readdir(directory) ) )
			{
				if(i % 3 == 0)
					printf("\n");
            	if(   strcmp(de->d_name,".")==0
            		||strcmp(de->d_name,"..")==0
            		||strcmp(de->d_name,".git")==0)
            		i++;
            	else
            		{
            			printf("%-25s", de->d_name);
						i++;
					}
            }
	else
		printf("Error: cannot get current working directory\n");
	printf("\n");
}

/*----------------------------------- F_CP -----------------------------------*/

// 'cp' - copy file
// can take absolute or relative path
void f_cp(char *filename, char *copyto)
{
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
/*----------------------------------- F_MV -----------------------------------*/

// 'mv' - move
void f_mv(char *par1, char *par2)
{
	// call f_cp()
	f_cp(par1, par2);
	
	// call f_rm()
	f_rm(par1);
}
/*----------------------------------- F_RM -----------------------------------*/

// 'rm' - remove
int f_rm(char *filename)
{	
	// check status
	return remove(filename);
}
/*----------------------------------- F_RMREC -----------------------------------*/

// rmrec
void f_rmrec(char *dirname)
{
    int i = 0 , j;
    char * name;
    DIR *directory;
    struct dirent *de;
    struct stat st;
    
    chdir(dirname);
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if (!(directory = opendir(cwd)))
            printf("ERROR\n\n");
        else
        {
            for (j = 0  ; j < 2 ; j++)
                if (0 != (de = readdir(directory)))
                {
                    printf("");
                }
            
            while (0 != (de = readdir(directory)))
            {
                stat(de->d_name , &st);
                
                if(S_ISDIR(st.st_mode))
                {
                    f_rmrec(de->d_name);
                    chdir(cwd);
                }else
                {
                    remove(de->d_name);
                }
                i++;
            }
        }
    }
    else
        printf("getcwd() ERROR \n\n");
        
        rmdir(cwd);
        printf("removed :  %s\n",cwd);
        
        
        }
/*----------------------------------- F_EXE -----------------------------------*/

//execve
void f_exe(char  *name, int pref)
{
        char *arg[256] = {NULL};
        char *env [] = {NULL};
        pid_t p , pid;
        time_t t1 , t2 , t3;
        char c[1024];
        int bg = 0;

        arg[0] =(char*) name;
        getl(c , 1024);
    
        if(c[1] == '&')
            bg = 1;
        if(f_prss() <= max_proc) {
        	p = fork();
    
	        if(p == 0)
	        {
	            execve(name , (char **)arg , env);
	        }
	    
	        else
	        {

	            if(!bg)
	            {
	            signal(SIGCHLD,handler);
	            time_t t1;
	            t1 = time(NULL);
	            while(1)
	                if(!ter){
	                        if((time(NULL)-t1 == 300)){
	                        	if(pref) {
		                            pid = tcgetpgrp(getpid());
		                            printf("process %d transfered to background\n",p);
	                            } else {
	                            	wait(p);
	                            	//printf("process %d remains foreground according to your preference...\n", p);
	                            }
	                            break;
	                        }
	                }
	                else
	                    break;
	            }
	            else
	                pid = tcgetpgrp(getpid());
	        }
	    }
      	else {
      		printf("Cannot create anymore processes.\n");
      	}
            
        
}


void getl (char s [1024] , int len)
{
    int c , i;
    
    for (i = 0 ; (i<len-1) && ((c = getchar()) != EOF) && (c != '\n') ; i++)
        s[i] = c;
    if(c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
}

//---------------------------------------------------------------

// returns allowed number of processes for this shell
int getmaxproc()
{
	system("cat /proc/sys/kernel/pid_max > pid_max");
	
	int num;
	char string[256];
	FILE *fptr;
	
	if ((fptr=fopen("/proc/sys/kernel/pid_max", "r"))==NULL)
	{
	   printf("Error! opening file\n");
	   exit(1);/* Program exits if file pointer returns NULL. */
	}
	
	fscanf(fptr, "%s", string);	// read entire thing into string

	// send string to a recursive function
	num = getvalue(string);
	fclose(fptr);
	return (num/3);
}
//---------------------------------------------------------------

// This function is written very shitty-ly and hardcoded
// FIX THIS
int getvalue(char *string)
{
	int len,size ,i , j, pow=1;
	
	len = strlen(string);

	if(len > 0)
	{
		size = len-1;

		/*	pow() function in math.h isn't functioning properly.
			manually doing it for now. */
		
		for(j = 0; j < size; j++)
		{
			pow *= 10;
		}
		
		i = (string[0]-'0') * pow;
	
		return (getvalue(string+1) + i);
	}
	else
	{
		return 0;
	}
}



void handler (int signo)
{
    ter = 1;
}

int f_prss ()
{
    FILE *fd;
    char ch;
    int lines = 0;
    
    system("ps rmrec > p.txt");
    
    fd = fopen ("p.txt" , "r");
    
    while(!feof(fd))
    {
        ch = fgetc(fd);
        if(ch == '\n')
        {
            lines++;
        }
    }
    
    fclose(fd);
    
    return lines-1;
}
