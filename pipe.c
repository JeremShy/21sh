#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//int				get_next_line(int const fd, char **line);

//0 : read
//1 : write

void func(int sig)
{
	printf("ERROR : Sigpipe received.\n");
	exit(0);
}

int main()
{
	signal(SIGPIPE, func);
	int tab[2];
	int f1;
	int f2;
	char line[100];
	char stdline[100];
	int n;

	pipe(tab);
	close(tab[0]);
	 write(tab[1], "penis", strlen("penis"));
	printf("%d - %d\n", tab[0], tab[1]);
	f1 = fork();
	if (f1 != 0)
	{
		wait(NULL);
	}
	else
	{
		f2 = fork();
		if (f2 != 0)
		{
			n = read(0, stdline, 99);
			stdline[n] = '\0';
			write(tab[1], stdline, sizeof(stdline));
			close(tab[1]);
			exit(0);
		}
		else
		{
			n = read(tab[0], line, 99);
			line[n] = '\0';
			write(1, line, strlen(line));
			close(tab[0]);
			exit(0);
		}
	}
	printf("everything was okay.\n");
	return (0);
}
