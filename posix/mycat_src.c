#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


void read_n_write(int fd_from, int fd_to)
{
	int length = 0;
	char buf

	while ((length = read(file_descriptor, buff, 1024)) > 0)
	{
		int written = 0;
		do
		{
			buff = buff + written;
			length -= written;
		}
		while ((written = write(1, buff, length)) > 0)

	}
}


int main(int arg_count, char* args[])
{	
	if (arg_count == 1)
	{
		char buff_x[1024];
		char * buff = buff_x;
		
		read_n_write(0, buff);

		return 0;
	}
	
	int i;
	for(i = 1; i < arg_count; ++i)
	{
		char buff_x[1024];
		char * buff = buff_x;
		int file_descriptor = open(args[i], O_RDONLY);
		
		read_n_write(file_descriptor, buff);
	}

	return 0;
}
