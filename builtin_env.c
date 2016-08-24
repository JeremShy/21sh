/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:57:59 by jcamhi            #+#    #+#             */
/*   Updated: 2016/08/24 14:33:27 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	print_env(t_env *new, t_cmd *cmd)
{
	while (new)
	{
		putstr_builtin(cmd, new->name, 1);
		putstr_builtin(cmd, "=", 1);
		putendl_builtin(cmd, new->arg, 1);
		new = new->next;
	}
	return (0);
}

t_env	*copy_env(t_env *env)
{
	t_env	*new;

	new = NULL;
	while (env)
	{
		new = add_elem_end(new, env->name, env->arg);
		env = env->next;
	}
	return (new);
}

t_env *create_tmp_env(t_data *data, t_env *env, char **scmd)
{
	char	**new_elem;
	t_env	*tmp;
	char	**tmp_when_we_have_to_do_something;
	int	i;

	i = 0;
	tmp = NULL;
	if (data->in_env_i != 1)
		tmp = copy_env(env);
	if (scmd[i] && ft_strchr(scmd[i], '='))
	{
		while (scmd[i] && ft_strchr(scmd[i], '='))
		{
			new_elem = ft_strsplit(scmd[i], '=');
			if (!new_elem[1])
			{
				tmp_when_we_have_to_do_something = malloc(3 * sizeof(char*));
				tmp_when_we_have_to_do_something[0] = new_elem[0];
				tmp_when_we_have_to_do_something[1] = ft_strdup("");
				tmp_when_we_have_to_do_something[2] = NULL;
				// free(new_elem);
				free_char_tab(new_elem);
				new_elem = tmp_when_we_have_to_do_something;
			}
			if (isset_arg(tmp, new_elem[0]))
				change_arg(tmp, new_elem[0], new_elem[1]);
			else
				tmp = add_elem_end(tmp, new_elem[0], new_elem[1]);
			i++;
			free_char_tab(new_elem);
		}
	}
	return (tmp);
}

int	env_tmp_exec(t_env **env, t_data *data, char **scmd, t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*new;
	char	*new_str;
	t_cmd	*orig_cmd;
	int	i;

	i = 0;
	orig_cmd = data->command;
	new = create_tmp_env(data, *env, scmd + i);
	tmp = create_tmp_env(data, *env, scmd + i);
	while (scmd[i] && ft_strchr(scmd[i], '='))
		i++;
	if (scmd[i] && ft_strequ(scmd[i], "env") && !scmd[i + 1])
	{
		print_env(new, cmd);
		delete_list(new);
		delete_list(tmp);
		return (0);
	}
	new_str = ft_strdup("");
	while (scmd[i])
	{
		new_str = ft_strjoinaf12(new_str, ft_strjoin(" ", scmd[i]));
		i++;
	}
	if (data->in_env_i == 0)
		exec_cmd(&tmp, parse(new_str, data->heredocs, &tmp, data), data);
	else
	{
		data->in_env_i = 0;
		exec_cmd(&new, parse(new_str, data->heredocs, &new, data), data);
	}
	delete_list(new);
	delete_list(tmp);
	free(new_str);
	delete_list_command(data->command);
	data->command = orig_cmd;
	return (0);
}
