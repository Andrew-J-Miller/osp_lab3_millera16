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


void pwd(char dir[1024]);

void help();

void cd(char dir[1024], char newDir[1024]);


int main(int argc, char *argv[])
{
	char cwd[1024];
	char *line[10] = {NULL};
	size_t n = 0;
	size_t input;
	int count = 0;
	char *tmp;
	char *args[100];
	int j = 0;
	char  *env;
	char *path[100] = {NULL};
	int i = 0 ;
	int pathnum = 0;
	int redirect = 0;
	size_t x = 0;


	//Gets current working directory
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "starting falcon shell. CWD is %s\n", cwd);
	else //Fail condition for getcwd failure
		perror("current working directory error\n");

	path[0] = "/bin";
	

	//Loop that gets user strings to deconstruct them into commands
	//exits whenever the string input is exit
	while (1)
	{	
		//Display current directory before taking a commmand
		fprintf(stdout, "%s$ ", cwd);


		//Get input from stdin
		getline(&line[0], &n, stdin);

		
		tmp = strdup(line[0]);
	

		//loops through to separate int arguements
		while ((args[count] = strtok(tmp, " "))!= NULL)
		{
			tmp = NULL;
			count++;
		}
		//Now that we have our arguements, we can look for the command in args[0]
		
		for (x = 0; x < strlen(line[0]); x++)
		{
			if (line[0][x] == '>' )
			{
				if (count == 3)
				{
					redirect = 1;
					freopen(args[2], "a+", stdout);

				}
				else
				{
					printf("Can only redirect to one file.\n");
				}	
			}
		}

	
		if (strcmp(args[0], "pwd\n") == 0)
		{
			pwd(cwd);	
		}
		else if (strcmp(args[0], "help\n") == 0)
		{
			help();
		}
		else if (strcmp(args[0], "exit\n") == 0)
		{
			return 0;
		}
		else if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "cd\n") == 0)
		{
	
			if (count ==  1)//Default to home directory
			{
				chdir(getenv("HOME"));
				getcwd(cwd, sizeof(cwd));
			
			}
			else if (count == 2) //Go to directory that was passed in
			{
				while(args[1][j] != '\n')
				{
					j++;
				}
				args[1][j] = '\0';
				printf("%s\n", args[1]);
				chdir(args[1]);
				getcwd(cwd, sizeof(cwd));
			}
			else
				printf("Error. Improper number of arguements\n");
			
		}
		else if (strcmp(args[0], "setpath") == 0 || strcmp(args[0], "setpath\n") == 0)
		{
			if (count == 1)
			{
				printf("Please enter at least one directory\n");
			}
			else
			{
				pathnum = 0;
				for (i = 1; i < count; i++)
				{
					path[pathnum] = strdup(args[i]);	
					pathnum++;
					
				}
				printf("path is now ");
				for (i = 0; i < pathnum; i++)
				{
					printf("%s ", path[i]);
				}
				printf("\n");
				chdir(cwd);
			}
		}
		else //fork into child process and run from path (or specified directory)
		{
		
		}
		tmp = NULL;
		for (i = 0; i < count; i ++)
		{
			args[i] = NULL;
		}
		count = 0;
		n = 0;
		i = 0;
		if (redirect == 1)
		{
			freopen("/dev/tty", "w", stdout);
		}
		redirect = 0;
	}

	return 0;
}


void pwd(char dir[1024])
{
	printf("Current directory is %s\n" , dir);
	return;
}

void help()
{
	printf("falsh shell has the following inbuilt commands:\n");
	printf("exit: exits program\n");
	printf("pwd: print working directory");
	printf("cd: change directory\n");
	printf("setpath: sets the path, at least one arguement required\n");
	printf("help: displays all inbuilt commands\n");
	return;
}


void cd(char dir[1024], char newDir[1024])
{
	dir = strdup(newDir);
	return;
}


