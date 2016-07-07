/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:30:14 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/07 19:03:36 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*print_prompt(t_env *env, t_data *data)
{
	char	*new;
	char	*tmp;
	char	*prompt;

	ft_putstr("\e[38;5;208m");
	if (data->c != '\0')
	{
		prompt_quote(data);
		ft_putstr("\e[39m");
		return (data->prompt);
	}
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
 		prompt = ft_strdup("<");
		prompt = ft_strjoinaf12(prompt, new);
		prompt = ft_strjoinaf1(prompt, ">% ");
	}
	else
//		prompt = ft_strjoinaf1(new, "");
	prompt = new;
	// printf("[%s]\n", data->first);
	ft_putstr(prompt);
	ft_putstr("\e[39m");
	return(prompt);
}


int			main(int ac, char **av, char **env)
{
	t_env		*list;
	t_data	data;
//	char	*cmd;

	if (ac > 1)
	{
		ft_putstr_fd("Usage : ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	list = ft_parse_env(env);
//	exec_mshrc(&list);
	singleton_termios(init_term(), 1); // Mets le term en mode non canonique et tout le bordel
	data.c = '\0';
	data.prompt = print_prompt(list, &data); // On mets le prompt dans data.prompt
	data.len_prompt = ft_strlen(data.prompt); // On mets la longueur dans...
	data.curs_x = data.len_prompt + 1;
	data.curs_y = 0;
	data.cmd = ft_strdup("");
	data.index = 0;
	data.real_len_cmd = 0;
	data.history = NULL;
	data.history_en_cours = NULL;
	data.end_hd = 0;
	data.heredocs = NULL;
	data.first = NULL;
	data.first_search = 1;
	boucle(list, &data); // Entre dans la boucle principale du programme.
	return (0);
}
