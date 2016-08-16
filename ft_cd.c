#include <sh21.h>

static int	chg_arg1(char **scmd, t_env *env, char *tmp)
{
	char	*new_dir;

	if (chdir(scmd[1]) == 0)
	{
		new_dir = getcwd(NULL, 0);
		change_arg(env, "OLDPWD", tmp);
		change_arg(env, "PWD", new_dir);
		free(new_dir);
		free(tmp);
		return (1);
	}
	else
	{
		ft_putstr_fd("The directory \"", 2);
		ft_putstr_fd(scmd[1], 2);
		ft_putstr_fd("\" is inexistant, or you don't have the necessary ", 2);
		ft_putstr_fd("rights to access it.\n", 2);
		free(tmp);
		return (0);
	}
}

static void	goto_home(t_env *env, char *tmp, t_data *data)
{
	char	*temp;

	change_arg(env, "OLDPWD", tmp);
	temp = find_var_env(data, "HOME");
	change_arg(env, "PWD", temp);
	chdir(temp);
	free(temp);
}

void	goto_oldpwd(t_env *env, t_data *data)
{
	char *old_pwd;
	char *pwd;

	if ((old_pwd = (char *)find_var_env(data, "OLDPWD")))
	{
		chdir(old_pwd);
		if ((pwd = getcwd(NULL, 0)))
		{
			change_arg(env, "OLDPWD", find_var_env(data, "PWD"));
			change_arg(env, "PWD", pwd);
			free(pwd);
		}
		else
		{
			write(2, ERR_GETCWD, ft_strlen(ERR_GETCWD));
		}
	}
	else
	{
		write(2, ERR_GETOLDWD, ft_strlen(ERR_GETOLDWD));
	}
}



int			ft_cd(char **scmd, t_env *env, t_data *data)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		write(2, ERR_GETCWD, ft_strlen(ERR_GETCWD));
		return (0);
	}
	else if (!scmd[1])
		goto_home(env, tmp, data);
	else if (!ft_strequ(scmd[1], "-"))
		return (chg_arg1(scmd, env, tmp));
	else
		goto_oldpwd(env, data);
	free(tmp);
	return (1);
}
