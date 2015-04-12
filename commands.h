
/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

/* Functions */
int getvaue(char*);
int getmaxproc();
int checkCmd(char *);
int f_rm(char*);

void f_ls ();
void _ls();
void f_cp(char*, char*);
void f_mv(char*, char*);
void f_rmrec(char *);
void f_exe(char *);
void handler (int);
