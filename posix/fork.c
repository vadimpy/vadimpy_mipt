#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{

	pid_t pid;
	int st;
	int i;
	
	printf("\nparent: pid = %d ppid = %d\n", getpid(), getppid());

	for(i = 0; i < atoi(argv[1]); ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			sleep(2);
			printf("child: pid = %d ppid = %d\n", getpid(), getppid());
			return 0;
		}
	}

	for(i = 0; i < atoi(argv[1]); ++i)
		wait(&st);

	return 0;
}
