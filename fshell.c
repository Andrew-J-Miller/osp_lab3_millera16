#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

//fshell.c
//This is the actual shell interpreter called by falsh.c
//Will have build in commands for exit, print working directory,
//change directory, setpath, and help.
//will also be able to call local programs and do simple redirection


//function for pwd
//takes a char array containing cwd
//has no return value
void pwd(char dir[1024]);

//function for help
//takes no args
//has no return value
void help();


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
	int pathnum = 1;
	int redirect = 0;
	size_t x = 0;
	pid_t cpid;


	//Gets current working directory
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fprintf(stdout, "starting falcon shell. CWD is %s\n", cwd);
	else //Fail condition for getcwd failure
		perror("current working directory error\n");
	
	//default path is just /bin
	path[0] = "/bin";
	

	//Loop that gets user strings to deconstruct them into commands
	//exits whenever the string input is exit
	while (1)
	{	
		//Display current directory before taking a commmand
		fprintf(stdout, "%s$ ", cwd);


		//Get input from stdin
		getline(&line[0], &n, stdin);

		//remove the newline char from user input
		strtok(line[0], "\n");

		//Create a temp string identical to trhe line string so it can be used with strtok without erasing the original string
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
			//Search for redirect and proper number of arguements
			if (line[0][x] == '>' )
			{
				if (count == 3)
				{
					//enable redirect and close stdout and stderr
					redirect = 1;
					freopen(("%s.out", args[2]), "a+", stdout);
					freopen(("%s.err", args[2]), "a+", stderr);
				}
				else //condition for redirect but improper arguement number
				{
					printf("Can only redirect to one file.\n");
				}	
			}
		}

	
		if (strcmp(args[0], "pwd") == 0)//run pwd
		{
			pwd(cwd);	
		}
		else if (strcmp(args[0], "help") == 0)//run help
		{
			help();
		}
		else if (strcmp(args[0], "exit") == 0)//run exit
		{
			return 0;
		}
		else if (strcmp(args[0], "cd") == 0)//run cd
		{
	
			if (count ==  1)//Default to home directory
			{
				chdir(getenv("HOME"));
				getcwd(cwd, sizeof(cwd));
			
			}
			else if (count == 2) //Go to directory that was passed in
			{
				printf("%s\n", args[1]);
				chdir(args[1]);
				getcwd(cwd, sizeof(cwd));
			}
			else //condition for > 2 cd args, errors
				printf("Error. Improper number of arguements\n");
			
		}
		else if (strcmp(args[0], "setpath") == 0)//run setpath
		{
			if (count == 1)//condition for setpath with no directory passed in
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
			//child process
			if (fork()==0)
			{

				//Searches all strings in path for program to execute
				for (i = 0; i < pathnum; i++)
				{
					//Formats string in such a way that it will run the arguement if it is in path
					execvp(("%s/%s",path[i],args[0]), args);
				
				}
				//Also tries cwd or any directory the user may have passed in
				execvp(("%s/%s",cwd, args[0]), args);
				execvp(("%s",args[0]), args);

				//If the exec call was unsucessful the child must be ended
				printf("Error. Program not found in path or local directory..\n");
				return 0;

			}
			else //The parent process must wait for the child
			{
				cpid = wait(NULL);		
			}
		}

		//end of shell loop. Resets all variables so as to smoothly loop into next command
		tmp = NULL;

		//resets all string tokens from user input
		for (i = 0; i < count; i ++)
		{
			args[i] = NULL;
		}
		count = 0;
		n = 0;
		i = 0;

		//reopens stdout if it was closed
		if (redirect == 1)
		{
			freopen("/dev/tty", "w", stdout);
			freopen("/dev/tty", "w", stderr);
		}
		redirect = 0;
	}

	return 0;
}


//prints current working directory
void pwd(char dir[1024])
{
	printf("Current directory is %s\n" , dir);
	return;
}


//prints all inbuilt commands
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




