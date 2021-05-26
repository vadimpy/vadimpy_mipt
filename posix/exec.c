#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[])
{
	execl("/bin/echo", "echo", "Hello", "world", NULL);
	return 0;
}
