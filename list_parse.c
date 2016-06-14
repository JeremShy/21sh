/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/13 22:30:19 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (DCHEV_DROITE);
	else if (ft_strnstr(str, "<<", 2))
		return (DCHEV_GAUCHE);
	else if (ft_strnstr(str, "&&", 2))
		return (ETET);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == '>')
		return (str[0]);
	else if (str[0] == '<')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

void	join_inside_quote(size_t *i, char *str)
{
	size_t	tmp;
	char	open;

	open = str[*i];
	// printf("open : %c\n", open);
	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	tmp = *i;
	while (str[tmp + 2])
	{
		str[tmp] = str[tmp + 2];
		tmp++;
	}
	str[tmp] = '\0';
	// printf("str : =%s=\n", str);
	if (*i == 0 || is_quote_open(str[0]))
		return ;
	(*i)--;
}

// void replace_backslash(char *str, size_t *i)
// {
// 	size_t tmp;
//
// 	if (!(str[i] == '\\'))
// 		return ;
// 	tmp = *i;
// 	while (str[tmp])
// 	{
// 		str[tmp] = str[tmp + 1];
// 		tmp++;
// 	}
// }

void		print_list(t_cmd *lst)
{
	size_t	i;
	char		**av;
	size_t	j;

	i = 0;
	while (lst != NULL)
	{
		printf("list number : %zu\n", i);
		av = lst->av;
		j = 0;
		while (av[j])
		{
			printf("av[%zu] : #%s#\n", j, av[j]);
			j++;
		}
		printf("sep : %c\n", lst->sep);
		i++;
		lst = lst->next;
		printf("\n");
	}
}

void		split_cmd(int count, char *str, t_cmd *cmd)
{
	size_t 	tmp_i;
	char		*tmp;
	size_t	i;
	int			n_av;

	i = 0;
	cmd->av = (char**)malloc((count + 1) * sizeof(char*));
	n_av = 0;
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		tmp_i = i;
		if(handle_aggr(&i, str, 1, cmd))
		{
			printf("IT'S ALIVE\n");
		}
		else if (handle_redir(&i, str, 1, cmd))
		{
			printf("TYPICAL PENIS\n");
		}
		else if (is_sep(&i, str, 1))
		{
			printf("RIP ORIGINALITE\n");
			// (*i)++;
			return ;
		}
		else if ((tmp = skip_quotes(str, &i, cmd)) != NULL)
		{
			if (tmp_i != i )
			{
				// printf("str : %s, i : %zu, tmp_i : %zu\n", str, i, tmp_i);
				cmd->av[n_av] = ft_strsub(str, tmp_i, i - tmp_i);
				printf("on ecrit : [%s]\n", cmd->av[n_av]);
				n_av++;
			}
		}
	}
}

t_cmd	*create_cmd_elem(char *str, int count)
{
	t_cmd		*elem;
	int			sep;

	sep = 0;
	elem = (t_cmd*)malloc(sizeof(t_cmd));
	elem->fd_in = create_fd(-1);
	elem->fd_out = create_fd(-2);
	elem->fd_err = create_fd(-3);
	// printf("str: %s\n", str);
	printf("str : [%s]\n", str);
	split_cmd(count, str, elem);
	elem->next = NULL;
	// printf("sep : %c\n", (char)sep);
	free(str);
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	t_cmd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}
