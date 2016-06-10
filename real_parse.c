/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 22:47:34 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/09 23:17:42 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*handle_redir(size_t *i, char *str, int jump, t_cmd *cmd)
{
	size_t	tmp;
	char		*quote;
	int			fd;
	int			fd_file;
	int			redir_type; //0 : >, 1 : >>

	tmp = *i;
	fd = (str[tmp] == '>' ? 1 : 0);
	if ((str[tmp] == '<' && str[tmp + 1] == '<') || (str[tmp] == '>' && str[tmp + 1] == '>'))
	{
		redir_type = 1;
		tmp += 2;
	}
	else if (str[tmp] == '<' || str[tmp] == '>')
	{
		redir_type = 0;
		tmp++;
	}
	else if (ft_isdigit(str[*i]))
	{
		if ((str[tmp + 1] == '>' && str[tmp + 2] == '>') || (str[tmp + 1] == '<' && str[tmp + 2] == '<'))
		{
			redir_type = 1;
			tmp += 3;
		}
		else if (str[tmp + 1] == '>' || str[tmp + 1] == '<')
		{
			redir_type = 0;
			tmp += 2;
		}
		else
			return (NULL);
		fd = (str[tmp + 1] == '>' ? ft_atoi(str + *i) : 0);
	}
	if (tmp != *i)
	{
		while (ft_isspace2(str[tmp]))
			tmp++;
		if (is_empty(str, &tmp))
		{
			cmd->p_error = 1;
			return(NULL);
		}
		quote = skip_quotes(str, &tmp, cmd);
		if (!quote)
			quote = ft_strdup("");
		if (fd > 2)
			return(quote);
		printf("Quote : [%s]. fd : %d\n", quote, fd);
		if (redir_type == 0)
			fd_file = open(quote, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd_file = open(quote, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == 0)
			cmd->fd_in = add_fd_elem(cmd->fd_in, create_fd(fd_file));
		else if (fd == 1)
			cmd->fd_out = add_fd_elem(cmd->fd_out, create_fd(fd_file));
		else if (fd == 2)
			cmd->fd_err = add_fd_elem(cmd->fd_err, create_fd(fd_file));
		if (jump)
			*i = tmp;
		printf("redir_type : %d\n", redir_type);
		// dup2(fd_file, fd);
		// write(fd, "a\n", 2);
		return (quote);
	}
	return (NULL);
}
