/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 15:12:42 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/30 16:22:06 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_env	*init_list_no_env(void)
{
	t_env	*ret;
	char	*tmp;

	tmp = ft_strdup("/nfs/2015/j/jcamhi/.brew/bin:/usr/bin:/bin:/usr/sbin");
	tmp = ft_strjoinaf1(tmp, ":/sbin:/usr/local/bin:/usr/local/munki");
	ret = add_elem_end(NULL, "PATH", tmp);
	free(tmp);
	tmp = getcwd(NULL, 0);
	ret = add_elem_end(ret, "PWD", tmp);
	ret = add_elem_end(ret, "OLDPWD", tmp);
	free(tmp);
	ret = add_elem_end(ret, "HOME", "/");
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
