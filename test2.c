#include <stddef.h>
#include <sh21.h>

int main()
{
	while(1)
	{
		int i = open("a", O_RDONLY);
		printf("%d\n", i);
		sleep(10);
	}
}
