#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>

int main()
{
	int finished = 0;
	while (!finished)
	{
		printf("promt$ ");
		char str[256];
		int i = 0;

		fgets(str, 256, stdin);
		for(;str[i] != '\n'; ++i);
		str[i] = '\0';
		i = 0;
		
		if (*str)
		{
			char * args[256];
			for(args[i] = strtok(str, " "); args[i]; ++i, args[i] = strtok(NULL, " "));

			int pid = fork();
			if (pid == 0)
				execvp(args[0], args);

			int * killed_proc;
			wait(killed_proc);
			if (**args == '0')
				finished = 1;
		}
	}
	return 0;
}

