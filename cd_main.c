#include <stdlib.h>
#include <sh21.h>

void		display_not_such(char *who, char *where, t_cmd *cmd, t_data *data)
{
	putstr_builtin(cmd, who, 2);
	putstr_builtin(cmd, ": ", 2);
	putstr_builtin(cmd, where, 2);
	putstr_builtin(cmd, ": No such file or directory\n", 2);
	data->cd_ret = 1;
}



void	display_cd_permission(char *path, t_cmd *cmd, t_data *data)
{
	putstr_builtin(cmd, "cd: ", 2);
	putstr_builtin(cmd, path, 2);
	putstr_builtin(cmd, ": Permission denied\n", 2);
	data->cd_ret = 1;
}

size_t		ft_nstrlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s && s[i])
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

char	*strdup_skip(char *str)
{
	size_t	len;
	int		i;
	int		t;
	char	*dup;

	i = 0;
	t = 0;
	len = ft_strlen(str);
	if ((dup = (char *)malloc(sizeof(char) * (len + 1))))
	{
		while (str[i])
		{
			if (ft_strncmp("//", &str[i], 2))
			{
				dup[t] = str[i];
				t++;
			}
			i++;
		}
		dup[t] = '\0';
	}
	return (dup);
}

void	ft_str2del(char **array)
{
	int i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

char	*triple_join(char *s1, char *s2, char *s3)
{
	char	*final;
	int		i;

	i = 0;
	if ((final = (char *)malloc(sizeof(char) * ft_nstrlen(s1) +
								ft_nstrlen(s2) + ft_nstrlen(s3) + 1)))
	{
		while (*s1)
		{
			final[i++] = *s1;
			s1++;
		}
		while (*s2)
		{
			final[i++] = *s2;
			s2++;
		}
		while (s3 && *s3)
		{
			final[i++] = *s3;
			s3++;
		}
		final[i] = '\0';
	}
	return (final);
}


char	*join_slash(char **s)
{
	int		i;
	char	*tmp;
	char	*str;

	str = ft_strjoin("/", s[0]);
	i = 1;
	while (s[i])
	{
		tmp = str;
		str = triple_join(tmp, "/", s[i]);
		ft_strdel(&tmp);
		i++;
	}
	ft_str2del(s);
	return (str);
}

static int	ft_count_string(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			n++;
		i++;
	}
	return (++n);
}

static char	*str_range_dup(char *str, int n)
{
	char	*new_str;
	int		i;

	i = 0;
	if ((new_str = (char *)malloc(sizeof(char) * (n + 1))))
	{
		while (i < n)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

static char	*move_into_substring(char *str, char c, int match)
{
	if (match)
	{
		while (*str == c)
			str++;
	}
	else
	{
		while (*str && *str != c)
			str++;
	}
	return (str);
}

static int	get_next_sep(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char		**ft_lz_strsplit(char *str, char c)
{
	char	**split;
	int		nb_str;
	int		i;
	int		range;

	nb_str = ft_count_string(str, c);
	i = 0;
	if ((split = (char **)malloc(sizeof(char *) * (nb_str + 1))))
	{
		while (i < nb_str)
		{
			if (i != 0)
				str = move_into_substring(str, c, 1);
			range = get_next_sep(str, c);
			split[i] = str_range_dup(str, range);
			str = move_into_substring(str, c, 0);
			i++;
		}
		split[nb_str] = NULL;
	}
	return (split);
}

void	display_cd_invalid_option(char *opt, t_cmd *cmd, t_data *data)
{
	putstr_builtin(cmd, "cd: ", 2);
	putstr_builtin(cmd, opt, 2);
	putstr_builtin(cmd, ": invalid option\n", 2);
	putstr_builtin(cmd, "cd: usage: cd [-L OR -P] [dir]\n", 2);
	data->cd_ret = 1;
}

int		is_physical(char *str)
{
	if (ft_strcmp("-P", str) == 0)
		return (1);
	return (0);
}

int		is_logical(char *str)
{
	if (ft_strcmp("-L", str) == 0)
		return (1);
	return (0);
}

int		is_minus(char *str)
{
	if (ft_strcmp("-", str) == 0)
		return (1);
	return (0);
}

int		operate_legal_opts(char **str, t_cmd *cmd, t_data *data)
{
	size_t	i;
	int		o;

	i = 1;
	o = 0;
	while (str[i])
	{
		if (str[i][0] == '-' && !is_minus(str[i]))
		{
			if ((is_physical(str[i]) || is_logical(str[i])) && o == 0)
				o++;
			else if (o && (is_physical(str[i]) || is_logical(str[i])))
				return (0);
			else
			{
				display_cd_invalid_option(str[i], cmd, data);
				return (-1);
			}
		}
		else
			return (1);
		i++;
	}
	return (1);
}

int		is_legal_options(char **str, t_cmd *cmd, t_data *data)
{
	int		ret;

	ret = operate_legal_opts(str, cmd, data);
	if (ret == 0)
	{
		putstr_builtin(cmd, "cd: usage: cd [-L OR -P] [dir]\n", 2);
		data->cd_ret = 1;
		return (0);
	}
	if (ret == -1)
	{
		data->cd_ret = 1;
		return (0);
	}
	return (1);
}


size_t	ft_str2len(char **array)
{
	int i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			i++;
		}
	}
	return (i);
}

int		is_logical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (1);
	if (len == 2)
		return (0);
	if (ft_strcmp("-L", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}


char	*concat_chdir(char *path,  t_env **env, t_data *data)
{
	char	*dirs;
	char	*full;
	char	**dir_l;
	int		i;

	dirs = find_var_env(data, "CHDIR", *env);
	if (!ft_strequ(dirs, ""))
	{
		dir_l = ft_lz_strsplit(dirs, ':');
		i = 0;
		while (dir_l[i])
		{
			full = triple_join(dir_l[i], "/", path);
			if (access(full, F_OK) == 0)
			{
				ft_str2del(dir_l);
				return (full);
			}
			ft_strdel(&full);
			i++;
		}
		ft_str2del(dir_l);
	}
	else
		free(dirs);
	return (NULL);
}

char	*create_chdir_path(char *path, t_env **env, t_data *data)
{
	char	*good;

	if (access(path, F_OK) == 0)
		return (ft_strdup(path));
	if ((good = concat_chdir(path, env, data)))
		return (good);
	return (ft_strdup(path));
}


void	ft_remove_endchar(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == c)
		str[len - 1] = '\0';
}


char	*remove_duplicate_slash(char *path)
{
	char	*ready;

	if (ft_strstr(path, "//"))
	{
		ready = strdup_skip(path);
		return (ready);
	}
	else
	{
		return (ft_strdup(path));
	}
}

void	native_full(char *path, t_env **env, char *old_pwd)
{
	if (chdir(path) == 0)
	{
		change_arg(*env, "OLDPWD", old_pwd);
		change_arg(*env, "PWD", path);
	}
}

void	made_full(char *path,  t_env **env, char *full, char *old_pwd)
{
	if (chdir(path) == 0)
	{
		change_arg(*env, "OLDPWD", old_pwd);
		change_arg(*env, "PWD", full);
	}
	ft_strdel(&full);
}

void	just_path(char *path, t_env **env, char *old_pwd)
{
	char	*wd;

	if (chdir(path) == 0)
	{
		change_arg(*env, "OLDPWD", old_pwd);
		wd = triple_join(old_pwd, "/", path);
		change_arg(*env, "PWD", wd);
		free(wd);
	}
}


void		ft_str2defrag(char **array, size_t origin_size)
{
	size_t	i;
	size_t	j;
	size_t	b;

	i = 0;
	if (origin_size != ft_str2len(array))
	{
		while (i < origin_size + 1)
		{
			if (array[i] == NULL)
			{
				b = i;
				j = i + 1;
				while (j < origin_size + 1)
				{
					array[i] = array[j];
					i++;
					j++;
				}
				i = b;
			}
			i++;
		}
	}
}

char	**defrag(char **s, size_t len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp("..", s[i]) == 0 && i > 0)
		{
			ft_strdel(&s[i - 1]);
			ft_str2defrag(s, len);
			ft_strdel(&s[i - 1]);
			ft_str2defrag(s, len);
			i = 0;
		}
		else if (ft_strcmp(".", s[i]) == 0)
		{
			free(s[i]);
			s[i] = NULL;
			ft_str2defrag(s, len);
			i = 0;
		}
		else
			i++;
	}
	return (s);
}

char	*troncate_dots(char *path)
{
	char	**s;
	char	*str;

	if (path[0] == '/')
	{
		s = ft_lz_strsplit(&path[1], '/');
	}
	else
	{
		s = ft_lz_strsplit(&path[0], '/');
	}
	s = defrag(s, ft_str2len(s));
	str = join_slash(s);
	ft_strdel(&path);
	return (str);
}

void	cd_symblink(char *path,  t_env **env, t_data *data)
{
	char	*old_pwd;
	char	*full;

	old_pwd = find_var_env(data, "PWD", *env);
	full = NULL;
	if (ft_strstr(path, "..") || ft_strstr(path, "./"))
	{
		full = triple_join(old_pwd, "/", path);
		full = troncate_dots(full);
	}
	if (path[0] == '/' && !full)
		native_full(path, env, old_pwd);
	else if (full)
		made_full(path, env, full, old_pwd);
	else
		just_path(path, env, old_pwd);
	free(old_pwd);
}

int		is_goto_home(char **command)
{
	size_t	len;

	len = ft_str2len(command);
	if (len == 1 || ft_strcmp(command[1], "~") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-P") == 0)
	{
		return (1);
	}
	else if (len == 2 && ft_strcmp(command[1], "-L") == 0)
	{
		return (1);
	}
	return (0);
}


void		cd_physical(char *path, t_env **env, t_data *data, t_cmd *cmd)
{
	int		ret;
	char	*buf_wd;
	char	*old_pwd;

	if ((buf_wd = (char *)malloc(sizeof(char) * 1024)))
	{
		old_pwd = find_var_env(data, "PWD", *env);
		if ((ret = chdir(path)) == 0)
		{
			change_arg(*env, "OLDPWD", old_pwd);
			change_arg(*env, "PWD", getcwd(buf_wd, 1024));
		}
		else
			display_cd_permission(path, cmd, data);
		free(buf_wd);
		free(old_pwd);
	}
}

void		change_dir(char *path, t_env **env, t_data *data, int p, t_cmd *cmd)
{
	struct	stat	*st;
	char		*ready;

	if (path && (st = (struct stat *)malloc(sizeof(struct stat))))
	{
		path = create_chdir_path(path, env, data);
		if (lstat(path, st) == 0)
		{
			if (p == 0 && (S_ISLNK(st->st_mode)))
			{
				if (ft_strlen(path) > 2)
					ft_remove_endchar(path, '/');
				ready = remove_duplicate_slash(path);
				cd_symblink(ready, env, data);
				ft_strdel(&ready);
			}
			else
				cd_physical(path, env, data, cmd);
		}
		else
			display_not_such("cd", path, cmd, data);
		free(st);
		free(path);
	}
}

void		go_to_home_directory(t_env **env, t_data *data, t_cmd *cmd)
{
	char	*home;

	home = (char *)find_var_env(data, "HOME", *env);
	if (!ft_strequ(home, ""))
	{
		change_dir(home, env, data, 0, cmd);
	}
	else
	{
		data->cd_ret = 1;
		ft_putendl_fd("cd: HOME not set", 2);
	}
	free(home);
}

char *get_cwd(size_t size, t_data *data)
{
	char *cwd;
	char *buf_cwd;

	if (size > BUF_CWD)
	{
		if (size < BUF_CWD_MAX)
			size = size * 2;
		else
		{
			data->cd_ret = 1;
			write(2, BUF_CWD_ERR, ft_strlen(BUF_CWD_ERR));
		}
	}
	if ((buf_cwd = (char *)malloc(sizeof(char) * size)))
	{
		if ((cwd = getcwd(buf_cwd, size)))
			return (cwd);
		else
		{
			free(buf_cwd);
			return (get_cwd(++size, data));
		}
	}
	else
	{
		write(2, BUF_CWD_ERR, ft_strlen(BUF_CWD_ERR));
		data->cd_ret = 1;
		return (NULL);
	}
}


void	go_to_old_pwd(t_data *data, t_env **env, int p, t_cmd *cmd)
{
	char	*old_pwd;
	char	*tmp;

	tmp = find_var_env(data, "OLDPWD", *env);
	if (!ft_strequ(tmp, ""))
	{
		old_pwd = find_var_env(data, "OLDPWD", *env);
		if (!ft_strequ(old_pwd, ""))
		{
			change_dir(old_pwd, env, data, p, cmd);
		}
		free(old_pwd);
	}
	else
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		data->cd_ret = 1;
	}
	free(tmp);
}

int		is_physical_goto_oldpwd(char **str)
{
	size_t	len;

	len = ft_str2len(str);
	if (len == 1)
		return (0);
	if (ft_strcmp("-", str[1]) == 0)
		return (0);
	if (len == 2)
		return (0);
	if (ft_strcmp("-P", str[1]) == 0 && ft_strcmp("-", str[2]) == 0)
		return (1);
	return (0);
}

int cd(char **command, t_env **env, t_data *data, t_cmd *cmd)
{
	char *cwd;

	data->cd_ret = 0;
	if (!is_legal_options(command, cmd, data))
		return (1);
	cwd = get_cwd(BUF_CWD, data);
	if (!cwd)
		return (1);
	if (is_goto_home(command))
		go_to_home_directory(env, data, cmd);
	else if (is_logical_goto_oldpwd(command))
		go_to_old_pwd(data, env, 0, cmd);
	else if (is_physical_goto_oldpwd(command))
		go_to_old_pwd(data, env, 1, cmd);
	else if (ft_strcmp(command[1], "-P") == 0)
		change_dir(command[2], env, data, 1, cmd);
	else if (ft_strcmp(command[1], "-L") == 0)
		change_dir(command[2], env, data, 0, cmd);
	else
		change_dir(command[1], env, data, 0, cmd);
	free(cwd);
	return (data->cd_ret);
}
