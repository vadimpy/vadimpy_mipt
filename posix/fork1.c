#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void doWork()
{
	sleep(1);
	printf("child: pid = %d ppid = %d\n", getpid(), getppid());
}


int main(int argc, char* argv[])
{

	pid_t pid = getpid();
	int st;
	int i;
        printf("parent: pid = %d ppid = %d\n", getpid(), getppid());
	

	pid = fork();
	if (pid == 0)
	{
		for(i = 0; i < atoi(argv[1]); ++i)
		{
			pid = fork();
			if (pid != 0)
			{
				doWork();
				wait(&st);
				return 0;
			}
		}
	}
	
	wait(&st);
	

        if (pid == 0)
		doWork();
	return 0;
}
