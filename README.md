# osp_lab3_millera16

This repositroy contains a C implementation for a shell interpreter.
The interpreter is run by calling falsh, which will call fshell to began reading user input


the -h flag can be passed into falsh to view a list of inbuilt interpreter commands.


Inbuilt interpreter commands are as follows:

exit: exits the falsh shell

pwd: Prints the current working directory

setpath: Sets the current path to any arguements passed in. This can be any number of optional arguements, so long as it is at lkeast one. The default path is simply /bin.

help: Prints all inbuilt commands.


The interpreter can also redirect with the > character. The redirects function as follows: command > filename will redirect command to <filename>.out for standard out and <filename>.err for standard error.
  
The interpreter will also fork and execute from path, local directory, or any directory passed in by the user if the command passed in is not recognized.

The repository contains a Makefile for these programs. Simply make to compile and make clean to remove.
