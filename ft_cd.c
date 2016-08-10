#include <sh21.h>

static int	chg_arg1(char **scmd, t_env *env, char *tmp)
{
	char	*new;

	if (chdir(scmd[1]) == 0)
	{
		new = getcwd(NULL, 0);
		change_arg(env, "OLDPWD", tmp);
		change_arg(env, "PWD", new);
		free(new);
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

int			ft_cd(char **scmd, t_env *env, t_data *data)
{
	char	*tmp;
	char	*temp;

	tmp = getcwd(NULL, 0);
	if (!scmd[1])
		goto_home(env, tmp, data);
	else if (!ft_strequ(scmd[1], "-"))
		return (chg_arg1(scmd, env, tmp));
	else
	{
		temp = ft_strdup(find_var_env(data, "OLDPWD"));
		chdir(temp);
		free(tmp);
		tmp = getcwd(NULL, 0);
		change_arg(env, "OLDPWD", find_var_env(data, "PWD"));
		change_arg(env, "PWD", tmp);
		free(temp);
	}
	if (tmp)
		free(tmp);
	return (1);
}
