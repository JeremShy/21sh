#include <sh21.h>

char *get_pb(void)
{
	int tab[2];
	pipe(tab);
	char **av;
	av = malloc(2 * sizeof(char*));
	av[0] = "./pbpaste";
	av[1] = NULL;
	char **env;
	env = malloc(sizeof(char*));
	env[0] = NULL;
	int pid = fork();
	if (pid != 0)
		wait(NULL);
	else
	{
		close(1);
		dup(tab[1]);
		execve("/usr/bin/pbpaste", av, env);
	}
	close(tab[1]);
	char *str = malloc(1000);
	int n = read(tab[0], str, 999);
	str[n] = '\0';
	free(av[1]);
	free(av);
	free(env);
	return(str);
}
