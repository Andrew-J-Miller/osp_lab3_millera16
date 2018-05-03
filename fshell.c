#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

//fshell.c
//This is the actual shell interpreter called by falsh.c
//Will have build in commands for exit, print working directory,
//change directory, setpath, and help.
//will also be able to call local programs and do simple redirection





int main(int argc, char *argv[])
{
	char cwd[1024];
	char *line;
	size_t n = 0;
	size_t input;
	char str[7] = "exit\n";


	//Gets current working directory
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "starting falcon shell. CWD is %s\n", cwd);
	else //Fail condition for getcwd failure
		perror("current working directory error\n");
	

	//Loop that gets user strings to deconstruct them into commands
	//exits whenever the string input is exit
	while (strcmp(line, str) != 0)
	{	
		//Display current directory before taking a commmand
		fprintf(stdout, "%s$ ", cwd);
		//Get input from stdin
		input = getline(&line, &n, stdin);

		
	}

	return 0;
}






