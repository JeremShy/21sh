/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:38:42 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/29 16:39:02 by JeremShy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

static char	*resolve_symlink(char *file)
{
	char	lnk_path[PATH_MAX];
	t_stat	structure;
	int path_size;

	printf("resolving symlink.\n");
	if (lstat(file, &structure) == -1)
	{
		return (NULL);
	}
	if ((structure.st_mode & S_IFMT) == S_IFLNK)
	{
		path_size = readlink(file, lnk_path, PATH_MAX - 1);
		lnk_path[path_size] = '\0';
		free(file);
		file = ft_strdup(lnk_path);
	}
	return (file);
}

static int	chg_arg1(char **scmd, t_env *env, char *tmp, int p_opt)
{
	char	*new;
	int		i;

	i = 1;
	while (scmd[i] && scmd[i][0] == '-' && ((scmd[i + 1] && !ft_strequ(scmd[i + 1], "-")) || !scmd[i + 1]))
		i++;
	if (p_opt)
		scmd[i] = resolve_symlink(scmd[i]);
	printf("scmd[i] : [%s]\n", scmd[i]);
	if (scmd[i] && chdir(scmd[i]) == 0)
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
		ft_putstr_fd(scmd[i], 2);
		ft_putstr_fd("\" is inexistant, or you don't have the necessary ", 2);
		ft_putstr_fd("rights to access it.\n", 2);
		free(tmp);
		return (0);
	}
}

static void	goto_home(t_env *env, char *tmp, int p_opt)
{
	char	*temp;

	change_arg(env, "OLDPWD", tmp);
	temp = find_arg(env, "HOME");
	if (p_opt)
		temp = resolve_symlink(temp);
	change_arg(env, "PWD", temp);
	chdir(temp);
	free(temp);
}

int			ft_cd(char **scmd, t_env *env)
{
	char	*tmp;
	char	*temp;
	int		l_opt;
	int		p_opt;
	int		i;

	i = 1;
	l_opt = 0;
	p_opt = 0;
	while (scmd[i] && scmd[i][0] == '-' && ((scmd[i + 1] && !ft_strequ(scmd[i + 1], "-")) || !scmd[i + 1]))
	{
		if (ft_strchr(scmd[i] + 1, 'L'))
			l_opt = 1;
		if (ft_strchr(scmd[i] + 1, 'P'))
			p_opt = 1;
		i++;
	}
	if (scmd[i] && scmd[i + 1] && ft_strequ(scmd[i + 1], "-"))
		i++;
	tmp = getcwd(NULL, 0);
	if (!scmd[i])
		goto_home(env, tmp, p_opt);
	else if (!ft_strequ(scmd[i], "-"))
		return (chg_arg1(scmd, env, tmp, p_opt));
	else
	{
		temp = ft_strdup(find_arg(env, "OLDPWD"));
		if (p_opt)
			temp = resolve_symlink(temp);
		chdir(temp);
		free(tmp);
		tmp = getcwd(NULL, 0);
		change_arg(env, "OLDPWD", find_arg(env, "PWD"));
		change_arg(env, "PWD", tmp);
		free(temp);
	}
	if (tmp)
		free(tmp);
	return (1);
}
