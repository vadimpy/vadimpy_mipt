#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char * argv[])
{

	/*struct timespec res;
	clock_gettime(CLOCK_MONOTONIC, &res);
	long t1_nsec = 0;
	long t1_sec = 0;
	t1_nsec = res.tv_nsec;
	t1_sec = res.tv_sec;
	*/
		
	if (argc > 1)
	{
		int fd[2] = {};
		pipe(fd);

		int pid = fork();
		if (pid == 0)
		{
			//перенаправляем вывод в буффер, созданный пайпом
			close(1);
			dup(fd[1]);
			close(fd[1]);
			execvp(argv[1], argv + 1);
		}
		//ждём, пока дочерний процесс умрёт
		int * p;
		wait(p);

		char output[512] = {};
		//читаем с пайпа
		read(fd[0], output, 512);
		printf("%s", output);

		int lines = 0, words = 0, bytes = 0;

		while (output[bytes] != 0)
		{
			if (output[bytes] == '\n')
				++lines;
			if (output[bytes] == ' ')
				++words;
			++bytes;
		}
		if (bytes != 0)
			++words;

		printf("lines: %d\n"
		       "words: %d\n"
		       "bytes: %d\n",
		       lines, words, bytes);
	}

	/*clock_gettime(CLOCK_MONOTONIC, &res);
	printf("%lg\n", (res.tv_sec * 1000 + res.tv_nsec / 1000000.0) - (t1_sec * 1000 + t1_nsec / 1000000.0));
	*/

	return 0;
}

