all: falsh fshell



falsh: falsh.c
	gcc -o falsh falsh.c


fshell: fshell.c
	gcc -o fshell fshell.c

clean:
	rm -f falsh fshell
