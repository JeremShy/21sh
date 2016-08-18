#include <sh21.h>

void reinitialise_heredoc(t_data *data, int flag)
{
	// flag 0 = a la fin de la key
	// flag 1 = a la fin de la comande
	if (flag)
	{
		free_heredoc(data, data->heredocs);
		data->end_hd = 0;
		data->quote_or_hd = 0;
		data->first_line_of_hd = 1;
	}
	else
	{
		data->c = '\0';
		free(data->cmd);
		data->heredocs = add_hc_elem(data->heredocs, create_hc_elem(ft_strdup(data->heredocs_tmp)));
		if (data->cmd_tmp && data->cmd_tmp[0] != '\0')
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
		}
		data->index = data->old_index;
		data->real_len_cmd = 0;
		data->quote_or_hd = 1;
		data->cmd = data->command_save;
	}
	if (data->key_here)
	{
		free(data->key_here);
		data->key_here = NULL;
	}
	if (data->heredocs_tmp && data->heredocs_tmp[0] != '\0')
	{
		free(data->heredocs_tmp);
		data->heredocs_tmp = ft_strdup("");
	}
	// NE PAS OBULIER DE FREE EGALEMENT  CMD_TMP;
}

void	delete_heredocs(t_data *data)
{
	free_heredoc(data, data->heredocs);
	if (data->heredocs_tmp)
		free(data->heredocs_tmp);
	if (data->key_here)
		free(data->key_here);
	// if (data->cmd_tmp) // --> FREE AUSSI POUR LES QUOTES ?
	// 	free(data->cmd_tmp); // --> FREE AUSSI POUR LES QUOTES ?
	// if (data->command_save)
		// free(data->command_save);
}

int	ft_exit_bi(char **scmd, t_env *env, t_data *data)
{
	int	tmp;

	invert_term();
	history_exit(data);
	delete_list(env);
	delete_heredocs(data);
	delete_list_history(data->history);
	// delete_list_command(data->command);
	free(data->prompt);
	if (scmd && scmd[1])
	{
		tmp = ft_atoi(scmd[1]);
		free_char_tab(scmd);
		free(data->cmd);
		exit(tmp);
	}
	exit(EXIT_SUCCESS);
}
