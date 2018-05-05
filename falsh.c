#include<stdio.h>
#include<string.h>
#include<unistd.h>

//falsh.c
//This is the c implementation of a shell interpreter called the falcon shell
//can be optionally called with the -h tag to list options
//




int main(int argc, char *argv[])
{
	
	char *args[] = {"./fshell", NULL};


	

	//Check for too many arguements. if > 2, fails gracefully
	if (argc > 2)
	{
		printf("Error, too many arguements\n");
		return 0;
	
	}

	//condition for -h flag passed in, displays options for falsh shell
	if (argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		printf("falsh shell has the following inbuild commands:\n");
		printf("exit: exits program\n");
		printf("pwd: print working directory\n");
		printf("cd: change directory\n");
		printf("setpath: sets the path, at least one arugement required\n");
		printf("help: displays all built in commands\n");
		return 0;
	}

	//At this point, the shell itself can be called
	//It will be a separate C file, fshell.c

	execvp(args[0], args);
	




	return 0;


}
