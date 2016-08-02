#include <sh21.h>

static t_env	*parse_line(t_env *ret, char *env)
{
	char	**split;

	split = ft_strsplit(env, '=');
	if (split[1])
	{
		ret = add_elem_end(ret, split[0], split[1]);
		free(split[0]);
		free(split[1]);
		free(split);
	}
	else
	{
		ret = add_elem_end(ret, split[0], "");
		free(split[0]);
		free(split);
	}
	return (ret);
}

char	*get_path(void)
{
	char	path[255];
	int		r;
	int		fd;

	r = 0;
	if ((fd = open("/etc/paths", O_RDONLY)) == -1)
		return (NULL);
	r = read(fd, path, 255);
	close(fd);
	path[r - 1] = '\0';
	r = 0;
	while (path[r])
	{
		if (path[r] == '\n')
			path[r] = ':';
		r++;
	}
	return (ft_strdup(path));
}

static t_env	*init_list_no_env(void)
{
	t_env	*ret;
	char	*tmp;

	tmp = get_path();
	ret = add_elem_end(NULL, "PATH", tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	ret = add_elem_end(ret, "PWD", tmp);
	ret = add_elem_end(ret, "OLDPWD", tmp);
	free(tmp);
	ret = add_elem_end(ret, "HOME", "/");
	ret = add_elem_end(ret, "SHLVL", "0");
	ret = add_elem_end(ret, "TERM", "xterm-256color");
	return (ret);
}

t_env			*ft_parse_env(char **env)
{
	int		i;
	t_env	*ret;
	char	*tmp;

	ret = NULL;
	i = 0;
	if (!env[0])
		ret = init_list_no_env();
	while (env[i] != NULL)
	{
		ret = parse_line(ret, env[i]);
		i++;
	}
	if (isset_arg(ret, "SHLVL"))
	{
		tmp = find_arg(ret, "SHLVL");
		change_arg(ret, "SHLVL", ft_itoa_base(ft_atoi(tmp) + 1, 10));
		free(tmp);
	}
	return (ret);
}
