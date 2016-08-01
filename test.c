#include <sh21.h>

int main()
{
	char truc[1001];
	printf("on entre dans le programme\n");
	while  (read(0, truc, 1000));
	printf("on sort du programme\n");
// 		exit(0);
	return (0);
}
