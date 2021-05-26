#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{

	int i;
	int n_mode;
	int help_mode;


	n_mode = 0;
	help_mode = 0;
	i = 1;
	
	if (argc != 1)
	{
		if (strcmp(argv[1], "-n") == 0)
		{
			i = 2;
			n_mode = 1;
		}

		if (strcmp(argv[1], "--help") == 0)
		{
			i = 2;
			help_mode = 1;
		}
	}
	
		if (help_mode)
			printf("help!\n");

		for(; i < argc - 1; ++i)
			printf("%s ", argv[i]);

		if (i < argc)
			printf("%s", argv[i]);
		
	
	if (!n_mode)
		printf("\n");
	

	return 0;
}
