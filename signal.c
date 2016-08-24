#include <sh21.h>

void	sigint(int sig)
{
	t_data	*data;

	sig = 0;
	(void)sig;
	data = singleton_data(NULL, 0);
	exec_tcap("me");
	while (data->index < (int)ft_strlen(data->cmd))
		move_right_without_mod(data);
	ft_putstr("\n");
	data->real_len_cmd = 0;
	if (data->first)
	{
		free(data->first);
		data->first = NULL;
	}
	data->first_search = 1;
	data->history_en_cours = NULL;
	free(data->cmd);
	data->cmd = ft_strdup("");
	data->index = 0;
	data->c = 0;
	free(data->prompt);
	data->prompt = print_prompt(data->env, data);
	data->len_prompt = ft_strlen(data->prompt);
	if (data->cmd_tmp)
	{
		if (data->cmd_tmp[0])
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
		}
	}
	reinitialise_heredoc(data, 1);
	free(data->cmd_tmp);
	data->cmd_tmp = ft_strdup("");
	data->quote_old_index = 0;
	data->mode_copy = 0;
	data->list_auto = NULL;
	data->cmd_before_auto = NULL;
	if (data->absolute_cmd_before_auto)
		free(data->absolute_cmd_before_auto);
	data->absolute_cmd_before_auto = NULL;
	data->index_before_auto = 0;
	data->index_before_move = 0;
}

void	clear_cmd(t_data *data)
{
	int	j;
	int	i;

	exec_tcap("cr");
	i = get_actual_line(data);
	j = get_line_max(data);
	while (i < j)
	{
		exec_tcap("do");
		i++;
	}
	j = get_line_max(data);
	while (j >= 0)
	{
		exec_tcap("cd");
		exec_tcap("up");
		j--;
	}
	j = 0;
	data->index = 0;
	i = 0;
	print_prompt(data->env, data);
	i = 0;
	while (i < (int)ft_strlen(data->cmd))
	{
		ft_putchar(data->cmd[i]);
		if (get_actual_cursor(data) + 1 == data->win_x)
		{
			exec_tcap("do");
			exec_tcap("cr");
		}
		data->index++;
		i++;
	}
}
