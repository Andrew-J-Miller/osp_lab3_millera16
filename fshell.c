#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

//fshell.c
//This is the actual shell interpreter called by falsh.c
//Will have build in commands for exit, print working directory,
//change directory, setpath, and help.
//will also be able to call local programs and do simple redirection



void help();

void exit();


int main(int argc, char *argv[])
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "%s\n" , cwd);
	else
		perror("current working directory error\n");


	return 0;
}






