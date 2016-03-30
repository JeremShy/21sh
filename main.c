/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:30:14 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/14 14:59:29 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_prompt(t_env *env)
{
	char	*new;
	char	*tmp;

	new = find_arg(env, "PROMPT");
	if (ft_strequ(new, ""))
	{
		free(new);
		new = getcwd(NULL, 0);
		if (!new)
		{
			tmp = find_arg(env, "HOME");
			if (ft_strequ(tmp, ""))
				tmp = ft_strjoinaf1(tmp, "/");
			change_arg(env, "PWD", tmp);
			chdir(tmp);
			new = getcwd(NULL, 0);
			free(tmp);
		}
		ft_printf("<%s>%% ", new);
	}
	else
		ft_printf("%s ", new);
	free(new);
}

void		exec_cmd(char *cmd, t_env **env)
{
	char **scmd;

	scmd = ft_special_split(cmd);
	free(cmd);
	if (scmd[0])
	{
		if (is_builtin(scmd[0]))
			exec_builtin(scmd, env);
		else
			exec_file(scmd, *env);
	}
}

static void	exec_mshrc(t_env **env)
{
	char **scmd;

	scmd = malloc(3 * sizeof(char*));
	scmd[0] = ft_strdup("source");
	scmd[1] = ft_strjoinaf1(ft_strjoinaf1(find_arg(*env, "HOME"), "/"),
		".mshrc");
	scmd[2] = ft_strdup("");
	ft_source(scmd, env);
	free(scmd[0]);
	free(scmd[1]);
	free(scmd[2]);
	free(scmd);
}

void		handle_line(char *line, t_env **env)
{
	char	**cmd_tab;
	int		i;

	if (line)
	{
		cmd_tab = ft_strsplit(line, ';');
		i = 0;
		while (cmd_tab[i])
		{
			exec_cmd(cmd_tab[i], env);
			i++;
		}
		free(cmd_tab);
		free(line);
	}
	else
		ft_putchar('\n');
}

int			main(int ac, char **av, char **env)
{
	t_env	*list;
	char	*cmd;

	if (ac > 1)
	{
		ft_putstr_fd("Usage : ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	signal(SIGINT, SIG_IGN);
	list = ft_parse_env(env);
	exec_mshrc(&list);
	print_prompt(list);
	while (get_next_line(0, &cmd))
	{
		handle_line(cmd, &list);
		print_prompt(list);
	}
	return (0);
}
