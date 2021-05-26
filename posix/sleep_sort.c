#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int n, char * args[])
{
	int i;
	int pid;
	int status;

	for(i = 1; i < n; ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			int a = atoi(args[i]);
			usleep(10000*a);
			printf("%d ", a);
			return 0;
		}
	}
	
	for(i = 1; i < n; ++i)
		wait(&status);

	return 0;
}
