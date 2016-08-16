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
	new = find_var_env(data, "PROMPT", env);
	if (ft_strequ(new, ""))
	{
		free(new);
		new = getcwd(NULL, 0);
		if (!new)
		{
			tmp = find_var_env(data, "HOME", env);
			if (ft_strequ(tmp, ""))
				tmp = ft_strjoinaf1(tmp, "/");
			change_arg(env, "PWD", tmp);
			chdir(tmp);
			new = getcwd(NULL, 0);
			free(tmp);
		}
 		prompt = ft_strdup("<");
		prompt = ft_strjoinaf12(prompt, new);
		prompt = ft_strjoinaf1(prompt, ">$ ");
	}
	else
//		prompt = ft_strjoinaf1(new, "");
	prompt = new;
	// printf("[%s]\n", data->first);
	ft_putstr(prompt);
	ft_putstr("\e[39m");
	// printf("------------  %d --------------- %d ---------\n", (int)ft_strlen(prompt), data->win_x);
	if ((int)ft_strlen(prompt) == data->win_x)
	{
		data->index = 0;
		move_r2l(data);
		data->index--;
	}
	return(prompt);
}

int			main(int ac, char **av, char **env)
{
	t_data	data;
//	char	*cmd;

	if (ac > 1)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	data.env = ft_parse_env(env);
	data.var = NULL;
	singleton_termios(init_term(&data), 1); // Mets le term en mode non canonique et tout le bordel
	signal(SIGINT, sigint);
	signal(SIGWINCH, sigwinch);
	get_winsize(&data);
	data.c = '\0';
	data.prompt = print_prompt(data.env, &data); // On mets le prompt dans data.prompt
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
	data.key_here = NULL;
	data.cmd_tmp = ft_strdup("");
	data.heredocs_tmp = ft_strdup("");
	data.quote_or_hd = 0;
	data.first_line_of_hd = 1;
	data.quote_old_index = 0;
	data.mode_copy = 0;
	data.command_save = ft_strdup("");
	data.clipboard = NULL;
	data.list_auto = NULL;
	data.cmd_before_auto = NULL;
	data.index_before_auto = 0;
	data.absolute_cmd_before_auto = NULL;
	get_index_min_win(&data);
	init_history(&data);
	singleton_data(&data, 1);
	boucle(data.env, &data); // Entre dans la boucle principale du programme.
	return (0);
}
